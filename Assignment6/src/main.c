#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

int main() {
    fd_set inSet;
    struct timeval timeout;
    
    FD_ZERO(&inSet);
    FD_SET (open("./resources/file1.txt", O_RDONLY), &inSet);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    
    printf("%d\n", select(FD_SETSIZE, &inSet, NULL, NULL, &timeout));
    
    return 0;
}

