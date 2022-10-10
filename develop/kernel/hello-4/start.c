/*
* start.c – пример модулей, состоящих из нескольких файлов.
*/
#include <linux/kernel.h> /* Выполнение работы ядра. */
#include <linux/module.h> /* В частности, модуля. */

int init_module(void)
{
pr_info("Hello, world - this is the kernel speaking\n");
return 0;
}
MODULE_LICENSE("GPL");
