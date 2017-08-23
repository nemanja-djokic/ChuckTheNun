#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x425785a6, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x4c554023, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0xeec4df5e, __VMLINUX_SYMBOL_STR(i2c_new_dummy) },
	{ 0xf4c89f08, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0x778c69ef, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbb72d4fe, __VMLINUX_SYMBOL_STR(__put_user_1) },
	{ 0x350233f9, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0x21e6c6e4, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xbd4c8d76, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x66bd9109, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "8D0C598D8B47429918255AD");
