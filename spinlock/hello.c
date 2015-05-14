#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

#include "hello.h"

#define HELLO_MAJOR 250
#define HELLO_MINOR 0

MODULE_LICENSE("GPL");

static struct cdev cdev;

static char data[1024];

spinlock_t lock;
int flags = 1;
	
static int hello_open(struct inode *inode, struct file *file)
{
	spin_lock(&lock);
	if (flags != 1) {
		spin_unlock(&lock);
		return -EBUSY;
	}

	flags--;
	spin_unlock(&lock);

	printk("hello open\n");
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	flags++;
	printk("hello release\n");
	return 0;
}
	
static ssize_t hello_write(struct file *file, const char __user *buf, size_t count, loff_t *loff)
{
	if (count < 0)
		return -EINVAL;
	if (count > 1023)
		return -EINVAL;

	if (copy_from_user(data, buf, count))
		return -EFAULT;

	data[count] = '\0';
	/*将数据写入设备*/
	printk("data = %s\n", data);

	return count;
}


static ssize_t hello_read(struct file *file, char __user *buf, size_t count, loff_t *loff)
{	
	if (count < 0) 
		return -EINVAL;
	if (count > 1023)
		count = 1023;
	/*读取设备*/

	if (copy_to_user(buf, data, count))
		return -EFAULT;

	return count;
}
	
static long hello_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int data;

	switch(cmd) {
		case HELLO_CMD1:
			printk("Hello cmd 1\n");
			break;
		case HELLO_CMD2:
			printk("Hello cmd 2\n");
			if (copy_from_user(&data, (void *)arg, sizeof(data)))
				return -EFAULT;
			printk("data = %d\n", data);
			break;
		default:
			printk("Invalid argument\n");
			return -EINVAL;
	}

	return 0;
}

static struct file_operations hello_fops = {
	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.write = hello_write,
	.read = hello_read,
	.unlocked_ioctl = hello_ioctl,
};

static int hello_init(void)
{
	dev_t devno = MKDEV(HELLO_MAJOR, HELLO_MINOR);
	int ret;

	printk("Hello World\n");

	/*申请设备号*/
	ret = register_chrdev_region(devno, 1, "hello");
	if (ret < 0) {
		printk("failed: register_chrdev_region\n");
		return ret;
	}

	cdev_init(&cdev, &hello_fops);
	cdev.owner = THIS_MODULE;
	ret = cdev_add(&cdev, devno, 1);
	if (ret < 0) {
		printk("failed: cdev_add\n");
		unregister_chrdev_region(devno, 1);
		return ret;
	}

	spin_lock_init(&lock);

	return 0;
}

static void hello_exit(void)
{
	dev_t devno = MKDEV(HELLO_MAJOR, HELLO_MINOR);
	cdev_del(&cdev);
	unregister_chrdev_region(devno, 1);
	printk("Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
