#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/wait.h>
#include<linux/uaccess.h>
#include<linux/kdev_t.h>
#include"s5pc100_pwm.h"
#include"pwm_music.h"
#include<mach/irqs.h>
//#include<linux/time.h>
//#include<linux/rtc.h>
#include<linux/sched.h>
#include<asm/io.h>
#include<linux/poll.h>
#include"head.h"
MODULE_LICENSE("GPL");


static int MAJOR = 250;
static int MINOR = 0;
struct cdev cdev;
int flag = 0;
int key = 0;
struct timer_list  my_timer;
wait_queue_head_t readq_queue;   //定义读等待头队列
wait_queue_head_t writeq_queue;  //定义写等待头队列
static unsigned int *gpg3con;
static unsigned int *gpg3data;
static unsigned int *gpdcon;
static unsigned int *tcfg0;
static unsigned int *tcfg1;
static unsigned int *tcon;
static unsigned int *tcntb1;
static unsigned int *tcmpb1;
//static struct timeval  tim_t;
//struct rtc_time  rtc_t;
static struct fasync_struct *async;
static struct file_operations key1_operations;
static irqreturn_t key1_interrupt(int,void *);
void key1_function(unsigned long);
static int key1_init(void)
{
	int ret;
	dev_t devno = MKDEV(MAJOR,MINOR);
	ret = register_chrdev_region(devno,1,"key1");
	if(0 != ret)
	{
		printk("register_chrdev_region error");
		return 0;
	}
	
	cdev_init(&cdev,&key1_operations);	
	ret=cdev_add(&cdev,devno,1);
	if(0 != ret)
	{
		printk("cdev_add error");
		goto err1;
		return 0;
	}
	init_waitqueue_head(&readq_queue);
	init_waitqueue_head(&writeq_queue);
	init_timer(&my_timer);
	my_timer.function = key1_function;
	add_timer(&my_timer);

	gpg3con = ioremap(0xe03001c0,4);  //地址映射
	gpg3data = ioremap(0xe03001c4,4);

	gpdcon = ioremap(0xe0300080,4);
	tcfg0 = ioremap(0xea000000,4);
	tcfg1 = ioremap(0xea000004,4);
	tcon = ioremap(0xea000008,4);
	tcntb1 = ioremap(0xea000018,4);
	tcmpb1 = ioremap(0xea00001c,4);

	writel((readl(gpdcon)& ~0xf0) |(0x2 << 4),gpdcon); //定义gpdcon1引脚为pwmtout_1模式，使用定时器1   pwm:脉冲调制输出
	writel((readl(tcfg0)& ~0xff) |(0xff),tcfg0);       //预分频，1~255，寄存器0~8位
	writel((readl(tcfg1)& ~0xf0) |(0x2 << 4),tcfg1);    //分频
	writel((readl(tcntb1)& ~0xffffffff) |(0x200),tcntb1);//计数寄存器，需要初始化
	writel((readl(tcmpb1)& ~0xffffffff) |(0x100),tcmpb1);//比较寄存器，需要初始化
//	writel((readl(tcon)& ~0xf00) |(0x9 << 8),tcon);      //控制寄存器，先设置成0x2<<8位,打开手动装载位，填充完上面两个寄存器后设置成0x9<<8位,表示
//此时关闭手动装载，打开自动装载，同时打开控制寄存器；

	writel((readl(gpg3con) & ~0xffff) |(0x1111),gpg3con);
	ret = request_irq(IRQ_EINT(1),key1_interrupt,IRQF_TRIGGER_FALLING|IRQF_DISABLED,"KEY1",NULL);
	if(0 != ret)
	{
		printk("request_irq error");
		goto err2;
		return -EINVAL;
	}
	ret = request_irq(IRQ_EINT(2),key1_interrupt,IRQF_TRIGGER_FALLING|IRQF_DISABLED,"KEY2",NULL);
    if(0 != ret)
	{
		printk("request_irq 2");
		goto err3;
		return -EINVAL;
	}
	ret = request_irq(IRQ_EINT(3),key1_interrupt,IRQF_TRIGGER_FALLING|IRQF_DISABLED,"KEY3",NULL);
    if(0 != ret)
	{
		printk("request_irq 3");
		goto err4;
		return -EINVAL;
	}
	ret = request_irq(IRQ_EINT(4),key1_interrupt,IRQF_TRIGGER_FALLING|IRQF_DISABLED,"KEY4",NULL);
    if(0 != ret)
	{
		printk("request_irq 4");
		goto err5;
		return -EINVAL;
	}
	ret = request_irq(IRQ_EINT(6),key1_interrupt,IRQF_TRIGGER_FALLING|IRQF_DISABLED,"KEY6",NULL);
    if(0 != ret)
	{
		printk("request_irq 6");
		goto err6;
		return -EINVAL;
	}
	ret = request_irq(IRQ_EINT(7),key1_interrupt,IRQF_TRIGGER_FALLING|IRQF_DISABLED,"KEY7",NULL);
    if(0 != ret)
	{
		printk("request_irq 7");
		goto err7;
		return -EINVAL;
	}
	
	printk("key_init\n");
	return 0;
err7:
		free_irq(IRQ_EINT(6),NULL);
err6:
		free_irq(IRQ_EINT(4),NULL);
err5:
		free_irq(IRQ_EINT(3),NULL);
err4:
		free_irq(IRQ_EINT(2),NULL);
err3:
		free_irq(IRQ_EINT(1),NULL);
err2:
		cdev_del(&cdev);
err1:
		unregister_chrdev_region(devno,1);
		return ret;

}
void key1_function(unsigned long data)
{

	switch(my_timer.data)//switch 中断号
	{
	case IRQ_EINT(1):
		key = 1;
		break;
	case IRQ_EINT(2):
		key = 2;
		break;

	case IRQ_EINT(3):
		key = 3;
		break;

	case IRQ_EINT(4):
		key = 4;
		break;

	case IRQ_EINT(6):
		key = 6;
		break;

	case IRQ_EINT(7):	
		key = 7;
		break;
	}
	flag = 1;  //flag置位
	wake_up(&readq_queue);//唤醒读等待
	kill_fasync(&async,SIGIO,POLLIN);//发送信号给应用成，通知应用层此时可读；

}
static irqreturn_t key1_interrupt(int irqnum,void *arg)
{
	my_timer.data = irqnum; //将中断号保存到结构体中
	mod_timer(&my_timer,jiffies+10);//定义等待时间
	return IRQ_HANDLED;
}

