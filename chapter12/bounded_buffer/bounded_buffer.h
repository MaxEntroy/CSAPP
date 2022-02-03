#pragma once

#include <semaphore.h>
#include <vector>

class BoundedBuffer {
 public:
  explicit BoundedBuffer(int size);

  void produce(int item);
  int consume();

 private:
  int size_ = 0;
  std::vector<int> buf_;

  int front_ = 0;  // buf_[(front)%size_] is first item
  int rear_ = 0;   // buf_[(rear_-1)%size_] is last item

  sem_t mtx_;    // protects assess to buf
  sem_t slots_;  // counts available slots
  sem_t items_;  // counts available items
};
