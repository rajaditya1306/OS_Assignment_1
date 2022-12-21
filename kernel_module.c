#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <sched.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/fs.h> 
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>

int read_process(pid_t pid, char* buf, char** start, off_t offset, int count, int* eof, void* data) {
	struct task_struct* task;

	for_each_process(task) {
		if (task_list->pid == pid) {

		}
	}
}