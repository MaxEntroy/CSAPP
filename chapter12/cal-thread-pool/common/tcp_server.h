#pragma once

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

#include "bounded_buffer.h"

namespace cal {

class TcpServer {
 public:
  TcpServer();

  TcpServer(const TcpServer&) = delete;
  TcpServer& operator=(const TcpServer&) = delete;

  virtual ~TcpServer() { close(listen_sfd_); }

  void Init(int port, int backlog);
  void EventLoop();

 private:
  static void* WorkerThread(void*);
  virtual void HandleIoEvent(int) = 0;

 private:
  int listen_sfd_;
  struct sockaddr_in serv_addr_;
  BoundedBuffer task_que_{kQueSize};

  static constexpr int kThreadsNum = 8;
  static constexpr int kQueSize = 8;
};

}  // namespace cal
