/*
* intrpt.c – Обработка ввода-вывода с помощью прерываний.
*
* За основу взят пример RPi Стефана Вендлера (devnull@kaltpost.de)
* из репозитория https://github.com/wendlers/rpi-kmod-samples
*
* При нажатии одной кнопки светодиод загорается, а при нажатии другой
* гаснет.
*/
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
static int button_irqs[] = { -1, -1 };
/* Определение вводов-выводов для светодиодов.
* Номера выводов можете изменить.
*/
static struct gpio leds[] = { { 4, GPIOF_OUT_INIT_LOW, "LED 1" } };
/* Определение вводов-выводов для BUTTONS.
* Номера вводов-выводов можете изменить.
*/
static struct gpio buttons[] = { { 17, GPIOF_IN, "LED 1 ON BUTTON" },
{ 18, GPIOF_IN, "LED 1 OFF BUTTON" } };
/* Функция обработки прерываний, активируемая нажатием кнопки. */
static irqreturn_t button_isr(int irq, void *data)
{
/* Первая кнопка. */
if (irq == button_irqs[0] && !gpio_get_value(leds[0].gpio))
gpio_set_value(leds[0].gpio, 1);
/* Вторая кнопка. */
else if (irq == button_irqs[1] && gpio_get_value(leds[0].gpio))
gpio_set_value(leds[0].gpio, 0);
return IRQ_HANDLED;
}
static int __init intrpt_init(void)
{
int ret = 0;
pr_info("%s\n", __func__);
/* Регистрация вводов-выводов светодиодов. */
ret = gpio_request_array(leds, ARRAY_SIZE(leds));
if (ret) {
pr_err("Unable to request GPIOs for LEDs: %d\n", ret);
return ret;
}
/* Регистрация вводов-выводов для BUTTON. */
ret = gpio_request_array(buttons, ARRAY_SIZE(buttons));
if (ret) {
pr_err("Unable to request GPIOs for BUTTONs: %d\n", ret);
goto fail1;
}
pr_info("Current button1 value: %d\n", gpio_get_value(buttons[0].gpio));
ret = gpio_to_irq(buttons[0].gpio);
if (ret < 0) {
pr_err("Unable to request IRQ: %d\n", ret);
goto fail2;
}
button_irqs[0] = ret;
pr_info("Successfully requested BUTTON1 IRQ # %d\n", button_irqs[0]);
ret = request_irq(button_irqs[0], button_isr,
IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
"gpiomod#button1", NULL);
if (ret) {
pr_err("Unable to request IRQ: %d\n", ret);
goto fail2;
}
ret = gpio_to_irq(buttons[1].gpio);
if (ret < 0) {
pr_err("Unable to request IRQ: %d\n", ret);
goto fail2;
}
button_irqs[1] = ret;
pr_info("Successfully requested BUTTON2 IRQ # %d\n", button_irqs[1]);
ret = request_irq(button_irqs[1], button_isr,
IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
"gpiomod#button2", NULL);
if (ret) {
pr_err("Unable to request IRQ: %d\n", ret);
goto fail3;
}
return 0;
/* Удаление проделанных настроек. */
fail3:
free_irq(button_irqs[0], NULL);
fail2:
gpio_free_array(buttons, ARRAY_SIZE(leds));
fail1:
gpio_free_array(leds, ARRAY_SIZE(leds));
return ret;
}
static void __exit intrpt_exit(void)
{
int i;
pr_info("%s\n", __func__);
/* Свободные прерывания. */
free_irq(button_irqs[0], NULL);
free_irq(button_irqs[1], NULL);
/* Отключение всех светодиодов. */
for (i = 0; i < ARRAY_SIZE(leds); i++)
gpio_set_value(leds[i].gpio, 0);
/* Снятие регистрации. */
gpio_free_array(leds, ARRAY_SIZE(leds));
gpio_free_array(buttons, ARRAY_SIZE(buttons));
}
module_init(intrpt_init);
module_exit(intrpt_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Handle some GPIO interrupts");
