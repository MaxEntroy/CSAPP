package(default_visibility = ["//visibility:public"])

cc_library(
  name = "tools",
  srcs = [
    "err.cc",
    "io_aux.cc"
  ],
  hdrs = [
    "err.h",
    "io_aux.h"
  ]
)

cc_library(
  name = "tcp_server",
  srcs = [
    "tcp_server.cc"
  ],
  hdrs = [
    "tcp_server.h"
  ],
  deps = [
    ":tools",
    ":task_queue"
  ]
)

cc_library(
  name = "tcp_client",
  srcs = [
    "tcp_client.cc",
  ],
  hdrs = [
    "tcp_client.h"
  ],
  deps = [
    ":tools"
  ]
)

cc_library(
  name = "task_queue",
  srcs = [
    "bounded_buffer.cc"
  ],
  hdrs = [
    "bounded_buffer.h",
    "mysem.h"
  ]
)
