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

char* generateRandomString(int string_len, int index) {
	char* base = "abcdefghijklmnopqrstuvwxyz";
	int len = 0, i;
	if (index > 9) len = 2;
	else len = 1;
	char ind[len + 1];
	sprintf(ind, "%d", index);
	char* new = (char*)malloc(sizeof(char)*(string_len + len + 1));

	for (i = 0; i < string_len - 1; i++) {
		int index = rand()%26;
		new[i] = base[index];
	}
	new[string_len - 1] = '_';
	for (i = string_len; i < string_len + len; i++) {
		new[i] = ind[i - string_len];
	}
	new[string_len + len] = '\0';

	return new;
}

int main() {
	int len = 0, i, string_len = 7, a_index = -1, fd;
	char** strings = (char**)malloc(sizeof(char*)*50);

	for (i = 0; i < 50; i++) {
		strings[i] = generateRandomString(string_len, i);
	}

	if ((fd = shm_open("shm", O_CREAT | O_RDWR, 0666)) < 0) {
		printf("shm open error\n");
		return 1;
	}

	ftruncate(fd, SIZE);

	void* ptr;
	ptr = mmap(0, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

	while (1) {
		for (i = a_index+1; i < a_index+6; i++) {
			// printf("%s\n", strings[i]);
			sprintf(ptr, "%s", strings[i]);
			ptr += strlen(strings[i]) + 1;
			// char buf[4] = {0};
			// snprintf(buf, sizeof(i), "%d", i);
			// write(fd, buf, strlen(buf));
			// char length[4];
			// sprintf(length, "%d", i);
		}
		char* a;
		while (a_index != i - 1) {
			a = (char*) ptr;
			a_index = atoi(a);
		}
		ptr += strlen(a) + 1;

		printf("Read: index %d\n", a_index);

		if (a_index == 49) {
			break;
		}
	}

	return 0;
}