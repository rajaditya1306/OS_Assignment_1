#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define COPY_SYSCALL 451

void check_equal(float** src, float** dest, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (src[i][j] != dest[i][j]) {
				printf("error\n");
				return;
			}
		}
	}
	printf("success\n");
}

int main() {
	float src[2][2] = {{1.0,2.0},{2.0,3.0}};
	float dest[2][2] = {{0.0,0.0},{0.0,0.0}};

	long sys_call_status;

	sys_call_status = syscall(COPY_SYSCALL, src, dest, 2, 2);

	if (sys_call_status != EFAULT) {
		printf("invoked\n");
		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++) {
				printf("%f", dest[i][j]);
			}
		printf("\n");
		}
	}
	return 0;
}
