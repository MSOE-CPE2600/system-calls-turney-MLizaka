/*
LAB9
ANDREW LIZAK
11/12/2024
------------------------
SYSTEM PROGRAMING
program_one.c --filename
------------------------
program 1 of lab 9
*/
#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main(){
    //struct timespec time;
    //clock_gettime(CLOCK_MONOTONIC, &time);
   // long time_reg = time.tv_sec;
   // int time_reg2 = (time_reg % 3600)/60; //->min
   // int time_reg3 = (time_reg2 / 3600); //->hrs
   // printf("system reports time as %d:%d seconds \n",time_reg3, time_reg2);
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    time_t time_reg = time.tv_sec;  // Total seconds since the system started
    struct tm *time_info = localtime(&time_reg);
    printf("TIME: %d:%d:%d (h:m:s)\n", time_info->tm_hour, time_info->tm_min, time_info->tm_sec);

    char hostname[256];
    size_t len = 256;
    gethostname(hostname, len);
    printf("network name: %s \n", hostname);

    struct utsname sys_infonames;
    int numba = uname(&sys_infonames);
    printf("the name of os: [%s] os release: [%s] os version: [%s] hardware type: [%s] \n",sys_infonames.sysname,sys_infonames.release,sys_infonames.version,sys_infonames.machine);

    int numbofproc = get_nprocs();
    printf("the number of processors is %d \n", numbofproc);

    struct sysinfo infozz;
    sysinfo(&infozz);
    printf("total physical mem is %ld bytes \n", infozz.totalram);
    printf("total avalibe free mem is %ld bytes \n",infozz.freeram);
    return 0;
}