#pragma once

#include <semaphore.h>
#include <pthread.h>
#include <vector>

class BoundedBuffer {
 public:
  explicit BoundedBuffer(int size);

  BoundedBuffer(const BoundedBuffer&) = delete;
  BoundedBuffer& operator=(const BoundedBuffer&) = delete;

  ~BoundedBuffer();

  void produce(int item);
  int consume();

 private:
  int size_ = 0;
  std::vector<int> buf_;

  int front_ = 0;  // buf_[(front)%size_] is first item
  int rear_ = 0;   // buf_[(rear_-1)%size_] is last item

  pthread_mutex_t mtx_;    // protects assess to buf
  pthread_cond_t not_empty_;  // counts available slots
  pthread_cond_t not_full_;   // counts available items
};
