#pragma once

#include <unistd.h>
#include <arpa/inet.h>

namespace cal {

class TcpClient {
 public:
  TcpClient();

  TcpClient(const TcpClient&) = delete;
  TcpClient& operator=(const TcpClient&) = delete;

  virtual ~TcpClient() { close(clnt_sfd_); }

 public:
  void Init(const char* ip, int port);
  void Run();

 private:
  virtual void HandleIoEvent(int) = 0;

 private:
  int clnt_sfd_;
  struct sockaddr_in serv_addr_;
};

}  // namespace cal
