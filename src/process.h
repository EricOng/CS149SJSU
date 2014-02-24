typedef struct
{
    int priority;
    float arrival;
    float runtime;
    float timeRemaining;
    float responseTime;   // Time from entering the active queue to starting to run
    float waitTime;       // Time from entering the active queue that the process spends NOT running
    float turnaroundTime; // Time from entering the active queue to terminating
} Process;

