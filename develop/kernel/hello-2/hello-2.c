#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sam. Kleiman");
MODULE_DESCRIPTION("A simple example Linux module #2.");
MODULE_VERSION("0.01");

static int hello2_data __initdata = 3;

static int __init hello_2_init(void)
{
pr_info("Hello, world %d\n", hello2_data);
return 0;
}
static void __exit hello_2_exit(void)
{
pr_info("Goodbye, world 2\n");
}
module_init(hello_2_init);
module_exit(hello_2_exit);
