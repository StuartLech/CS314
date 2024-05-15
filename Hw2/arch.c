#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct header {
    char name[256];
    int size;
};

void addFile(const char *archiveName, const char *fileName) {
    FILE *archive = fopen(archiveName, "ab");
    if (archive == NULL) {
        perror("Error opening archive file");
        exit(1);
    }

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening input file");
        fclose(archive);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    if (size == -1) {
        perror("Error determining file size");
        fclose(file);
        fclose(archive);
        exit(1);
    }
    fseek(file, 0, SEEK_SET);

    struct header h;
    strncpy(h.name, fileName, 255);
    h.name[255] = '\0';
    h.size = size;

    fwrite(&h, sizeof(struct header), 1, archive);

    char *buffer = malloc(size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        fclose(archive);
        exit(1);
    }

    fread(buffer, size, 1, file);
    fwrite(buffer, size, 1, archive);

    free(buffer);
    fclose(file);
    fclose(archive);
}

void listFiles(const char *archiveName) {
    FILE *archive = fopen(archiveName, "rb");
    if (archive == NULL) {
        perror("Error opening archive file");
        exit(1);
    }

    struct header h;

    while (fread(&h, sizeof(struct header), 1, archive)) {
        printf("%s\n", h.name);
        fseek(archive, h.size, SEEK_CUR);
    }

    fclose(archive);
}

void extractFile(const char *archiveName, const char *fileName) {
    FILE *archive = fopen(archiveName, "rb");
    if (archive == NULL) {
        perror("Error opening archive file");
        exit(1);
    }

    struct header h;

    while (fread(&h, sizeof(struct header), 1, archive)) {
        if (strcmp(h.name, fileName) == 0) {
            char *buffer = malloc(h.size);
            if (buffer == NULL) {
                perror("Memory allocation failed");
                fclose(archive);
                exit(1);
            }

            fread(buffer, h.size, 1, archive);
            FILE *file = fopen(fileName, "wb");
            if (file == NULL) {
                perror("Error opening file for writing");
                free(buffer);
                fclose(archive);
                exit(1);
            }

            fwrite(buffer, h.size, 1, file);

            free(buffer);
            fclose(file);
            break;
        } else {
            fseek(archive, h.size, SEEK_CUR);
        }
    }

    fclose(archive);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./arch <-a|-l|-e> <archive_name> [file_name]\n");
        exit(1);
    }

    const char *option = argv[1];
    const char *archiveName = argv[2];
    const char *fileName = argc > 3 ? argv[3] : NULL;

    if (strcmp(option, "-a") == 0 && fileName) {
        addFile(archiveName, fileName);
    } else if (strcmp(option, "-l") == 0) {
        listFiles(archiveName);
    } else if (strcmp(option, "-e") == 0 && fileName) {
        extractFile(archiveName, fileName);
    } else {
        printf("Invalid usage.\n");
    }

    return 0;
}
