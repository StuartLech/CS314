#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

void scanDir(const char *dirName, int binWidth, int *histogram) {
    struct dirent *entry;
    struct stat fileStat;
    DIR *dir = opendir(dirName);

    if (dir == NULL) {
        perror("Unable to read directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirName, entry->d_name);
        
        if (stat(path, &fileStat) < 0) {
            continue;
        }

        if (S_ISDIR(fileStat.st_mode)) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            scanDir(path, binWidth, histogram);
        } else if (S_ISREG(fileStat.st_mode)) {
            int bin = fileStat.st_size / binWidth;
            histogram[bin]++;
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <directory> <bin_width>\n", argv[0]);
        return 1;
    }

    const char *dirName = argv[1];
    int binWidth = atoi(argv[2]);

    int *histogram = calloc(1024, sizeof(int)); 
    scanDir(dirName, binWidth, histogram);

   
    for (int i = 0; i < 1024; i++) {
        if (histogram[i] > 0) {
            printf("%d - %d: %d\n", i * binWidth, (i + 1) * binWidth - 1, histogram[i]);
        }
    }

    free(histogram);

    return 0;
}
