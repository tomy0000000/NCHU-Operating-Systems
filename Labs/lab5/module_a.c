#include <linux/module.h>

int comp_100(int n) {
    if(n > 100) {
        return 1;
    } else if(n < 100) {
        return -1;
    } else {
        return 0;
    }
}

int init_module(void) {
    printk(KERN_INFO "Module A insert successfully\n");
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Module A remove successfully\n");
}

EXPORT_SYMBOL(comp_100);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomy Hsieh");
MODULE_DESCRIPTION("Module A");
