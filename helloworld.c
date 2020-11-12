#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include "/usr/src/linux-headers-5.4.0-52-generic/include/linux/string.h"

MODULE_LICENSE("GPL");///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Miryala ");    ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("PID check");///< The description -- see modinfo
MODULE_VERSION("0.1");///< The version of the module

static char *name = "world";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");
///< parameter descript

static int __init findtask_init(void){
 struct task_struct* task_list;
 for_each_process(task_list)
 {
     pr_info("== %s [%d]\n", task_list->comm, task_list->pid);
 }
 
 string Task = strcmp(comm, name);
 if (Task == 0)
 {
    printk(KERN_INFO "Found Process", name, pid);
 }
 else
 {
     printk(KERN_INFO "Process Not Found", name);
 }
 
 return 0;
}

/** @brief The LKM cleanup function
*Similar to the initialization function, it is static. The __exit macro notifies if this
*code is used for a built-in driver (not a LKM) that this function is not required.
*/
static void __exit findtask_exit(void){
 printk(KERN_INFO "TDR: Goodbye %s from the Test LKM!\n", name);
}

/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which identify the initialization function at insertion time and the cleanup function (as listed above)
*/

module_init(findtask_init);
module_exit(findtask_exit);
