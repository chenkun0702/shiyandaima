#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

#define HELLO_MINOR 0

MODULE_LICENSE("GPL");
	
dev_t devno;

int hello_init(void)
{
	int ret;

	printk("Hello World\n");

	/*申请设备号*/
	ret = alloc_chrdev_region(&devno, HELLO_MINOR, 1, "hello");
	if (ret < 0) {
		printk("failed: register_chrdev_region\n");
		return ret;
	}

	return 0;
}

void hello_exit(void)
{
	unregister_chrdev_region(devno, 1);
	printk("Goodbye World\n");
}

module_init(hello_init);
module_exit(hello_exit);
