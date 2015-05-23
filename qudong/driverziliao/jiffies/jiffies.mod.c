#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xf6628fc9, "module_layout" },
	{ 0xd6a968fe, "cdev_del" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x2b140f5e, "cdev_add" },
	{ 0x88dc55cf, "cdev_init" },
	{ 0xd8e484f0, "register_chrdev_region" },
	{ 0x7d11c268, "jiffies" },
	{ 0xf9a482f9, "msleep" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xf89843f9, "schedule_work" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xabd0c91c, "rtc_time_to_tm" },
	{ 0x1d2e87c6, "do_gettimeofday" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "584FB9F3E613FF042EE2315");