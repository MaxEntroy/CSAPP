package(default_visibility = ["//visibility:public"])
load("@rules_proto//proto:defs.bzl", "proto_library")

cc_proto_library(
  name = "cal_cc_proto",
  deps = [":cal_proto"]
)

proto_library(
  name = "cal_proto",
  srcs = [
    "cal_header.proto",
    "cal_req.proto",
    "cal_res.proto"
  ]
)
