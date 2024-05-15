#ifndef MYSEMAPHORE_H
#define MYSEMAPHORE_H

#include <pthread.h>

typedef struct Sem {
    int count;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
} semaphore;

void up(semaphore *sem);
void down(semaphore *sem);
void init_semaphore(semaphore *sem, int initial_count);

#endif
