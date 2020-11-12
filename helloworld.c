#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vikyat ");
MODULE_DESCRIPTION("A simple Linux driver.");
MODULE_VERSION("0.1");

static char *name;
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name requested");

void procs_info_print(void)
{
        int Task = 1;
        int Num = 0;
        struct task_struct* task_list;
        size_t process_counter = 0;
        for_each_process(task_list) {
                ++process_counter;
        int Comp = strcmp(task_list->comm, name);
        if (Comp == 0)
        {
            Task = Comp;
            Num = task_list->pid;
        }

        }
    
        if (Task == 0)
        {
            printk(KERN_INFO "Found Process", name, Num);
        }
        else
        {
            printk(KERN_INFO "Process Not Found", name);
        }


    
    printk(KERN_INFO "== Number of process: %zu\n", process_counter);

 
 
}

int init_module(void)
{
        printk(KERN_INFO "[ INIT ==\n");

        procs_info_print();

        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "== CLEANUP ]\n");
}

MODULE_LICENSE("MIT");
