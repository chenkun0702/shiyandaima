#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
#include<linux/device.h>
#include"head.h"
#define   NUM   4
MODULE_LICENSE("GPL");//模块的申明，如果没有申明容易出现警告

static int MAJOR = 260;
static int MINOR = 0;
static char buff1[20] = "hello world";
static char buff2[20];
atomic_t  v = ATOMIC_INIT(1);//定义原子变量v并初始化为1，1表示未打开
spinlock_t lock;//定义自旋锁
int flag = 1;   //表示未打开
struct class *cls;  //定义类
//struct device device;
static struct cdev  cdev;
struct file_operations hello_init_ops;
static int hello_init(void)
{
	int ret;

	dev_t devno = MKDEV(MAJOR,MINOR);  //申请设备号，devno同时包括主设备号和次设备号；
	spin_lock_init(&lock);//初始化自旋锁
    ret = register_chrdev_region(devno,NUM,"hello1");//注册设备号，NUM表示注册的次设备的个数，hello1为设备名称
	if (0 != ret)
	{

	//	alloc_chrdev_region(&devno, 0, 1,"hello");
		printk("register_chrdev_region fail\n");
	}

	cdev_init(&cdev,&hello_init_ops);//设备初始化
 	ret=cdev_add(&cdev,devno,NUM);//注册设备
	if(ret != 0)
	{
		printk("error");
		unregister_chrdev_region(devno,NUM);//如果注册设备不成功，则释放设备号
		return 0;
	}

	cls = class_create(THIS_MODULE,"hel123");//自动创建一个类
	device_create(cls,NULL,devno,NULL,"helllo-0");//自动创建设备节点
	device_create(cls,NULL,devno+1,NULL,"helllo-1");//devno+1(主设备号不变，次设备号加1，后面为次设备名称）
	device_create(cls,NULL,devno+2,NULL,"helllo-2");
	device_create(cls,NULL,devno+3,NULL,"helllo-3");
	printk("hello_init\n");
	return 0;
}

static int hello_open(struct inode *inode, struct file *fps)
{
	printk("hello_open success\n");
    printk("iminor = %d\n",iminor(inode));//获得次设备号
#if 0
	if(!atomic_dec_and_test(&v)) //原子操作，先自减再测试，由于上面定义了v值为1，自减后值为0，（为0返回TRUE
		                          //   否则返回FALSE）
		                          
	{
		atomic_inc(&v);
		return -EBUSY;//返回错误码，前面加负号
	}
//#endif
	spin_lock(&lock);  //自旋锁
	if(flag != 1)  
	{
		spin_unlock(&lock);//解锁
		return -EBUSY;
	}
	flag--;//FLAG置0
	spin_unlock(&lock);解锁
	printk("the first open success\n");
#endif
	return 0;
}

static int hello_release(struct inode *inode, struct file *fps)
{
	flag++;//FLAG置1
//	atomic_inc(&v);
	printk("hello_release success\n");
	return 0;
}

static ssize_t hello_read(struct file *file, char __user *buff, size_t size, loff_t *len)
{
	if (size > 20)
		size = 20;
	if(size < 0)
		return EINVAL;
	
	if(copy_to_user(buff,buff1,20))
	{
		return 14;
	}

	printk("hello_read\n");
	return 0;

}

static ssize_t hello_write(struct file *file, const char __user *buff, size_t size, loff_t *len)
{
	int ret;
	if(size > 20)
		size = 20;
	if(size < 0)
		return EINVAL;
	printk("hello_write success\n");
    ret=copy_from_user(buff2 ,buff,20);
	if(0 != ret)
	{
		printk("copy_to_user error");
		return 0;
	}
	
	printk("buff2 = %s\n",buff2);
	return 0;
}

#if 0 
static long hello_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
	case(LED_ON):

        copy_from_user(buff2 ,(void *)arg,20);
		printk("LED_ON\n arg = %d\n",arg);
		break;
	case(LED_OFF):
		printk("LED_OFF\n");
		break;
	}
	return 0;
}
#endif

struct file_operations hello_init_ops={

	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
	.write = hello_write,
//	.unlocked_ioctl = hello_unlocked_ioctl,
};

static void hello_exit(void)
{

	dev_t devno = MKDEV(MAJOR,MINOR);

	device_destroy(cls,devno+3);
	device_destroy(cls,devno+2);//自动释放设备，后申请的先释放
	device_destroy(cls,devno+1);
	device_destroy(cls,devno);
	class_destroy(cls);//释放类
	cdev_del(&cdev);//释放设备节点
	unregister_chrdev_region(devno,NUM);//释放设备号
	
	printk("hello_exit\n");
}

module_init(hello_init);//内核加载函数
module_exit(hello_exit);//内核释放资源
