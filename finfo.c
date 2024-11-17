// Andrew Lizak
//11/16/24
//LAB9
// finfo.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
void help_print_perms(mode_t mode){
    printf("permissions: ");
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');
    printf("\n");
}

void help_print_file_type(mode_t mode){
    if(S_ISDIR(mode)){
        printf("file type directory \n");
    }
    
    else if (S_ISREG(mode)){
        printf("regualar file \n");
    }    
    else if (S_ISLNK(mode)){
        printf("is linker file \n");
    }
    else if (S_ISFIFO(mode)){
        printf("FIFO file typen \n");
    }
    else if (S_ISSOCK(mode)) {
        printf("filetype socket \n");
    }    
    else{
        printf("unknown file type \n");
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("enter correct file name \n");
        return 1;
    }

    const char *file = argv[1];
    struct stat file_info;

    if(stat(file, &file_info) == -1){
        printf("error \n");
        return 1;
    }
    help_print_file_type(file_info.st_mode);
    help_print_perms(file_info.st_mode);

    printf("owner UID = %d \n",file_info.st_uid);
    printf("size of file in gytes is %ld \n",file_info.st_size);

    char modified[256];
    struct tm *ti = localtime(&file_info.st_mtime);
    if(ti == NULL){
        printf("err \n");
        return 1;
    }
     strftime(modified, sizeof(modified), "%Y-%m-%d %H:%M:%S", ti);
     printf("the file was modified lasr %s \n", modified);
    return 0;
}