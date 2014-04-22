#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>

#define BUFFER_SIZE 32
#define READ 0
#define WRITE 1

int main() {
    printf("Program started!\n");
    int fd1[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];
    int fd5[2];
    printf("Arrays created.\n");
    if(pipe(fd1) == -1) {
	fprintf(stderr, "Pipe 1 failed.");
	return 1;
    }
    if(pipe(fd2) == -1) {
	fprintf(stderr, "Pipe 2 failed.");
	return 1;
    }
    if(pipe(fd3) == -1) {
	fprintf(stderr, "Pipe 3 failed.");
	return 1;
    }
    if(pipe(fd4) == -1) {
	fprintf(stderr, "Pipe 4 failed.");
	return 1;
    }
    if(pipe(fd5) == -1) {
	fprintf(stderr, "Pipe 5 failed.");
	return 1;
    }
    // Spawn all of the child processes.
    if(fork() == 0) {
	printf("Child 1 begin!\n");
	// Child process #1
	close(fd1[READ]);
	sleep(6);
	write(fd1[WRITE], "Child 1 Message", BUFFER_SIZE);
	close(fd1[WRITE]);
    } else if(fork() == 0) {
	printf("Child 2 begin!\n");
	// Child process #2
	close(fd2[READ]);
	sleep(2);
	write(fd2[WRITE], "Child 2 Message", BUFFER_SIZE);
	close(fd2[WRITE]);
    } else if(fork() == 0) {
	printf("Child 3 begin!\n");
	// Child process #3
	close(fd3[READ]);
	sleep(4);
	write(fd3[WRITE], "Child 3 Message", BUFFER_SIZE);
	close(fd3[WRITE]);
    } else if(fork() == 0) {
	printf("Child 4 begin!\n");
	// Child process #4
	close(fd4[READ]);
	sleep(5);
	write(fd4[WRITE], "Child 4 Message", BUFFER_SIZE);
	close(fd4[WRITE]);
    } else if(fork() == 0) {
	printf("Child 5 begin!\n");
	// Child process #5 (different from 1-4)
	close(fd5[READ]);
	write(fd5[WRITE], "Child 5 Message", BUFFER_SIZE);
	close(fd5[WRITE]);
    } else {
	printf("Parent begin!\n");
	// Parent process
	// Close the unused WRITE ends
	close(fd1[WRITE]);
	close(fd2[WRITE]);
	close(fd3[WRITE]);
	close(fd4[WRITE]);
	close(fd5[WRITE]);
	printf("Closed write ends.\n");
	
	char buffer[BUFFER_SIZE];
	int result, nread;
	fd_set inputs, input_fds;
	struct timeval timeout;
	FD_ZERO(&inputs);
	printf("Adding to sets.\n");
	FD_SET(fd1[READ], &inputs);
	FD_SET(fd2[READ], &inputs);
	FD_SET(fd3[READ], &inputs);
	FD_SET(fd4[READ], &inputs);
	FD_SET(fd5[READ], &inputs);
	int readTotal = 0;
	while(readTotal < 5) {
	    input_fds = inputs;
	    timeout.tv_sec = 2;
	    timeout.tv_usec = 500000;
	    result = select(FD_SETSIZE, &input_fds, NULL, NULL, &timeout);
	    switch(result) {
		case -1: {
		    perror("Select:");
		    exit(1);
		}
		case 0: {
		    printf("No children are ready.\n");
		    sleep(1);
		}
		default: {
		    if(FD_ISSET(fd1[READ], &input_fds)) {
			nread = read(fd1[READ], buffer, BUFFER_SIZE);
			buffer[nread] = 0;
			printf("Host read message(%d) from Child 1: %s\n", nread, buffer);
			readTotal++;
		    }
		    if(FD_ISSET(fd2[READ], &input_fds)) {
			nread = read(fd2[READ], buffer, BUFFER_SIZE);
			buffer[nread] = 0;
			printf("Host read message(%d) from Child 2: %s\n", nread, buffer);
			readTotal++;
		    }
		    if(FD_ISSET(fd3[READ], &input_fds)) {
			nread = read(fd3[READ], buffer, BUFFER_SIZE);
			buffer[nread] = 0;
			printf("Host read message(%d) from Child 3: %s\n", nread, buffer);
			readTotal++;
		    }
		    if(FD_ISSET(fd4[READ], &input_fds)) {
			nread = read(fd4[READ], buffer, BUFFER_SIZE);
			buffer[nread] = 0;
			printf("Host read message(%d) from Child 4: %s\n", nread, buffer);
			readTotal++;
		    }
		    if(FD_ISSET(fd5[READ], &input_fds)) {
			nread = read(fd5[READ], buffer, BUFFER_SIZE);
			buffer[nread] = 0;
			printf("Host read message(%d) from Child 5: %s\n", nread, buffer);
			readTotal++;
		    }
		}
	    }
	}
	
	// Close the READ ends
	close(fd1[READ]);
	close(fd2[READ]);
	close(fd3[READ]);
	close(fd4[READ]);
	close(fd5[READ]);
    }
}


