#include "app/cal_server.h"

#include "common/io_aux.h"

#include "proto/cal_req.pb.h"
#include "proto/cal_res.pb.h"

namespace cal {

void CalServer::HandleIoEvent(int clnt_sfd) {
  CalReq req;
  CalRes res;
  RecvReq(clnt_sfd, &req);

  DoCal(req, &res);

  SendRes(clnt_sfd, res);
}

void CalServer::RecvReq(int clnt_sfd, CalReq* req) {
  // recv cal header
  constexpr int kHeaderLen = 5;
  std::string header_buf(kHeaderLen, ' ');
  io_read_n(clnt_sfd, &header_buf[0], kHeaderLen); // bug: clnt_sfd should be non-blocking
  CalReqHeader req_header;
  req_header.ParseFromString(header_buf);

  // recv cal req
  int req_len = req_header.msg_len();
  std::string req_buf(req_len, ' ');
  io_read_n(clnt_sfd, &req_buf[0], req_len);
  req->ParseFromString(req_buf);
}

void CalServer::DoCal(const CalReq& req, CalRes* res) {
  res->set_seqno(req.seqno());

  int sz = req.opnd_arr_size();
  if (sz < 2) {
    res->set_result(0);
    return;
  }

  int ret = req.opnd_arr(0);
  switch(req.optr()[0]) {
    case '+' : {
      for(int i = 1; i < sz; ++i)
        ret += req.opnd_arr(i);
      res->set_result(ret);
      break;
    }
    case '-' : {
      for(int i = 1; i < sz; ++i)
        ret -= req.opnd_arr(i);
      res->set_result(ret);
      break;
    }
    case '*' : {
      for(int i = 1; i < sz; ++i)
        ret *= req.opnd_arr(i);
      res->set_result(ret);
      break;
    }
    case '/' : {
      for(int i = 1; i < sz; ++i)
        ret /= req.opnd_arr(i);
      res->set_result(ret);
      break;
    }
  }
}

void CalServer::SendRes(int clnt_sfd, const CalRes& res) {
  std::string res_buf;
  res.SerializeToString(&res_buf);

  cal::CalResHeader res_header;
  res_header.set_msg_len(res_buf.size());
  std::string header_buf;
  res_header.SerializeToString(&header_buf);

  // send cal header
  io_write_n(clnt_sfd, header_buf.data(), header_buf.size());

  // send cal res
  io_write_n(clnt_sfd, res_buf.data(), res_buf.size());
}

} // namespace cal
