
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
MODULE_LICENSE("GPL");

int devmax = 225;
int devmin = 0;
static int hello_init(void)
{
	dev_t devno = MKDEV(devmax,devmin);
	int ret;
	ret=register_chrdev_region(devno,1,"hello");
	if(0 != ret )
	{
		printk("error");
		return 0;
	}
	printk("hello\n");
	return 0;
}

static void hello_clean(void)
{
	dev_t devno = MKDEV(devmax,devmin);
	unregister_chrdev_region(devno,1);
	printk("cleanup\n");
}

module_init(hello_init);

module_exit(hello_clean);
