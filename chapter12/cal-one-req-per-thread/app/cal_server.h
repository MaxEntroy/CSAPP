#pragma once

#include "common/tcp_server.h"

namespace cal {

class CalReq;
class CalRes;

class CalServer : public TcpServer {
 public:
  CalServer() = default;

  CalServer(const CalServer&) = delete;
  CalServer& operator=(const CalServer&) = delete;

 private:
   void HandleIoEvent(int) override;

   void RecvReq(int clnt_sfd, CalReq* req);
   void DoCal(const CalReq& req, CalRes* res);
   void SendRes(int clnt_sfd, const CalRes& res);
};

}; // namespace cal
