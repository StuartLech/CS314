#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MySemaphore.h"

#define THINKING 0
#define HUNGRY 1
#define EATING 2

int N;
int *state;
semaphore mutex;
semaphore *s;

void think(int i);
void eat(int i);
void take_forks(int i);
void put_forks(int i);
void test(int i);  // Adding function declaration here

void test(int i) {
    if (state[i] == HUNGRY && state[(i+N-1)%N] != EATING && state[(i+1)%N] != EATING) {
        state[i] = EATING;
        up(&s[i]);
    }
}

void think(int i) {
    printf("Philosopher %d is thinking.\n", i);
}

void eat(int i) {
    printf("Philosopher %d is eating.\n", i);
}

void take_forks(int i) {
    down(&mutex);
    state[i] = HUNGRY;
    test(i);
    up(&mutex);
    down(&s[i]);
}

void put_forks(int i) {
    down(&mutex);
    state[i] = THINKING;
    test((i+N-1)%N);
    test((i+1)%N);
    up(&mutex);
}

void *philosopher(void *num) {
    int *i = (int *) num;
    int eat_count = 0;

    while (eat_count < 2) {
        think(*i);
        take_forks(*i);
        eat(*i);
        put_forks(*i);
        eat_count++;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_philosophers>\n", argv[0]);
        return 1;
}
 N = atoi(argv[1]);
    state = malloc(N * sizeof(int));
    s = malloc(N * sizeof(semaphore));

    init_semaphore(&mutex, 1);

    for (int i = 0; i < N; i++) {
        init_semaphore(&s[i], 0);
        state[i] = THINKING;
    }

    pthread_t *threads = malloc(N * sizeof(pthread_t));

    for (int i = 0; i < N; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&threads[i], NULL, philosopher, arg);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    free(state);
    free(s);
    free(threads);

    return 0;
}
