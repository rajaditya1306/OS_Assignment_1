#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sched.h>

int t1, t2, t3;

#define BILLION 1000000000;

int main() {
    pid_t p1, p2, p3;
    scanf("%d %d %d", &t1, &t2, &t3);
    struct timespec start1, start2, start3, finish1, finish2, finish3;
    struct sched_param pa, pb, pc;
    pa.sched_priority = t1;
    pb.sched_priority = t2;
    pc.sched_priority = t3;
    double time1, time2, time3;
    
    p1 = fork();
    sched_setscheduler(getpid(), SCHED_OTHER, &pa);
    clock_gettime(CLOCK_REALTIME, &start1);

    if (p1 < 0) {
        fprintf(stderr, "Fork failed!!\n");
    }
    else if (p1 == 0) {
        // char* args1[] = {"/home/strayweeb/OS_Assignment_1/compile1.sh", NULL};
        execl("/bin/sh", "sh", "/home/strayweeb/OS_Assignment_1/compile1.sh", NULL);
    }
    else {
        p2 = fork();
        sched_setscheduler(getpid(), SCHED_FIFO, &pb);
        clock_gettime(CLOCK_REALTIME, &start2);

        if (p2 < 0) {
            fprintf(stderr, "Fork failed!!\n");
        }
        else if (p2 == 0) {clock_gettime(CLOCK_REALTIME, &start2);
            // char* args2[] = {"/home/strayweeb/OS_Assignment_1/compile2.sh", NULL};
            execl("/bin/sh", "sh", "/home/strayweeb/OS_Assignment_1/compile2.sh", NULL);
        }
        else {
            p3 = fork();
            sched_setscheduler(getpid(), SCHED_RR, &pc);
            clock_gettime(CLOCK_REALTIME, &start3);

            if (p3 < 0) {
                fprintf(stderr, "Fork failed!!\n");
            }
            else if (p3 == 0) {
                // char* args3[] = {"/home/strayweeb/OS_Assignment_1/compile3.sh", NULL};
                execl("/bin/sh", "sh", "/home/strayweeb/OS_Assignment_1/compile3.sh", NULL);
            }
            else {
                wait(&p3);
                clock_gettime(CLOCK_REALTIME, &finish3);
                time3 = (finish3.tv_sec - start3.tv_sec) + (double)(finish3.tv_nsec - start3.tv_nsec)/BILLION;
            }
            wait(&p2);
            clock_gettime(CLOCK_REALTIME, &finish2);
            time2 = (finish2.tv_sec - start2.tv_sec) + (double)(finish2.tv_nsec - start2.tv_nsec)/BILLION;
        }
        wait(&p1);
        clock_gettime(CLOCK_REALTIME, &finish1);
        time3 = (finish1.tv_sec - start1.tv_sec) + (double)(finish1.tv_nsec - start1.tv_nsec)/BILLION;  
    }
    printf("%lf %lf %lf", time1, time2, time3);
}
