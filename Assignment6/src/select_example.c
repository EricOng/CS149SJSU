#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    char buffer[128];
    int result, nread;
    fd_set inputs, input_fds;
    
    struct timeval timeout;
    
    FD_ZERO(&inputs);
    FD_SET(0, &inputs);
    
    while(1) {
    input_fds = inputs;
    timeout.tv_sec = 2;
    timeout.tv_usec = 500000;
    
    result = select(FD_SETSIZE, &input_fds, NULL, NULL, &timeout);
    
    switch(result) {
	case -1: {
	    perror("select");
	    exit(1);
    	}
	case 0: {
	    printf("@");
	    fflush(stdout);
	    break;
	}
	default: {
	    if(FD_ISSET(0, &input_fds)) {
		ioctl(0, FIONREAD, &nread);
		if(nread == 0) {
		    printf("Keyboard input done.\n");
		    exit(0);
		}
		nread = read(0, buffer, nread);
		buffer[nread] = 0;
		printf("Read %d characters from the keyboard: %s", nread, buffer);
	    }
	}
    }
    }
}

