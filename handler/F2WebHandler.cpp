/**
 * @author Huahang Liu (x@zerus.co)
 * @date 2014-06-24
 */

#include "F2WebHandler.h"

#include <proxygen/httpserver/ResponseBuilder.h>

namespace {
using proxygen::HTTPMessage;
using proxygen::ResponseBuilder;
}

namespace zerus {
namespace f2web {
namespace handler {

void F2WebHandler::onRequest(std::unique_ptr<HTTPMessage> headers) noexcept {
}

void F2WebHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
  if (body_) {
    body_->prependChain(std::move(body));
  } else {
    body_ = std::move(body);
  }
}

void F2WebHandler::onEOM() noexcept {
  ResponseBuilder(downstream_)
    .status(200, "OK")
    .body(std::move(body_))
    .sendWithEOM();
}

void F2WebHandler::onUpgrade(proxygen::UpgradeProtocol protocol) noexcept {
}

void F2WebHandler::requestComplete() noexcept {
  delete this;
}

void F2WebHandler::onError(proxygen::ProxygenError err) noexcept {
  delete this;
}

} // namespace handler
} // namespace f2web
} // namespace zerus
