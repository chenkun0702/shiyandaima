#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/wait.h>
#include<linux/uaccess.h>
#include<linux/kdev_t.h>
#include<mach/irqs.h>
#include<linux/time.h>
#include<linux/rtc.h>
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
wait_queue_head_t readq_queue;
wait_queue_head_t writeq_queue;
static unsigned int *gpg3con;
static unsigned int *gpg3data;
static struct timeval  tim_t;
struct rtc_time  rtc_t;
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
	gpg3con = ioremap(0xe03001c0,4);
	gpg3data = ioremap(0xe03001c4,4);
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

	switch(my_timer.data)
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
	flag = 1;
	wake_up(&readq_queue);
	kill_fasync(&async,SIGIO,POLLIN);

}
static irqreturn_t key1_interrupt(int irqnum,void *arg)
{
	my_timer.data = irqnum;
	mod_timer(&my_timer,jiffies+15);
	return IRQ_HANDLED;
}

int key1_open(struct inode *inode, struct file *file)
{

	do_gettimeofday(&tim_t);
	rtc_time_to_tm(tim_t.tv_sec,&rtc_t);
	printk("%d-%d-%d  %d-%d-%d\n",rtc_t.tm_year,rtc_t.tm_mon,rtc_t.tm_mday,rtc_t.tm_hour,rtc_t.tm_min,rtc_t.tm_sec);
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
	case LED_ON:
		writel(readl(gpg3data)|(1 << var),gpg3data);
		break;
	case LED_OFF:
		writel(readl(gpg3data)&(~0xf << var),gpg3data);
		break;
	}
	return ret;
}
#if 0
static ssize_t key1_write(struct file *file, const char __user *buff, size_t size, loff_t *len)
{
	do_gettimeofday(&tim_t);
	rtc_time_to_tm(tim_t.tv_sec,&rtc_t);
	printk("%d-%d-%d  %d-%d-%d\n",rtc_t.tm_year,rtc_t.tm_mon,rtc_t.tm_mday,rtc_t.tm_hour,rtc_t.tm_min,rtc_t.tm_sec);
	
	printk("key1_write\n");
	return 0;
}
#endif
static int key1_fasync(int fd, struct file *file, int on)
{
	return(fasync_helper(fd,file,on,&async));
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

