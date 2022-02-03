package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "CalServer",
  srcs = [
    "cal_service.cc"
  ],
  deps = [
    ":cal_server"
  ]
)

cc_binary(
  name = "CalClient",
  srcs = [
    "cal_client_stub.cc"
  ],
  deps = [
    ":cal_client"
  ]
)

cc_library(
  name = "cal_server",
  srcs = [
    "cal_server.cc"
  ],
  hdrs = [
    "cal_server.h"
  ],
  deps = [
    "//common:tools",
    "//common:tcp_server",
    "//proto:cal_cc_proto"
  ]
)

cc_library(
  name = "cal_client",
  srcs = [
    "cal_client.cc",
  ],
  hdrs = [
    "cal_client.h"
  ],
  deps = [
    "//common:tools",
    "//common:tcp_client",
    "//proto:cal_cc_proto"
  ]
)
