#include<linux/kernel.h>
#include<linux/platform_device.h>
#include<linux/module.h>
#include<linux/clk.h>
#include<linux/wait.h>
#include<linux/interrupt.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/io.h>
#include<linux/sched.h>
#include<asm/uaccess.h>



#define  ADC_MUTEX  0x1c
#define  ADC_CLEAR  0x18
#define  ADC_DATA0  0x0c
#define  ADC_CON    0x00
MODULE_LICENSE("GPL");

static int MAJOR = 250;
static int MINOR = 0;
dev_t devno;
char buff[128];
int flag = 0;
wait_queue_head_t myread;
static irqreturn_t adc_func(int ,void *);
struct cdev cdev;
struct resource *irqres;
void __iomem *adccon = NULL;
struct clk *clk;

static int hello_open(struct inode *node, struct file *flie)
{
	printk("hello_open success\n");
	return 0;
}

static int hello_release(struct inode *node, struct file *file)
{
	printk("hello_release success \n");
	return 0;
}


static ssize_t hello_read(struct file *file, char __user *buff, size_t num, loff_t *lsp)
{
	int data  = 0;
	int ret;
	if(num > 128 )
		num = 128;
	if(num < 0)
		return 0;
	writel(readl(adccon) |(0x1 << 0),adccon);//使能adccon ,打开adc转换
	wait_event(myread,flag !=0);  //等待中断
	data = readl(adccon + ADC_DATA0) &0xfff;//读取数据寄存器的值
	ret=copy_to_user(buff,&data,sizeof(int));//将读取到的值发送到应用层
	flag = 0;//flag置位
	return ret;
}


struct file_operations hello_file_operations={   //定义file_operations结构体
	.owner =THIS_MODULE, 
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
};

static irqreturn_t adc_func(int irqnum,void *arg)
{
	writel(0,adccon +ADC_CLEAR);//清中断
	flag = 1;  //flag置位
	wake_up(&myread);//唤醒读等待队列
	return IRQ_HANDLED;
}

int hello_probe(struct platform_device *pdev)
{
	int ret;
	//platform_get_resource(struct platform_device *dev,unsigned int type,unsigned int num);
	//                            描述设备的结构体        资源的类型                                
	struct resource *memres = platform_get_resource(pdev,IORESOURCE_MEM,0);//从pdev中获取第num个类型为type的资源，num默认从0开始
	struct resource *irqres = platform_get_resource(pdev,IORESOURCE_IRQ,0);
	if( memres==NULL || irqres == NULL)//判断资源是否合法
	{
		printk("get resource fail\n" );
		return -ENOMEM;
	}
	
	clk = clk_get(NULL,"adc"); //获得时钟
	clk_enable(clk);//使能时钟
	adccon = ioremap(memres->start,memres->end - memres->start);//物理地址到虚拟地址的映射
	if(adccon == NULL)
	{
		printk("ioremap fail\n");
		return -ENOMEM;
	}
	
	ret = request_irq(irqres->start,adc_func,IRQF_DISABLED,"adc",NULL);//注册中断
	if(0 != ret)
	{
		printk("request_irq fail\n");
		return -ENOMEM;
	}
	init_waitqueue_head(&myread);//初始化读等待头队列

	writel(0,ADC_MUTEX + adccon);//选择0通道
	writel((1<<16 | 1<<14 |0xff<<6),adccon);  //1<<16设置为12位精度  1<<14使能预分频 oxff<<6 预分频 
	        
	devno = MKDEV(MAJOR,MINOR);//申请设备号
	ret = register_chrdev_region(devno,1,"hello12");//注册设备号
	if(0 != ret)
	{
		printk("register_chrdev_region error \n");
		return -ENOMEM;
	}
	cdev_init(&cdev,&hello_file_operations);//初始化设备
	ret = cdev_add(&cdev,devno,1);//注册设备
	if(0 != ret)
	{
		printk("cdev_add error \n");
		goto err1;
	}
		
	printk("hello_probe\n");
	return 0;
err1:
	unregister_chrdev_region(devno,1);//如注册设备不成功，卸载设备号

	return 0;
}


int hello_remove(struct platform_device *device_t)  //卸载  和hello_probe相反的操作
{
	cdev_del(&cdev);//卸载设备
	unregister_chrdev_region(devno,1);//卸载设备号
	free_irq(irqres->start,NULL);//释放中断
	iounmap(adccon);//取消映射
	clk_disable(clk);//取消时钟
	return 0;
}

static struct platform_driver hello_driver ={

	.driver.name = "s5pc100-adc",   //此处名称需和platform_device中名称相同
	.probe = hello_probe,
	.remove = hello_remove,

};

int hello_init(void)  //加载函数
{

	platform_driver_register(&hello_driver);
	printk("hello_init\n");
	return 0;
}

void hello_exit(void)  //卸载函数
{

	platform_driver_unregister(&hello_driver);
	printk("hello_exit\n");

}

module_init(hello_init);
module_exit(hello_exit);
