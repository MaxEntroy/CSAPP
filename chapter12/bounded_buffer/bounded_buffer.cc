#include "bounded_buffer.h"
#include "mysem.h"

BoundedBuffer::BoundedBuffer(int size) : size_(size) {
  buf_.resize(size_);

  SEM_INIT(&mtx_, 1);
  SEM_INIT(&slots_, size_);
  SEM_INIT(&items_, 0);
}

void BoundedBuffer::produce(int item) {
  P(&slots_);
  P(&mtx_);
  buf_[rear_++%size_] = item;
  V(&mtx_);
  V(&items_);
}

int BoundedBuffer::consume() {
  int item = 0;
  P(&items_);
  P(&mtx_);
  item = buf_[front_++%size_];
  V(&mtx_);
  V(&slots_);
  return item;
}
