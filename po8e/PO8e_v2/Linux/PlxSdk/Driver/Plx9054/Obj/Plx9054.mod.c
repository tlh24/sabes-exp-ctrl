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
	{ 0x440b06f4, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x8487a2b6, "flush_work" },
	{ 0x1fedf0f4, "__request_region" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0x4d7272e4, "migrate_enable" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0x830e547b, "ioremap_prot" },
	{ 0x69a358a6, "iomem_resource" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xd50bf783, "dma_set_mask" },
	{ 0x4d884691, "malloc_sizes" },
	{ 0x964bcb2, "boot_cpu_data" },
	{ 0xd7cad316, "pci_disable_device" },
	{ 0xf31ede69, "__rt_mutex_init" },
	{ 0xf89843f9, "schedule_work" },
	{ 0x6678ce78, "__register_chrdev" },
	{ 0x1c15c176, "x86_dma_fallback_dev" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x91715312, "sprintf" },
	{ 0xabc53cba, "rt_up_read" },
	{ 0xefdc3015, "rt_spin_lock" },
	{ 0x9c457ab0, "rt_spin_unlock" },
	{ 0x89887225, "__init_waitqueue_head" },
	{ 0x71de9b3f, "_copy_to_user" },
	{ 0xa008145b, "pci_set_master" },
	{ 0xff7559e4, "ioport_resource" },
	{ 0x5d2f2554, "current_task" },
	{ 0x27e1a049, "printk" },
	{ 0x2fa5a500, "memcmp" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0x88d01bc1, "pci_bus_write_config_dword" },
	{ 0xd6b8e852, "request_threaded_irq" },
	{ 0x49608959, "migrate_disable" },
	{ 0x9638fbf2, "__rt_spin_lock_init" },
	{ 0x78764f4e, "pv_irq_ops" },
	{ 0x42c8de35, "ioremap_nocache" },
	{ 0x5c97817d, "pci_bus_read_config_dword" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xfc2e29c9, "get_user_pages" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x7c61340c, "__release_region" },
	{ 0xb4035192, "pci_unregister_driver" },
	{ 0x7a172b67, "kmem_cache_alloc_trace" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0xfcc57bad, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x963d01de, "remap_pfn_range" },
	{ 0x71a40c69, "prepare_to_wait" },
	{ 0x8173c477, "dma_supported" },
	{ 0xedc03953, "iounmap" },
	{ 0x5a574b29, "__pci_register_driver" },
	{ 0x4000ddad, "put_page" },
	{ 0xe9713c35, "finish_wait" },
	{ 0x8c30ce32, "pci_enable_device" },
	{ 0x77e2f33, "_copy_from_user" },
	{ 0x52ba837f, "rt_down_read" },
	{ 0x662d305, "dma_ops" },
	{ 0xf20dabd8, "free_irq" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v000010B5d00009054sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00004550d00009054sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v00004550d00000854sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010B5d00001860sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010B5d0000C860sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000010B5d00005406sv*sd*bc*sc*i*");
