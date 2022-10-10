#include <linux/kernel.h> /* Выполнение работы ядра. */
#include <linux/module.h> /* В частности, модуля. */
void cleanup_module(void)
{
pr_info("Short is the life of a kernel module\n");
}
MODULE_LICENSE("GPL");
