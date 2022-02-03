#include "tcp_server.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "err.h"

namespace cal {

TcpServer::TcpServer() : listen_sfd_(socket(PF_INET, SOCK_STREAM, 0)) {
  if(listen_sfd_ == -1) {
    perr_handling("socket", "error");
  }

  memset(&serv_addr_, 0, sizeof(serv_addr_));
}

void TcpServer::Init(int port, int backlog) {
  // set reuse addr
  int option = 1;
  socklen_t optlen = sizeof(option);
  int ret = setsockopt(listen_sfd_, SOL_SOCKET, SO_REUSEADDR, &option, optlen);
  if (ret == -1) {
    perr_handling("setsockopt", "error");
  }

  // bind
  serv_addr_.sin_family = AF_INET;
  serv_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr_.sin_port = htons(port);

  ret = bind(listen_sfd_, (struct sockaddr*) &serv_addr_, sizeof(serv_addr_));
  if(ret == -1) {
    perr_handling("bind", "error");
  }

  // listen
  ret = listen(listen_sfd_, backlog);
  if(ret == -1) {
    perr_handling("listen", "error");
  }
}

void TcpServer::EventLoop() {
  struct sockaddr_in clnt_addr;
  memset(&clnt_addr, 0, sizeof(clnt_addr));
  socklen_t clnt_addr_len = 0;
  pthread_t tid = 0;

  // serving-loop
  while(1) {
    printf("Tcp server[localhost:%d] waiting...\n", ntohs(serv_addr_.sin_port));

    // accept
    int* clnt_sfd = new int{};
    *clnt_sfd = accept(listen_sfd_, (struct sockaddr*) &clnt_addr, &clnt_addr_len);
    if (*clnt_sfd == -1) {
      continue;
    }
    printf("[%s:%d] connected.\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
    ThreadArgs* args = new ThreadArgs(this, clnt_sfd);
    if (pthread_create(&tid, nullptr, ThreadWrapper, static_cast<void*>(args))) {
      perr_handling("pthread_create", "error");
    }
  }
}

void* TcpServer::ThreadWrapper(void* args) {
  pthread_detach(pthread_self());

  ThreadArgs* t_args = static_cast<ThreadArgs*>(args);
  t_args->srv->HandleIoEvent(*t_args->sfd);

  close(*t_args->sfd);
  delete t_args->sfd;
  delete t_args;

  return nullptr;
}

}  // namespace cal
