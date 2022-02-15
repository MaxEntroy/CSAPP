#include "bounded_buffer.h"

#include <assert.h>

BoundedBuffer::BoundedBuffer(int size) : size_(size) {
  buf_.resize(size_);

  assert(pthread_mutex_init(&mtx_, nullptr) == 0);
  assert(pthread_cond_init(&not_empty_, nullptr) == 0);
  assert(pthread_cond_init(&not_full_, nullptr) == 0);
}

BoundedBuffer::~BoundedBuffer() {
  assert(pthread_mutex_destroy(&mtx_) == 0);
  assert(pthread_cond_destroy(&not_empty_) == 0);
  assert(pthread_cond_destroy(&not_full_) == 0);
}

void BoundedBuffer::produce(int item) {
  pthread_mutex_lock(&mtx_);
  while((rear_ + 1) % size_ == front_) {
    pthread_cond_wait(&not_full_, &mtx_);
  }
  buf_[rear_++%size_] = item;
  pthread_mutex_unlock(&mtx_);
  pthread_cond_signal(&not_empty_);
}

int BoundedBuffer::consume() {
  int item = 0;
  pthread_mutex_lock(&mtx_);
  while (front_ == rear_) {
    pthread_cond_wait(&not_empty_, &mtx_);
  }
  item = buf_[front_++%size_];
  pthread_mutex_unlock(&mtx_);
  pthread_cond_signal(&not_full_);
  return item;
}
