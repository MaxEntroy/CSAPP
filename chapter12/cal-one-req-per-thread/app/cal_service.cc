#include "app/cal_server.h"

constexpr int kPort = 54321;
constexpr int kBacklog = 10;

int main(int argc, char* argv[]) {
  cal::CalServer server;
  server.Init(kPort, kBacklog);
  server.EventLoop();

  return 0;
}
