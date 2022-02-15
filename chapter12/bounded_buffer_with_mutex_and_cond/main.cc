#include <pthread.h>
#include <unistd.h>

#include <iostream>

#include "bounded_buffer.h"

constexpr int kProducerNum = 1;
constexpr int kConsumerNum = 2;

constexpr int kBufferSize = 8;
BoundedBuffer buffer(kBufferSize);

void* producer(void*);
void* consumer(void*);

pthread_mutex_t io_mtx;

int main(void) {
  pthread_t producers[kProducerNum];
  pthread_t consumers[kConsumerNum];

  // creating threads
  for (int i = 0; i < kProducerNum; ++i) {
    if (pthread_create(producers + i, nullptr, producer, nullptr)) {
      std::cerr << "pthread_create failed." << std::endl;
      return -1;
    }
  }
  for (int i = 0; i < kConsumerNum; ++i) {
    if (pthread_create(consumers + i, nullptr, consumer, nullptr)) {
      std::cerr << "pthread_create failed." << std::endl;
      return -1;
    }
  }

  // detached threads is also ok, but we can't see the print.
  for (int i = 0; i < kProducerNum; ++i) {
    pthread_join(producers[i], nullptr);
  }
  for (int i = 0; i < kConsumerNum; ++i) {
    pthread_join(consumers[i], nullptr);
  }
  return 0;
}

void* producer(void*) {
  while (true) {
    pthread_mutex_lock(&io_mtx);
    std::cout << "[Producer]Please produce an item(input a nonnegative number): ";
    pthread_mutex_unlock(&io_mtx);
    int item = 0;
    std::cin >> item;
    buffer.produce(item);
    sleep(1);
  }
  return nullptr;
}

void* consumer(void*) {
  while (true) {
    int item = buffer.consume();
    pthread_mutex_lock(&io_mtx);
    std::cout << "[" << pthread_self() << "] Consume an item: " << item << std::endl;
    pthread_mutex_unlock(&io_mtx);
  }
  return nullptr;
}
