/**
 * @author Huahang Liu (x@zerus.co)
 * @date 2014-06-24
 */

#pragma once

#include <proxygen/httpserver/RequestHandler.h>

#include <folly/Memory.h>

#include <memory>

namespace zerus {
namespace f2web {
namespace handler {

class F2WebHandler : public proxygen::RequestHandler {
public:
  void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;

  void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

  void onEOM() noexcept override;

  void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;

  void requestComplete() noexcept override;

  void onError(proxygen::ProxygenError err) noexcept override;

private:
  std::unique_ptr<folly::IOBuf> body_;
};

} // namespace zerus
} // namespace f2web
} // namespace zerus
