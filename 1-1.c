#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define BILLION  1000000000L;

void calcTimeDifference(struct timespec tp1, struct timespec tp2, struct timespec* result) {
	result->tv_sec = (tp2.tv_sec - tp1.tv_sec);  
	result->tv_nsec = (tp2.tv_nsec - tp1.tv_nsec);
}

void* countA(void* args) {
	double i, limit = pow(2, 32);
	struct timespec start, finish;
	struct timespec* tp = (struct timespec*) args;
	clock_gettime(CLOCK_REALTIME, &start);
	for (i = 1; i < limit; i++) {
		;
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	calcTimeDifference(start, finish, tp);
	pthread_exit(NULL);
}

void* countB(void* args) {
	double i, limit = pow(2, 32);
	struct timespec start, finish;
	struct timespec* tp = (struct timespec*) args;
	clock_gettime(CLOCK_REALTIME, &start);
	for (i = 1; i < limit; i++) {
		;
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	calcTimeDifference(start, finish, tp);
	pthread_exit(NULL);
}

void* countC(void* args) {
	double i, limit = pow(2, 32);
	struct timespec start, finish;
	struct timespec* tp = (struct timespec*) args;
	clock_gettime(CLOCK_REALTIME, &start);
	for (i = 1; i < limit; i++) {
		;
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	calcTimeDifference(start, finish, tp);
	pthread_exit(NULL);
}

int main() {
	pthread_t tid1, tid2, tid3;
	struct sched_param sp1, sp2, sp3;
	struct timespec tp1, tp2, tp3, test;
	pthread_attr_t at1, at2, at3;

	sp1.sched_priority = 0;
	sp2.sched_priority = 0;
	sp3.sched_priority = 0;

	pthread_attr_init(&at1);
	pthread_attr_init(&at2);
	pthread_attr_init(&at3);

	pthread_attr_setschedpolicy(&at1, SCHED_OTHER);
	pthread_attr_setschedpolicy(&at2, SCHED_RR);
	pthread_attr_setschedpolicy(&at3, SCHED_FIFO);

	pthread_attr_setschedparam(&at1, &sp1);
	pthread_attr_setschedparam(&at2, &sp2);
	pthread_attr_setschedparam(&at3, &sp3);

	pthread_create(&tid1, &at1, countA, (void*) &tp1);
	pthread_create(&tid2, &at2, countB, (void*) &tp2);
	pthread_create(&tid3, &at3, countC, (void*) &tp3);

	double time1 = tp1.tv_sec + tp1.tv_nsec/ BILLION;
	double time2 = tp2.tv_sec + tp2.tv_nsec/ BILLION;
	double time3 = tp3.tv_sec + tp3.tv_nsec/ BILLION;

	printf("thread 1: %lf\n", time1);
	printf("thread 2: %lf\n", time2);
	printf("thread 3: %lf\n", time3);

	return 0;
}