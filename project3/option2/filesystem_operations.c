// filesystem_operations.c
#include "filesystem_structs.h"

struct fs_t* fs;

void mapFileSystem(int fd) {
    if ((fs = mmap(NULL, FSSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
}

void unmapFileSystem() {
    munmap(fs, FSSIZE);
}

void formatFileSystem() {
    fs->superblock.freeblocks = NUM_BLOCKS;
    fs->superblock.freeinodes = NUM_INODES;
    memset(fs->fbl, 0, sizeof(fs->fbl));
    for (int i = 0; i < NUM_INODES; i++) {
        fs->inodes[i].flags = 0;
    }
}

void loadFileSystem() {
    // Add logic here if your filesystem supports loading from a persistent storage
}

void listFileSystemFiles() {
    for (int i = 0; i < NUM_INODES; i++) {
        if (fs->inodes[i].flags & FLAG_INUSE) {
            printf("File: %s\n", fs->inodes[i].name);
        }
    }
}

void addFileToFilesystem(char* filename) {
    FILE *fp;
    int inodeIndex = -1, block, i;
    char buf[BLOCK_WIDTH];
    char* baseName;

    baseName = strrchr(filename, '/');
    baseName = (baseName == NULL) ? filename : baseName + 1;

    for (i = 0; i < NUM_INODES; i++) {
        if ((fs->inodes[i].flags & FLAG_INUSE) && strcmp(fs->inodes[i].name, baseName) == 0) {
            printf("File already exists: %s\n", baseName);
            return;
        }
    }

    for (i = 0; i < NUM_INODES; i++) {
        if (!(fs->inodes[i].flags & FLAG_INUSE)) {
            inodeIndex = i;
            break;
        }
    }

    if (inodeIndex == -1) {
        printf("No free inodes.\n");
        return;
    }

    fp = fopen(filename, "rb");
    if (!fp) {
        printf("File not found: %s\n", filename);
        return;
    }

    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int blocksNeeded = (fileSize + BLOCK_WIDTH - 1) / BLOCK_WIDTH;

    for (i = 0; i < blocksNeeded; i++) {
        block = allocateBlock();
        if (block == -1) {
            printf("No free blocks.\n");
            fclose(fp);
            return;
        }
        int readSize = fread(buf, 1, BLOCK_WIDTH, fp);
        memcpy(fs->blocks[block].data, buf, readSize);
        fs->inodes[inodeIndex].blocks[i] = block;
    }

    fs->inodes[inodeIndex].flags |= FLAG_INUSE;
    strncpy(fs->inodes[inodeIndex].name, baseName, sizeof(fs->inodes[inodeIndex].name) - 1);
    fs->inodes[inodeIndex].nblocks = blocksNeeded;
    fs->inodes[inodeIndex].size = fileSize;

    fclose(fp);
}

void removeFileFromFilesystem(char* filename) {
    for (int i = 0; i < NUM_INODES; i++) {
        if ((fs->inodes[i].flags & FLAG_INUSE) && strcmp(fs->inodes[i].name, filename) == 0) {
            for (int j = 0; j < fs->inodes[i].nblocks; j++) {
                int block = fs->inodes[i].blocks[j];
                fs->fbl[block / 8] &= ~(1 << (block % 8));
                fs->superblock.freeblocks++;
            }
            fs->inodes[i].flags &= ~FLAG_INUSE;
            printf("File removed: %s\n", filename);
            break;
        }
    }
}

void extractFileFromFilesystem(char* filename) {
    for (int i = 0; i < NUM_INODES; i++) {
        if ((fs->inodes[i].flags & FLAG_INUSE) && strcmp(fs->inodes[i].name, filename) == 0) {
            for (int j = 0; j < fs->inodes[i].nblocks - 1; j++) {
                int block = fs->inodes[i].blocks[j];
                fwrite(fs->blocks[block].data, 1, BLOCK_WIDTH, stdout);
            }

            int lastBlock = fs->inodes[i].blocks[fs->inodes[i].nblocks - 1];
            int lastBlockSize = fs->inodes[i].size % BLOCK_WIDTH;
            if (lastBlockSize == 0 && fs->inodes[i].nblocks > 0) {
                lastBlockSize = BLOCK_WIDTH;
            }
            fwrite(fs->blocks[lastBlock].data, 1, lastBlockSize, stdout);
            break;
        }
    }
}

int allocateBlock() {
    for(int i = 0; i < NUM_BLOCKS; i++) {
        for(int j = 0; j < 8; j++) {
            if((fs->fbl[i] & (1 << j)) == 0) {
                fs->fbl[i] |= 1 << j;
                fs->superblock.freeblocks--;
                return i * 8 + j;
            }
        }
    }
    return -1;
}