int key1_open(struct inode *inode, struct file *file)
{

	printk("key1_open\n");
	return 0;
}


static int key1_release(struct inode *inode, struct file *file)
{

	printk("key1_release\n");
	return 0;
}


static ssize_t key1_read(struct file *file, char __user *buff, size_t num, loff_t *var)
{
	int ret;
	wait_event(readq_queue,flag!=0);
	ret = copy_to_user(buff,&key,sizeof(int));
	flag = 0;
	return(ret);
}
long key1_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;
	int var = 0;
	ret = copy_from_user(&var,(void *)arg,sizeof(int));

	switch(cmd)
	{
	case PWM_ON:
		writel((readl(tcon)& ~0xf00) |(0x2 << 8),tcon);
		writel((readl(tcon)& ~0xf00) |(0x9 << 8),tcon);
		break;
	case SET_PRE:
		//		writel((readl(tcfg0)& ~0xff) |(0Xff),tcfg0);
		break;
	case SET_CNT:
		writel((readl(tcntb1)& ~0xffffffff) |(var),tcntb1);//按位与或非时均转化为二进制后进行
		writel((readl(tcmpb1)& ~0xffffffff) |(var>>1),tcmpb1);

		break;
	}
	return ret;
}
#if 0
static ssize_t key1_write(struct file *file, const char __user *buff, size_t size, loff_t *len)
{
	do_gettimeofday(&tim_t);//获得内核时间  ，里面的结构体已在外部定义
	rtc_time_to_tm(tim_t.tv_sec,&rtc_t);//将内核时间转化为当前系统时间   
	printk("%d-%d-%d  %d-%d-%d\n",rtc_t.tm_year,rtc_t.tm_mon,rtc_t.tm_mday,rtc_t.tm_hour,rtc_t.tm_min,rtc_t.tm_sec);
	
	printk("key1_write\n");
	return 0;
}
#endif
static int key1_fasync(int fd, struct file *file, int on)
{
	return(fasync_helper(fd,file,on,&async));//异步通知驱动程序
}
static struct file_operations key1_operations={
	.owner = THIS_MODULE,
	.open = key1_open,
	.release = key1_release,
	.read = key1_read,
//	.write = key1_write,
	.unlocked_ioctl = key1_unlocked_ioctl,
	.fasync = key1_fasync,
};


static void key1_exit(void)
{
	dev_t devno = MKDEV(MAJOR,MINOR);
	free_irq(IRQ_EINT(1),NULL);
	free_irq(IRQ_EINT(2),NULL);
	free_irq(IRQ_EINT(3),NULL);
	free_irq(IRQ_EINT(4),NULL);
	free_irq(IRQ_EINT(6),NULL);
	free_irq(IRQ_EINT(7),NULL);
	cdev_del(&cdev);
	unregister_chrdev_region(devno,1);
	printk("key1_exit\n");
}

module_init(key1_init);
module_exit(key1_exit);

