/**
 * @author Huahang Liu (x@zerus.co)
 * @date 2014-06-24
 */

#pragma once

#include "F2WebHandler.h"

#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

namespace zerus {
namespace f2web {
namespace handler {

class F2WebHandlerFactory : public proxygen::RequestHandlerFactory {
public:
  void onServerStart() noexcept override {
  }

  void onServerStop() noexcept override {
  }

  proxygen::RequestHandler* onRequest(
    proxygen::RequestHandler*,
    proxygen::HTTPMessage*) noexcept override {
    return new F2WebHandler();
  }
};

} // namespace handler
} // namespace f2web
} // namespace zerus
