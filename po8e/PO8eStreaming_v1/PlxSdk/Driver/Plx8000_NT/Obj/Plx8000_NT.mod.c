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
	{ 0x568fba06, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x8487a2b6, "flush_work" },
	{ 0x1fedf0f4, "__request_region" },
	{ 0x830e547b, "ioremap_prot" },
	{ 0x69a358a6, "iomem_resource" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x4d884691, "malloc_sizes" },
	{ 0x964bcb2, "boot_cpu_data" },
	{ 0xeb560280, "pci_disable_device" },
	{ 0xf89843f9, "schedule_work" },
	{ 0xd4dd3418, "__register_chrdev" },
	{ 0xf873629b, "x86_dma_fallback_dev" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x91715312, "sprintf" },
	{ 0x6395be94, "__init_waitqueue_head" },
	{ 0x71de9b3f, "_copy_to_user" },
	{ 0x49fadb13, "pci_set_master" },
	{ 0xff7559e4, "ioport_resource" },
	{ 0x8f64aa4, "_raw_spin_unlock_irqrestore" },
	{ 0x9021c4eb, "current_task" },
	{ 0x27e1a049, "printk" },
	{ 0x2fa5a500, "memcmp" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x226138e7, "pci_bus_write_config_dword" },
	{ 0x20da8e3d, "pci_get_domain_bus_and_slot" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x78764f4e, "pv_irq_ops" },
	{ 0x42c8de35, "ioremap_nocache" },
	{ 0x1714e2cd, "pci_bus_read_config_dword" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x7c61340c, "__release_region" },
	{ 0xb1b13d8f, "pci_unregister_driver" },
	{ 0x7a172b67, "kmem_cache_alloc_trace" },
	{ 0xd52bf1ce, "_raw_spin_lock" },
	{ 0x9327f5ce, "_raw_spin_lock_irqsave" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0xcf21d241, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0xb80dc366, "remap_pfn_range" },
	{ 0x5c8b5ce8, "prepare_to_wait" },
	{ 0xcbe1db9f, "pci_disable_msi" },
	{ 0xf1b1309d, "dma_supported" },
	{ 0xedc03953, "iounmap" },
	{ 0x87d591c5, "__pci_register_driver" },
	{ 0xfa66f77c, "finish_wait" },
	{ 0xde607115, "pci_dev_put" },
	{ 0xe6671df3, "pci_enable_msi_block" },
	{ 0xc1211685, "pci_enable_device" },
	{ 0x77e2f33, "_copy_from_user" },
	{ 0xba9eb9d3, "dma_ops" },
	{ 0xf20dabd8, "free_irq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v000010B5d*sv*sd*bc*sc*i*");
