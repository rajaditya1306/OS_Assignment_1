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

#define SIZE 4096

int main() {
	int len = 0, i, string_len = 7, a_index = -1, fd;

	if ((fd = shm_open("shm", O_RDWR, 0666)) < 0) {
		printf("shm open error\n");
		return 1;
	}

	void* ptr;
	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	while (1) {
		for (int i = 0; i < 5; i++) {
			char* a = (char*) ptr;
			printf("%s\n", a);
			len = strlen(a);
			ptr += len + 1;
			int alen = -1, ind = 0;
			for (int j = 0; j < len; j++) {
				if (a[j] == '_') {
					alen = 0;
					ind = j;
				}
				if (alen >= 0) alen += 1;
			}
			char num[alen + 1];
			for (int j = 0; j < len; j++) {
				if (j > ind) {
					num[j - ind - 1] = a[j];
				}
			}
			num[alen] = '\0';
			a_index = atoi(num);
			printf("%d\n", a_index);
		}
		if (a_index > 9) len = 2;
		else len = 1;
		char ind[len + 1];
		sprintf(ind, "%d", a_index);
		printf("%s\n", ind);
		sprintf(ptr, "%s", ind);
		ptr += strlen(ind) + 1;
		sprintf(ptr, "%s", "nnn");
		while (!strcmp(((char*)ptr), "nnn"));

		if (a_index == 49) break;
	}
	shm_unlink("shm");

	return 0;
}