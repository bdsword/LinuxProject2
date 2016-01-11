/*===========================================================================*/
/*     prototype of new system call two is as follows                        */
/*     int wake_up_my_process(int)                                          */
/*     if this system is executed succwssfully, it returns 0; otherwise,     */
/*     it returns a negative value.                                          */
/*===========================================================================*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>      
#include <linux/types.h>

int wake_up_my_process(pid_t pid) {
    return syscall(352, pid);
}


main(int argc, char **argv)
{
    unsigned int pid;

    if(argc<2)
    {
        printf("Input the global PID of the process that you want to wake up.\n");
        printf("Format: program PID\n");
        exit(0);
    }

    pid=atol(argv[1]);

    if(wake_up_my_process(pid)<0)  //new system call two
    {
        printf("Cannot wake up process %d\n", pid);
        exit(0);
    }  
    else
        printf("Process %d has been waked up.\n",pid);                
}
