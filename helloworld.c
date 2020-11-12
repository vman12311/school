#include <linux/init.h> // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>// Core header for loading LKMs into the kernel
#include <linux/kernel.h> // Contains types, macros, functions for the kernel

MODULE_LICENSE("GPL");///< The license type -- this affects runtime behavior
MODULE_AUTHOR(“Miryala ");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("PID check");///< The description -- see modinfo
MODULE_VERSION("0.1");///< The version of the module

static char *name = "world"; ///< An example LKM argument -- default value is "world"
module_param(name, charp, S_IRUGO); 
///< Param desc. charp = char ptr, S_IRUGO can be read/not changed
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");
///< parameter descript

static int __init hello_init(void){
 printk(KERN_INFO “TDR: Hello %s from the Test LKM!\n", name);
 return 0;
}

/** @brief The LKM cleanup function
*Similar to the initialization function, it is static. The __exit macro notifies if this
*code is used for a built-in driver (not a LKM) that this function is not required.
*/
static void __exit hello_exit(void){
 printk(KERN_INFO “TDR: Goodbye %s from the Test LKM!\n", name);
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which identify the initialization function at insertion time and the cleanup function (as listed above)
*/

module_init(hello_init);
module_exit(hello_exit);
