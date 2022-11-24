#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
#include <sched.h>

// double time1, time2, time3;
int t1, t2, t3;
#define BILLION 1000000000;

// void calcTimeDifference(struct timespec* tp1, struct timespec* tp2, struct timespec* result) {
// 	result->tv_sec = (tp2->tv_sec - tp1->tv_sec);  
// 	result->tv_nsec = (tp2->tv_nsec - tp1->tv_nsec);
// }

void* countA(void* args) {
	struct sched_param sp1;
	sp1.sched_priority = t1;
	pthread_setschedparam(pthread_self(), SCHED_OTHER, &sp1);
	unsigned int i = 1, limit = UINT_MAX;
	struct timespec start, finish;
	double* tp = (double*) args;
	clock_gettime(CLOCK_REALTIME, &start);
	while (i < limit) {
		i++;
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	*tp = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec)/BILLION;
	pthread_exit(NULL);
}

void* countB(void* args) {
	struct sched_param sp2;
	sp2.sched_priority = t2;
	pthread_setschedparam(pthread_self(), SCHED_RR, &sp2);
	unsigned int i = 1, limit = UINT_MAX;
	struct timespec start, finish;
	double* tp = (double*) args;
	clock_gettime(CLOCK_REALTIME, &start);
	while (i < limit) {
		i++;
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	*tp = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec)/BILLION;
	pthread_exit(NULL);
}

void* countC(void* args) {
	struct sched_param sp3;
	sp3.sched_priority = t3;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp3);
	unsigned int i = 1, limit = UINT_MAX;
	struct timespec start, finish;
	double* tp = (double*) args;
	clock_gettime(CLOCK_REALTIME, &start);
	while (i < limit) {
		i++;
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	*tp = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec)/BILLION;
	pthread_exit(NULL);
}

int main() {
	pthread_t tid1, tid2, tid3;
	double time1, time2, time3;
	scanf("%d %d %d", &t1, &t2, &t3);
	// struct sched_param sp1, sp2, sp3;
	// struct timespec* tp1 = (struct timespec*) malloc(sizeof(struct timespec));
	// struct timespec* tp2 = (struct timespec*) malloc(sizeof(struct timespec));
	// struct timespec* tp3 = (struct timespec*) malloc(sizeof(struct timespec));
	// pthread_attr_t at1, at2, at3;

	// sp1.sched_priority = 0;
	// sp2.sched_priority = 1;
	// sp3.sched_priority = 1;

	// pthread_attr_init(&at1);
	// pthread_attr_init(&at2);
	// pthread_attr_init(&at3);

	// pthread_attr_setschedpolicy(&at1, SCHED_OTHER);
	// pthread_attr_setschedpolicy(&at2, SCHED_RR);
	// pthread_attr_setschedpolicy(&at3, SCHED_FIFO);

	// pthread_attr_setschedparam(&at1, &sp1);
	// pthread_attr_setschedparam(&at2, &sp2);
	// pthread_attr_setschedparam(&at3, &sp3);

	pthread_create(&tid1, NULL, &countA, (void*) &time1);
	pthread_create(&tid2, NULL, &countB, (void*) &time2);
	pthread_create(&tid3, NULL, &countC, (void*) &time3);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	printf("thread 1: %lf\n", time1);
	printf("thread 2: %lf\n", time2);
	printf("thread 3: %lf\n", time3);

	return 0;
}
