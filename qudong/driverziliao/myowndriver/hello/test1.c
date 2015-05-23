#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>
#include"head.h"

MODULE_LICENSE("GPL");

static int MAJOR = 250;
static int MINOR = 0;
static char buff1[20] = "hello world";
static char buff2[20];

static struct cdev  cdev;
struct file_operations hello_init_ops;
static int hello_init(void)
{
	int ret;

	dev_t devno = MKDEV(MAJOR,MINOR);
    ret = register_chrdev_region(devno,1,"hello");
	if (0 != ret)
	{

		alloc_chrdev_region(&devno, 0, 1,"hello");
		printk("register_chrdev_region fail\n");
	}

	cdev_init(&cdev,&hello_init_ops);
 	ret=cdev_add(&cdev,devno,1);
	if(ret != 0)
	{
		printk("error");
		unregister_chrdev_region(devno,1);
		return 0;
	}

	printk("hello_init\n");
	return 0;
}

static int hello_open(struct inode *inode, struct file *fps)
{
	printk("hello_open success\n");
	return 0;
}

static int hello_release(struct inode *inode, struct file *fps)
{
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

static long hello_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
	case(LED_ON):
		printk("LED_ON\n");
		break;
	case(LED_OFF):
		printk("LED_OFF\n");
		break;
	}
	return 0;
}
struct file_operations hello_init_ops={

	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.read = hello_read,
	.write = hello_write,
	.unlocked_ioctl = hello_unlocked_ioctl,
};

static void hello_exit(void)
{

	dev_t devno = MKDEV(MAJOR,MINOR);
	
	cdev_del(&cdev);
	unregister_chrdev_region(devno,1);
	
	printk("hello_exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
