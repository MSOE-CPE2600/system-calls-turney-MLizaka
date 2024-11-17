// ANDREW LIZAK
//11/14/2024
//LAB9
// pinfo.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


const char* sched_policy_to_string(int policy) {
    switch(policy) {
        case SCHED_FIFO: return "SCHED_FIFO";
        case SCHED_RR: return "SCHED_RR";
        case SCHED_OTHER: return "SCHED_OTHER";
        case SCHED_IDLE: return "SCHED_IDLE";
        case SCHED_BATCH: return "SCHED_BATCH";
        default: return "Unknown";
    }
}

int main(int argc, char* argv[]) {
    pid_t pid;
    int priority;
    int sch_policy;
    struct sched_param sch_param;

    // Checking for passed in pid
    if (argc == 2) {
        pid = atoi(argv[1]);
    } else if (argc == 1) {
        pid = getpid();
    } else {
        fprintf(stderr, "Error with entered process id \n");
        return 1;
    }

    // Kill returns 0 when process is found and user has signal permissions
    if (kill(pid, 0) == -1) {
        if (errno == ESRCH) {
            printf("Error: Process does not exist.\n");
        } else {
            printf("Error \n");
        }
        return 1;
    }

    // Get nice value (priority)
    priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1) {
        printf("Error getting priority \n");
        return 1;
    }

    // Get scheduling policy
    sch_policy = sched_getscheduler(pid);
    if (sch_policy == -1) {
        printf("Error getting scheduler \n");
        return 1;
    }

    // Get real-time priority if applicable
    if (sch_policy == SCHED_FIFO || sch_policy == SCHED_RR) {
        if (sched_getparam(pid, &sch_param) == -1) {
            printf("Error getting real-time priority \n");
            return 1;
        }
        printf("Real-time priority: %d\n", sch_param.sched_priority);
    }

    printf("Process id is: %d\n", pid);
    printf("Priority: %d\n", priority);
    printf("Scheduling policy: %s\n", sched_policy_to_string(sch_policy));

    return 0;
}