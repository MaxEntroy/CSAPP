#pragma once

#include "common/tcp_client.h"

namespace cal {

class CalReq;
class CalRes;

class CalClient : public TcpClient {
 public:
  CalClient() = default;

  CalClient(const CalClient&) = delete;
  CalClient& operator=(const CalClient&) = delete;

 private:
  void HandleIoEvent(int) override;

  void MakeReq(CalReq* req);
  void SendReq(int clnt_sfd, const CalReq& req);
  void RecvRes(int clnt_sfd, CalRes* res);
  void ShowRes(const CalRes& res);

};

} // namespace cal
