
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
MODULE_LICENSE("GPL");


int var;
char *p;
int len ;
int array[4];

int global_data = 111222;
EXPORT_SYMBOL(global_data);
int *fun1(void)
{
	int *p;
	printk("zhizhenfun1i\n");
	p = &global_data;
	return p;
}
int func(void)
{
	printk("funcsuccess\n");
	return 0;
}
EXPORT_SYMBOL(func);
EXPORT_SYMBOL(fun1);

//module_param(p,charp ,0400);
//module_param_named(test,p,charp,0400);
module_param_array(array,int,&len,0400);
static int hello_init(void)
{
	printk("hello\n");
	printk("charp0 = %d\n",array[0]);
	printk("charp1 = %d\n",array[1]);
	printk("charp2 = %d\n",array[2]);
	printk("charp3 = %d\n",array[3]);
	return 0;
}

static void hello_clean(void)
{
	printk("cleanup\n");
}

module_init(hello_init);

module_exit(hello_clean);
