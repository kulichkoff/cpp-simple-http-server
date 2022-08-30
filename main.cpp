#include <iostream>
#include <memory>
#include <evhttp.h>

int main() {
  if (!event_init()) {
    std::cerr << "Failed to init libevent." << std::endl;
    return -1;
  }

  const char *server_address = "127.0.0.1";
  std::uint16_t server_port = 5689;

  std::unique_ptr<evhttp, decltype(&evhttp_free)> server(
    evhttp_start(server_address, server_port), &evhttp_free);

  if (!server) {
    std::cerr << "Failed to init http server." << std::endl;
    return -1;
  }

  evhttp_set_gencb(server.get(), [](evhttp_request *req, void *) {
    auto *out_buf = evhttp_request_get_output_buffer(req);
    if (!out_buf) return;
    evbuffer_add_printf(out_buf,
                        "<html><body><center><h1>Hello World!</h1></center></body></html>");
    evhttp_send_reply(req, HTTP_OK, "", out_buf);
  }, nullptr);

  std::cout << "Server is starting!" << std::endl;
  if (event_dispatch() == -1) {
    std::cerr << "Failed to run message loop." << std::endl;
    return -1;
  }

  return 0;
}
