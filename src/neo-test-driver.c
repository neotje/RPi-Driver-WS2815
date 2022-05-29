#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#include <linux/proc_fs.h>
#include <linux/slab.h>

#include <asm/io.h>

/**
 * 
 * param stuff
 * 
 */


/**
 * 
 * Proc stuff
 * 
 */
#define TEST_DRIVER_MAX_SIZE 1024

static struct proc_dir_entry *test_proc = NULL;

static char data_buffer[TEST_DRIVER_MAX_SIZE];

ssize_t test_proc_read(struct file *file, char __user *user, size_t size, loff_t *offset)
{
    return copy_to_user(user, "test_proc_read\n", 15);
}

ssize_t test_proc_write(struct file *file, const char __user *user, size_t size, loff_t *offset)
{
    memset(data_buffer, 0x0, sizeof(data_buffer));

    if (size > TEST_DRIVER_MAX_SIZE)
        size = TEST_DRIVER_MAX_SIZE;

    copy_from_user(data_buffer, user, size);

    printk(KERN_INFO "test_proc_write: '%s'\n", data_buffer);
    return size;
}

static const struct proc_ops test_proc_ops = {
    .proc_read = test_proc_read, // this function gets executed when the user reads the proc file (e.g. cat /proc/neo-proc).
    .proc_write = test_proc_write, // this function gets executed when the user writes to the proc file (e.g. echo "test" > /proc/neo-proc).
};



/**
 * 
 * Module init and exit.
 * 
 */

static int __init test_driver_init(void)
{
    printk("Welcome to neo's driver!\n");

    test_proc = proc_create("neo-proc", 0666, NULL, &test_proc_ops);

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