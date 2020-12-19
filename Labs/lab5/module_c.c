#include <linux/module.h>

extern int test_n;

module_param(test_n, int, 0);
MODULE_PARM_DESC(test_n, "New test_n");

int init_module(void) {
    printk(KERN_INFO "Module C insert successfully\n");
    printk(KERN_INFO "The given param is %d\n", test_n);
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Module C remove successfully\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomy Hsieh");
MODULE_DESCRIPTION("Module C");
