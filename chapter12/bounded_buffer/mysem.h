#pragma once

#include <semaphore.h>

// SEM_INT(&mtx), P(&mtx) and V(&mtx)
#define SEM_INIT(s, value) sem_init(s, 0, value)
#define P(s) sem_wait(s)
#define V(s) sem_post(s)

