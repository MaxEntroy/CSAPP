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
  struct ThreadArgs {
    ThreadArgs(TcpServer* srv_in, int* sfd_in) : srv(srv_in), sfd(sfd_in) {}
    TcpServer* srv = nullptr;
    int* sfd = nullptr;
  };

  static void* ThreadWrapper(void*);
  virtual void HandleIoEvent(int) = 0;

 private:
  int listen_sfd_;
  struct sockaddr_in serv_addr_;
};

}  // namespace cal
