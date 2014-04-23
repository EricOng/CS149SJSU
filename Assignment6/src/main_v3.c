#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>


#define BUFFER_SIZE 128
#define CHILD    5
#define THIRTY_SECONDS 30
#define THREE_SECONDS 3

char* timeText(struct timeval now, struct timeval then);

int main ()
{
	// Keep track of time
	struct timeval startTime;
	
	//Keep track of children
	bool child = false;
	int  child_id = -1;

	//File descriptor stuff
	pid_t pid[CHILD];
	int fd[CHILD][2] = {-1, -1, -1, -1 ,-1};
	
	fd_set inputs, inputfds;
	struct timeval timeout;

	gettimeofday(&startTime, NULL);
	//Create the children
	int k = 0;
	for(k; k < CHILD; k++)
	{
		//Prevent children from making children
		if(!child)
		{
			if(pipe(fd[k]) == -1)
			{
				fprintf(stderr,"pipe() failed");
				return 1;
			}

			pid[k] = fork();
			if(pid[k] < 0) 
			{
				fprintf(stderr,"fork() failed");
				return 1;
			}

			if(pid[k] == 0)
			{
				child = true;
				child_id = k;
			}
		}
	}

	//Children write messages to the pipe
	if(child)
	{
		sleep(child_id);
		srand(time(NULL));
		int messageCount = 0;
		
		char wbuf[BUFFER_SIZE];
		
		close(fd[child_id][0]);

		struct timeval currentTime;
		gettimeofday(&currentTime, NULL);
		while(currentTime.tv_sec - startTime.tv_sec < THIRTY_SECONDS) {
			messageCount = messageCount + 1;
			snprintf(wbuf, BUFFER_SIZE, "%s | Child %d message %d", timeText(currentTime, startTime), child_id, messageCount);
			write(fd[child_id][1], wbuf, BUFFER_SIZE);
			sleep(rand() % THREE_SECONDS);
			gettimeofday(&currentTime, NULL);
		}

		close(fd[child_id][1]);
	} 

	//Parent reads messages from the pipe
	else 
	{   
		FD_ZERO(&inputs);

		int i = 0;
		for(i; i < CHILD; i++)
		{
			FD_SET(fd[i][0], &inputs);
		}

		char rbuf[BUFFER_SIZE];
		int result;
		struct timeval now;
		gettimeofday(&now, NULL);
		while(now.tv_sec - startTime.tv_sec < THIRTY_SECONDS)
		{
			inputfds = inputs;

			timeout.tv_sec = 2;
			timeout.tv_usec = 500000;

			result = select(CHILD, &inputfds, (fd_set *) 0, (fd_set *) 0, &timeout);
			//printf("result: %d\n", result);

			switch(result) {
				case 0: {
					printf("read nothing\n");
					fflush(stdout);
					break;
				}

				case -1: {
					perror("select");
					return 1;
				}

				// If, during the wait, we have some action on the file descriptor,
				// we read the input on stdin and echo it whenever an 
				// <end of line> character is received, until that input is Ctrl-D.
				default: {
					int fd_id = 0;
					for(fd_id; fd_id < CHILD; fd_id++)
					{
						inputfds = inputs;
						if (FD_ISSET(fd[fd_id][0], &inputfds)) 
						{
							read(fd[fd_id][0], rbuf, BUFFER_SIZE);
							printf("%s | %s\n", timeText(now, startTime), rbuf);
							fflush(stdout);
						}
					}
					break;
				}
			}
		    gettimeofday(&now, NULL);
		}
	}

	return 0;
}

char* timeText(struct timeval now, struct timeval then) {
    char printOut[7];
    long sec = now.tv_sec - then.tv_sec;
    long usec = now.tv_usec - then.tv_usec;
    if(usec < 0) {
	sec = sec - 1;
	usec = usec + 1000000;
    }
    snprintf(printOut, 8, "%02d:%04d", sec, usec);
    return printOut;
}

