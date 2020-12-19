#include <linux/module.h>

int test_n = 56;
extern int comp_100(int);

int init_module(void) {
    printk(KERN_INFO "Module B insert successfully\n");
    printk(KERN_INFO "test_n = %d\n", test_n);
    printk(KERN_INFO "comp_100(56) = %d\n", comp_100(test_n));
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Module B remove successfully\n");
}

EXPORT_SYMBOL(test_n);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomy Hsieh");
MODULE_DESCRIPTION("Module B");
