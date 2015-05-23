#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
#include<linux/device.h>
#include<linux/poll.h>
#include<linux/sched.h>
#include<asm/io.h>
#include<asm-generic/poll.h>
#include"head.h"
#define   NUM   4
MODULE_LICENSE("GPL");

static int MAJOR = 260;
static int MINOR = 0;
static char buff1[20] = "hello world";
//static char buff2[20];
atomic_t  v = ATOMIC_INIT(1);
spinlock_t lock;
int flag = 1;
struct class *cls;
//static struct fasync_struct  *str;
//wait_queue_head_t my_queue_read;
//wait_queue_head_t my_queue_write;
//struct device device;
unsigned int *gpg3con;
unsigned int *gpg3data;
static struct cdev  cdev;
struct file_operations hello_init_ops;
static int hello_init(void)
{
	int ret;

	dev_t devno = MKDEV(MAJOR,MINOR);
	spin_lock_init(&lock);
//	init_waitqueue_head(&my_queue_read);
//	init_waitqueue_head(&my_queue_write);
    ret = register_chrdev_region(devno,NUM,"hello1");
	if (0 != ret)
	{

	//	alloc_chrdev_region(&devno, 0, 1,"hello");
		printk("register_chrdev_region fail\n");
	}

	cdev_init(&cdev,&hello_init_ops);
 	ret=cdev_add(&cdev,devno,NUM);
	if(ret != 0)
	{
		printk("error");
		unregister_chrdev_region(devno,NUM);
		return 0;
	}

	cls = class_create(THIS_MODULE,"hel123");
	device_create(cls,NULL,devno,NULL,"helllo-0");
	device_create(cls,NULL,devno+1,NULL,"helllo-1");//devno+1(主设备号不变，次设备号加1，后面为次设备名称）
	device_create(cls,NULL,devno+2,NULL,"helllo-2");
	device_create(cls,NULL,devno+3,NULL,"helllo-3");
	printk("hello_init\n");
#if 0
	gpg3con = ioremap(0xE03001c0,4);//物理地址映射为虚拟地址
	if (NULL == gpg3con)
	{
		printk("gpg3con  failue");
		goto err1;
	}
	gpg3data = ioremap(0xE03001c4,4);
	if(NULL == gpg3data)
	{
		printk("gpg3data failue");
		goto err2;
	}
    writel((readl(gpg3con) & (~0xffff)) | (0x1111),gpg3con);//readl函数参数为地址，返回值为寄存器值；writel函数将相应寄存器值写入指定地址
err1:
	cdev_del(&cdev);
err2:
	iounmap(gpg3con);
#endif
	return 0;
}

static int hello_open(struct inode *inode, struct file *fps)
{
	printk("hello_open success\n");
    printk("iminor = %d\n",iminor(inode));//获得次设备号
#if 0
	if(!atomic_dec_and_test(&v))
	{
		atomic_inc(&v);
		return -EBUSY;
	}
//#endif
	spin_lock(&lock);//获得自旋锁
	if(flag != 1)//判断条件是否成立
	{
		spin_unlock(&lock);//打开自旋锁
		return -EBUSY;
	}
	flag--;//修改标志位
	spin_unlock(&lock);//打开自旋锁
	printk("the first open success\n");
#endif
	return 0;
}

static int hello_release(struct inode *inode, struct file *fps)
{
//	flag++;
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
//	wait_event_interruptible(my_queue_read,flag != 1);
	if(copy_to_user(buff,buff1,20))
	{
		return 14;
	}
//	flag = 1;
//	wake_up_interruptible(&my_queue_write);
	printk("hello_read\n");
	return size;

}
#if 0
static ssize_t hello_write(struct file *file, const char __user *buff, size_t size, loff_t *len)
{
	int ret;
	if(size > 20)
		size = 20;
	if(size < 0)
		return EINVAL;
	printk("hello_write success\n");
//	wait_event_interruptible(my_queue_write,flag != 0);
    ret=copy_from_user(buff2 ,buff,20);
	if(0 != ret)
	{
		printk("copy_to_user error");
		return 0;
	}
//	flag = 0;
//	wake_up_interruptible(&my_queue_read);
	kill_fasync(&str,SIGIO,POLLIN);
	printk("buff2 = %s\n",buff2);
	return size;
}
#endif
#if 0
static long hello_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int n;
	int var = 0;
	n=copy_from_user(&var,(void *)arg,sizeof(arg));
	switch(cmd)
	{
	case LED_ON:
		printk("LED_ON\n");
		writel((readl(gpg3data))|(1<<var),gpg3data);
		break;
	case LED_OFF:
		writel((readl(gpg3data))|(~(1<<var)),gpg3data);
		printk("LED_OFF\n");
		break;
	}
	return 0;
}
#endif
#if 0
unsigned int hello_poll(struct file *file, struct poll_table_struct *stru)//轮循函数，判断目前是否可以进行非阻塞的读取和写入
{
	int mask = 0;

	poll_wait(file,&my_queue_read,stru);
	poll_wait(file,&my_queue_write,stru);
	if(flag != 1)
		mask |= POLLIN;
	if(flag != 0)
		mask |= POLLOUT;
	return mask;
}
int hello_fasync(int fd, struct file *file, int on)
{
	return (fasync_helper(fd,file,on,&str));	
	

}
#endif
struct file_operations hello_init_ops={

	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
//	.write = hello_write,
//	.fasync = hello_fasync,
//	.poll = hello_poll,
//	.unlocked_ioctl = hello_unlocked_ioctl,
};

static void hello_exit(void)
{

	dev_t devno = MKDEV(MAJOR,MINOR);
//	iounmap(gpg3data);
//	iounmap(gpg3con);
	device_destroy(cls,devno+3);
	device_destroy(cls,devno+2);
	device_destroy(cls,devno+1);
	device_destroy(cls,devno);
	class_destroy(cls);
	cdev_del(&cdev);
	unregister_chrdev_region(devno,NUM);
	
	printk("hello_exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
