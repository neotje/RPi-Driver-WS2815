#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

static int __init test_driver_init(void)
{
    printk("Welcome to neo's driver!\n");
    return 0;
}

static void __exit test_driver_exit(void)
{
    printk("Leaving neo's driver!\n");
    return;
}

module_init(test_driver_init);
module_exit(test_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Neotje");
MODULE_DESCRIPTION("Test driver tutorial");
MODULE_VERSION("1.0");