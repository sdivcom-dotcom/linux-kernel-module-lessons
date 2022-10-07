#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sam. Kleiman");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");
static int __init hello_init(void) {
 printk(KERN_INFO "Hello, World Sam!\n");
 return 0;
}
static void __exit hello_exit(void) {
 printk(KERN_INFO "Goodbye, World Sam!\n");
}
module_init(hello_init);
module_exit(hello_exit);
