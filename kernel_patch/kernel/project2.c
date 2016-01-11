#include <linux/sched.h>
#include <linux/types.h>

DECLARE_WAIT_QUEUE_HEAD(my_wait_queue);

asmlinkage void sys_go_to_sleep_now(void) {
    printk("Enter sys_go_to_sleep_now()\n");
    DEFINE_WAIT(cur_p);
    set_current_state(TASK_UNINTERRUPTIBLE);
    add_wait_queue(&my_wait_queue, &cur_p);
    printk("Try to call schedule()\n");
    schedule();
    printk("Exit sys_go_to_sleep_now()\n");
}

asmlinkage int sys_wake_up_my_process(pid_t pid) {
    struct task_struct * process = find_task_by_vpid(pid);
    int ret_pid = -1;
    unsigned long flags;

    printk(KERN_INFO "current_pid: %d\n", process->pid);

    spin_lock_irqsave(&(&my_wait_queue)->lock, flags);
    wait_queue_t *curr, *next;
    list_for_each_entry_safe(curr, next, &(&my_wait_queue)->task_list, task_list) {
        /* unsigned flags = curr->flags; */
        printk(KERN_INFO "try_pid: %d\n", ((struct task_struct *)(curr->private))->pid);
        if (((struct task_struct *)(curr->private))->pid == process->pid && curr->func(curr, TASK_NORMAL, 1, NULL))/* && (flags & WQ_FLAG_EXCLUSIVE) && !--nr_exclusive) */
        {
            printk(KERN_INFO "found target process\n");
            ret_pid = process->pid;
            break;
        }
    }
    spin_unlock_irqrestore(&(&my_wait_queue)->lock, flags);
    return ret_pid;
}
