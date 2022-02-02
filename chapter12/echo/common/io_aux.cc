#include "io_aux.h"

#include <errno.h>
#include <unistd.h>

#include <iostream>

namespace cal {

void io_read_n(int fd, char buf[], int n) {
  int ready = 0;
  while(ready < n) {
    int nread = read(fd, buf + ready, n - ready);
    if (nread == -1) {
      if (errno == EINTR)
        nread = 0;
      else
        return;
    } else if (nread == 0)
      break;
    else
      ready += nread;
  }
}

void io_write_n(int fd, char buf[], int n) {
  int ready = 0;
  while(ready < n) {
    int nwrite = write(fd, buf + ready, n - ready);
    if (nwrite == -1) {
      if (errno == EAGAIN)
        nwrite = 0;
      else
        return;
    } else if (nwrite == 0)
      break;
    else
      ready += nwrite;
  }
}

}  // namespace cal
