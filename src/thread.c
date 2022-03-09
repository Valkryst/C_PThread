/**
 * Author: Valkryst
 *
 * Purpose
 *      A set of convenience functions to allow for easier use of threads.
 *
 * Notes
 *      * All threads are created with their detatch state set to
 *        PTHREAD_CREATE_JOINABLE, According to the documentation (See sources
 *        #1 & #2).
 *
 *        Because of this, I do not believe that we need to specifically create
 *        and set a thread attribute when creating our threads, but it is better
 *        to be on the safe side. Especially when the assignment specifically
 *        says to ensure that the threads cannot be detatched.
 *
 * Sources
 *      1. https://linux.die.net/man/3/pthread_mutexattr_settype
 */
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "logger.h"
#include "thread.h"

/**
 * Allocates a pthread attribute and sets its detatch state to
 * PTHREAD_CREATE_JOINABLE.
 *
 * @return The pthread attribute or NULL if an error occurred.
 */
pthread_attr_t *createThreadAttribute() {
    pthread_attr_t *attribute = (pthread_attr_t*) malloc(sizeof(pthread_attr_t));
    if (NULL == attribute) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not allocate memory for attribute."
		);
        return NULL;
    }

    if (0 != (errno = pthread_attr_init(attribute))) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not initialize attribute."
		);
        free(attribute);
        return NULL;
    }

    if (0 != (errno = pthread_attr_setdetachstate(attribute, PTHREAD_CREATE_JOINABLE))) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not set detatch state."
		);
        free(attribute);
        return NULL;
    }

    return attribute;
}

/**
 * Destroys and frees a pthread attribute.
 *
 * @param attribute A pthread attribute.
 * @return 0 if successful or 1 if an error occurred.
 */
int destroyThreadAttribute(pthread_attr_t *attribute) {
    if (NULL == attribute) {
        printError(
			0,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not destroy attribute as it is null."
		);
        return 1;
    }

    if (0 != (errno = pthread_attr_destroy(attribute))) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not destroy attribute."
		);
        return 1;
    }

    free(attribute);
    return 0;
}

/**
 * Allocates and starts a thread with the detatch state set to
 * PTHREAD_CREATE_JOINABLE.
 *
 * @param function A function for the thread to run.
 * @param functionArguments Arguments to pass to the function.
 * @return The thread or NULL if an error occurred.
 */
pthread_t *createThread(void *function(), void *functionArguments) {
    pthread_attr_t *attribute = createThreadAttribute();
    if (NULL == attribute) {
        printError(
			0,
			__FILE__,
			__PRETTY_FUNCTION__,
			NULL
		);
        return NULL;
    }

    pthread_t *thread = (pthread_t*) malloc(sizeof(pthread_t));
    if (NULL == thread) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not allocate memory for thread."
			);

        if (0 != destroyThreadAttribute(attribute)) {
            printError(
				0,
				__FILE__,
				__PRETTY_FUNCTION__,
				NULL)
			;
        }

        free(thread);
        return NULL;
    }

    if (0 != (errno = pthread_create(thread, attribute, function, functionArguments))) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not create thread."
		);

        if (0 != destroyThreadAttribute(attribute)) {
            printError(
				0,
				__FILE__,
				__PRETTY_FUNCTION__,
				NULL
			);
        }

        free(thread);
        return NULL;
    }

    if (0 != destroyThreadAttribute(attribute)) {
        printError(
			0,
			__FILE__,
			__PRETTY_FUNCTION__,
			NULL
		);
        free(thread);
        return NULL;
    }

    return thread;
}

/**
 * Joins and frees a thread.
 *
 * @param thread A thread.
 * @return 0 if successful or 1 if an error occurred.
 */
int destroyThread(pthread_t *thread) {
    if (NULL == thread) {
        printError(
			0,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not destroy thread as it is null."
		);
        return 1;
    }

    if (0 != (errno = pthread_join(*thread, NULL))) {
        printError(
			errno,
			__FILE__,
			__PRETTY_FUNCTION__,
			"Could not join thread."
		);
        return 1;
    }

    free(thread);
    return 0;
}