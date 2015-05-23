#include<linux/module.h>
#include<linux/interrupt.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/wait.h>
#include<linux/uaccess.h>
#include<linux/kdev_t.h>
#include<mach/irqs.h>
#include<linux/sched.h>
#include<asm/io.h>
#include"head.h"
MODULE_LICENSE("GPL");


static int MAJOR = 250;
static int MINOR = 0;
struct cdev cdev;
int flag = 0;
int key = 0;
wait_queue_head_t readq_queue;
wait_queue_head_t writeq_queue;
static unsigned int *gpg3con;
static unsigned int *gpg3data;
static struct file_operations key1_operations;
static irqreturn_t key1_interrupt(int,void *);
struct tasklet_struct  my_tasklet;  //定义tasklet_steuct 结构体
void my_tasklet_func(unsigned long num)//tasklet 函数
{
	printk("helloooooooooooooooo\n");
}
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
	gpg3con = ioremap(0xe03001c0,4);
	gpg3data = ioremap(0xe03001c4,4);
	writel((readl(gpg3con) & ~0xffff) |(0x1111),gpg3con);
	tasklet_init(&my_tasklet,my_tasklet_func,0);//初始化tasklet；
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

static irqreturn_t key1_interrupt(int irqnum,void *arg)
{
	switch(irqnum)
	{
		case IRQ_EINT(1):
			 key = 1;
			 flag = 1;
			 wake_up(&readq_queue);

			 return 0;
		case IRQ_EINT(2):
			 key = 2;
			 flag = 1;
			 wake_up(&readq_queue);
			 return 0;

		case IRQ_EINT(3):
			 key = 3;
			 flag = 1;
			 wake_up(&readq_queue);
			 return 0;

		case IRQ_EINT(4):
			 key = 4;
			 flag = 1;
			 wake_up(&readq_queue);
			 return 0;

		case IRQ_EINT(6):
			 key = 6;
			 flag = 1;
			 wake_up(&readq_queue);
			 return 0;

		case IRQ_EINT(7):	
			 key = 7;
			 flag = 1;
			 wake_up(&readq_queue);
			 return 0;
	}
	tasklet_schedule(&my_tasklet);//调度
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
	case LED_ON:
		writel(readl(gpg3data)|(1 << var),gpg3data);
		break;
	case LED_OFF:
		writel(readl(gpg3data)&(~0xf << var),gpg3data);
		break;
	}
	return ret;
}

static ssize_t key1_write(struct file *file, const char __user *buff, size_t num, loff_t *lsp)
{
	printk("key_write\n");
	return 0;
}
static struct file_operations key1_operations={
	.owner = THIS_MODULE,
	.open = key1_open,
	.release = key1_release,
	.read = key1_read,
	.write = key1_write,
	.unlocked_ioctl = key1_unlocked_ioctl,
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

