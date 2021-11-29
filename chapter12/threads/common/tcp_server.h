#pragma once

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

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
  virtual void HandleIoEvent(int) = 0;

 private:
  int listen_sfd_;
  struct sockaddr_in serv_addr_;
};

}  // namespace cal
