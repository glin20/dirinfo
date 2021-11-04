#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char path[100];
    if (argc > 1){
        strcpy(path, argv[1]);
    }
    else{
        printf("Enter Directory: \n");
        fgets(path, sizeof(path) - 1, stdin);
        int i = 0;
        while (path[i]) {
            i++;
        }
        path[i-1] = 0;
    }
    struct stat stats;
    DIR *directory;
    struct dirent *dirents;
    directory = opendir(path);
    if (!directory){
        printf("%s\n", strerror(errno));
    }
    if (directory){
        dirents = readdir(directory);
        while (dirents){
            printf("name: %s, type: %d\n", dirents -> d_name, dirents -> d_type);
            dirents = readdir(directory);
        }
        rewinddir(directory);

        dirents = readdir(directory);
        printf("\nDirectories:\n");
        while (dirents){
            if (dirents -> d_type == 4){
                printf("name: %s\n", dirents -> d_name);
            }
            dirents = readdir(directory);
        }
        rewinddir(directory);

        dirents = readdir(directory);
        printf("\nFiles:\n");
        unsigned long long i = 0;
        while (dirents){
            if (dirents -> d_type == 8){
                printf("name: %s\n", dirents -> d_name);
                stat(dirents -> d_name, &stats);
                i += stats.st_size;
            }
            dirents = readdir(directory);
        }
        printf("size: %llu\n", i);
        closedir(directory);
    }
    return 0;
}
