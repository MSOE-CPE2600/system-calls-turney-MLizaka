// Andrew Lizak 
//LAB9
//11/15/24
// pmod.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <time.h>
int main(int argc, char* argv[])
{
    int n1 = nice(0); //gets current nice value

    if(n1 == -1){
        printf("ERR \n");
        return 1;
    }

    printf(" current nice value %d \n", n1);
    int new_nice = n1 - 10;
    if(new_nice < -20){
        new_nice = -20;
    }

    if(nice(-10)==-1){
        printf("err \n");
        return 1;
    }

    printf("new nice %d \n", new_nice);

    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;

    if (nanosleep(&ts, NULL) == -1) {
        printf("ERR \n");
        return 1;
    }
    printf("BYE! \n");
    return 0;
}