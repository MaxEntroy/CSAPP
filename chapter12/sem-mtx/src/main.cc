#include <pthread.h>

int counter = 0;

void* routine(void* arg);

int main(void) {
  return 0;
}

void* routine(void* arg) {
  int n = *(static_cast<int*>(arg));

  for (int i = 0; i < n; ++i) {
    ++counter;
  }

  return NULL;
}
