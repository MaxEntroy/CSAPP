#include "app/cal_client.h"

constexpr char kIp[] = "localhost";
constexpr int kPort = 54321;

int main(int argc, char* argv[]) {
  cal::CalClient client;

  client.Init(kIp, kPort);
  client.Run();

  return 0;
}
