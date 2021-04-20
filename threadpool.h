#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond_var;

extern int activeThreads;


typedef struct threadpool_t{
    pthread_t *threads;
    int nthreads;
}Threadpool;


/**
 * @function thread_func
 * @brief The function the threads will execute
 * @param args The arguments of threadpool
 * @return void
 */
void *thread_func(void *args);


/**
 * @function create_threadpool
 * @brief It creates the threadpool based on the given threads
 * @param nthreads The number of threads to assign to threadpool
 * @return A pointer to a Threadpool struct
 */
Threadpool *create_threadpool(int nthreads);

#endif