#include <pthread.h>
#include <iostream>

#include "mysem.h"

int total = 200;
int person = 0;

sem_t io_mtx;
sem_t total_mtx;
sem_t person_mtx;
sem_t trans_mtx;

// trasfer m from src to dst
void* unsafe_transfer(void* arg);

// trasfer m from src to dst
void* safe_transfer(void* arg);

void uni_version();
void mul_version();
void safe_mul_version();

int main() {
  SEM_INIT(&io_mtx);
  SEM_INIT(&total_mtx);
  SEM_INIT(&person_mtx);
  SEM_INIT(&trans_mtx);
  //uni_version();
  mul_version();
  return 0;
}

void* unsafe_transfer(void* arg) {
  int trans = reinterpret_cast<intptr_t>(arg);
  P(&total_mtx);
  if (total < trans) {
    P(&io_mtx);
    std::cerr << "Not enough money." << std::endl;
    V(&io_mtx);
    V(&total_mtx);
    return NULL;
  }
  V(&total_mtx);

  P(&total_mtx);
  total -= trans;
  V(&total_mtx);

  P(&io_mtx);
  std::cout << "total:" << total <<  std::endl;
  V(&io_mtx);

  P(&person_mtx);
  person += trans;
  V(&person_mtx);

  P(&io_mtx);
  std::cout << "person:" << person << std::endl;
  V(&io_mtx);

  return NULL;
}

void* safe_transfer(void* arg) {
  int trans = reinterpret_cast<intptr_t>(arg);
  P(&trans_mtx);
  if (total < trans) {
    std::cerr << "Not enough money." << std::endl;
    return NULL;
  }

  total -= trans;

  std::cout << "total:" << total <<  std::endl;

  person += trans;

  std::cout << "person:" << person << std::endl;
  V(&trans_mtx);

  return NULL;
}

void uni_version() {
  int m = 100;
  unsafe_transfer(reinterpret_cast<void*>(m));

  m = 100;
  unsafe_transfer(reinterpret_cast<void*>(m));

  m = 100;
  unsafe_transfer(reinterpret_cast<void*>(m));
}

void mul_version() {
  pthread_t tid1, tid2, tid3;
  int m = 100;
  if (pthread_create(&tid1, NULL, safe_transfer, reinterpret_cast<void*>(m))) {
    std::cerr << "pthread_create failed." << std::endl;
  }

  if (pthread_create(&tid2, NULL, safe_transfer, reinterpret_cast<void*>(m))) {
    std::cerr << "pthread_create failed." << std::endl;
  }

  if (pthread_create(&tid3, NULL, safe_transfer, reinterpret_cast<void*>(m))) {
    std::cerr << "pthread_create failed." << std::endl;
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
}


