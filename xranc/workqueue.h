/*
 * Copyright 2019-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Multithreaded work queue.
 * Copyright (c) 2012 Ronald Bennett Cemer
 * This software is licensed under the BSD license.
 * See the accompanying LICENSE.txt for details.
 */

#ifndef WORKQUEUE_H
#define WORKQUEUE_H

#include <pthread.h>

typedef struct worker {
    pthread_t thread;
    int terminate;
    struct workqueue *workqueue;
    struct worker *prev;
    struct worker *next;
} worker_t;

typedef struct job {
    void (*job_function)(struct job *job);
    void *user_data;
    struct job *prev;
    struct job *next;
} job_t;

typedef struct workqueue {
    struct worker *workers;
    struct job *waiting_jobs;
    pthread_mutex_t jobs_mutex;
    pthread_cond_t jobs_cond;
} workqueue_t;

int workqueue_init(workqueue_t *workqueue, int numWorkers);

void workqueue_shutdown(workqueue_t *workqueue);

void workqueue_add_job(workqueue_t *workqueue, job_t *job);

#endif  /* #ifndef WORKQUEUE_H */
