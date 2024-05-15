// filesystem_manager.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "filesystem_structs.h"

int checkIfNewFilesystem(int fd);
void showUsageAndExit(char* programName);

int main(int argc, char** argv) {
    int opt;
    int listFiles = 0, addFile = 0, removeFile = 0, extractFile = 0;
    char *fileToAdd = NULL, *fileToRemove = NULL, *fileToExtract = NULL, *fsName = NULL;
    int fileDescriptor = -1, isNewFilesystem = 0, isFsNameProvided = 0;

    while ((opt = getopt(argc, argv, "la:r:e:f:")) != -1) {
        switch (opt) {
            case 'l':
                listFiles = 1;
                break;
            case 'a':
                addFile = 1;
                fileToAdd = strdup(optarg);
                break;
            case 'r':
                removeFile = 1;
                fileToRemove = strdup(optarg);
                break;
            case 'e':
                extractFile = 1;
                fileToExtract = strdup(optarg);
                break;
            case 'f':
                isFsNameProvided = 1;
                fsName = strdup(optarg);
                break;
            default:
                showUsageAndExit(argv[0]);
        }
    }

    if (!isFsNameProvided) {
        showUsageAndExit(argv[0]);
    }

    if ((fileDescriptor = open(fsName, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    } else {
        if (checkIfNewFilesystem(fileDescriptor)) {
            isNewFilesystem = 1;
        }
        if (isNewFilesystem) {
            if (lseek(fileDescriptor, FSSIZE-1, SEEK_SET) == -1) {
                perror("seek failed");
                exit(EXIT_FAILURE);
            } else {
                if (write(fileDescriptor, "\0", 1) == -1) {
                    perror("write failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    mapFileSystem(fileDescriptor);

    if (isNewFilesystem) {
        formatFileSystem();
    }

    loadFileSystem();

    if (addFile) {
        addFileToFilesystem(fileToAdd);
        free(fileToAdd);
    }

    if (removeFile) {
        removeFileFromFilesystem(fileToRemove);
        free(fileToRemove);
    }

    if (extractFile) {
        extractFileFromFilesystem(fileToExtract);
        free(fileToExtract);
    }

    if (listFiles) {
        listFileSystemFiles();
    }

    unmapFileSystem();

    free(fsName);
    return 0;
}

int checkIfNewFilesystem(int fd) {
    struct stat stats;
    fstat(fd, &stats);
    return stats.st_size == 0;
}

void showUsageAndExit(char* programName) {
    fprintf(stderr, "Usage %s [-l] [-a path] [-r path] [-e path] -f name\n", programName);
    exit(EXIT_FAILURE);
}
