/**
 * @author Huahang Liu (x@zerus.co)
 * @date 2014-06-24
 */

#include "zerus/f2web/handler/F2WebHandler.h"
#include "zerus/f2web/handler/F2WebHandlerFactory.h"

#include <proxygen/httpserver/HTTPServer.h>

#include <glog/logging.h>

#include <gflags/gflags.h>

#include <chrono>
#include <stdlib.h>
#include <thread>

int main(int argc, char** argv) {
  using folly::SocketAddress;
  using proxygen::HTTPServer;
  using proxygen::HTTPServerOptions;
  using proxygen::RequestHandlerChain;
  using zerus::f2web::handler::F2WebHandler;
  using zerus::f2web::handler::F2WebHandlerFactory;

  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  HTTPServerOptions options;
  options.threads = 8;
  options.idleTimeout = std::chrono::milliseconds(60000);
  options.shutdownOn = {SIGINT, SIGTERM};
  options.enableContentCompression = true;
  options.handlerFactories = RequestHandlerChain()
      .addThen<F2WebHandlerFactory>()
      .build();

  std::vector<HTTPServer::IPConfig> IPs = {
    {SocketAddress("127.0.0.1", 8888, true), HTTPServer::Protocol::HTTP},
  };

  HTTPServer server(std::move(options));
  server.bind(IPs);

  // Start HTTPServer mainloop in a separate thread
  std::thread t([&] () {
    server.start();
  });

  t.join();
  return 0;

  return EXIT_SUCCESS;
}
