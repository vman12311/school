#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched/signal.h>
#include "linux/string.h" //my Linux's kernel string.h location
#include <linux/jiffies.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vikyat Miryala");
MODULE_DESCRIPTION("A simple Linux driver.");
MODULE_VERSION("0.1");

static char *name;
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name requested");

unsigned long j, one, half;

void simple_timer_function(struct timer_list *); //new
static struct timer_list simple_timer;



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
            printk(KERN_INFO "Found Process %s with PID: %d", name, Num);
        }
        else
        {
            printk(KERN_INFO "Not Found process %s", name);
        }


    
    printk(KERN_INFO ".");
 
}

int init_module(void)
{
        printk(KERN_INFO "[ INIT ==\n");
        add_timer(&simple_timer); //new
        mod_timer (&simple_timer, jiffies + ( msecs_to_jiffies(500))); //new
        procs_info_print();

        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "== CLEANUP ]\n");
        del_timer(&simple_timer);
}
