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
    int fd1[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];
    int fd5[2];
    
    // Spawn all of the child processes.
    if(fork() == 0) {
	// Child process #1
	if(pipe(fd1) == -1) {
	    fprintf(stderr, "Child 1 failed.");
	    return 1;
	}
	close(fd1[READ]);
	write(fd1[WRITE], "Child 1 Message");
	close(fd1[WRITE]);
    } else if(fork() == 0) {
	// Child process #2
	if(pipe(fd2) == -1) {
	    fprintf(stderr, "Child 2 failed.");
	    return 1;
	}
	close(fd2[READ]);
	write(fd2[WRITE], "Child 2 Message");
	close(fd2[WRITE]);
    } else if(fork() == 0) {
	// Child process #3
	if(pipe(fd3) == -1) {
	    fprintf(stderr, "Child 3 failed.");
	    return 1;
	}
	close(fd3[READ]);
	write(fd3[WRITE], "Child 3 Message");
	close(fd3[WRITE]);
    } else if(fork() == 0) {
	// Child process #4
	if(pipe(fd4) == -1) {
	    fprintf(stderr, "Child 4 failed.");
	    return 1;
	}
	close(fd4[READ]);
	write(fd4[WRITE], "Child 4 Message");
	close(fd4[WRITE]);
    } else if(fork() == 0) {
	// Child process #5 (different from 1-4)
	if(pipe(fd5) == -1) {
	    fprintf(stderr, "Child 5 failed.");
	    return 1;
	}
	close(fd5[READ]);
	write(fd5[WRITE], "Child 5 Message");
	close(fd5[WRITE]);
    } else {
	// Parent process
	// Close the unused WRITE ends
	close(fd1[WRITE]);
	close(fd2[WRITE]);
	close(fd3[WRITE]);
	close(fd4[WRITE]);
	close(fd5[WRITE]);
	
	
	
	// Close the READ ends
	close(fd1[READ]);
	close(fd2[READ]);
	close(fd3[READ]);
	close(fd4[READ]);
	close(fd5[READ]);
    }
}


