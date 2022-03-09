/**
 * Author: Valkryst
 *
 * Purpose
 *      A set of convenience functions to allow for easier use of threads.
 */
#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

pthread_t *createThread(void *(*function) (void *), void *functionArguments);
int destroyThread(pthread_t *thread);

#endif
