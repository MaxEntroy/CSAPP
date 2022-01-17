#include <semaphore.h>
#include <stdint.h>
#include <pthread.h>
#include <iostream>

int counter = 0;

sem_t mtx;

#define P(s) sem_wait(s)
#define V(s) sem_post(s)

void* routine(void* arg);

int main(void) {
  int n = 100000;

  sem_init(&mtx, 0 ,1);

  pthread_t tid1, tid2;
  if (pthread_create(&tid1, NULL, routine, reinterpret_cast<void*>(n))) {
    std::cerr << "pthread_create failed.";
  }
  if (pthread_create(&tid2, NULL, routine, reinterpret_cast<void*>(n))) {
    std::cerr << "pthread_create failed.";
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  std::cout << "counter:" << counter << std::endl;
  return 0;
}

void* routine(void* arg) {
  intptr_t n = reinterpret_cast<intptr_t>(arg);

  for (int i = 0; i < n; ++i) {
    P(&mtx);
    ++counter;
    V(&mtx);
  }

  return NULL;
}
