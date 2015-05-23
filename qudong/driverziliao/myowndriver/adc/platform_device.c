#include<linux/kernel.h>
#include<linux/platform_device.h>
#include<linux/module.h>



MODULE_LICENSE("GPL");
void hello_release(struct device *dev)
{
	printk("hello_release\n");
}
static struct platform_device hello_device={

	.name = "platform_t",
	.id = -1,
	.dev.release = hello_release,
};

static int hello_init(void)
{
	platform_device_register(&hello_device);
	printk("hello_init \n");
	return 0;
}
void hello_exit(void)
{
	platform_device_unregister(&hello_device);
	printk("hello_exit\n");
}


module_init(hello_init);
module_exit(hello_exit);

