/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>

#include <folly/dynamic.h>

#include <ABI44_0_0React/ABI44_0_0config/ABI44_0_0ReactNativeConfig.h>
#include <ABI44_0_0React/ABI44_0_0renderer/componentregistry/ComponentDescriptorRegistry.h>
#include <ABI44_0_0React/ABI44_0_0renderer/core/ShadowNode.h>
#include <ABI44_0_0React/ABI44_0_0renderer/uimanager/UIManagerDelegate.h>

namespace ABI44_0_0facebook {
namespace ABI44_0_0React {

// Temporary NativeModuleRegistry definition
using NativeModuleCallFn =
    std::function<folly::dynamic(const std::string &, const folly::dynamic &)>;

class NativeModuleRegistry {
 public:
  void registerModule(
      const std::string &moduleName,
      NativeModuleCallFn callFn) {
    modules_.emplace(moduleName, callFn);
  }

  folly::dynamic call(
      const std::string &moduleName,
      const std::string &methodName,
      const folly::dynamic &args) const {
    return modules_.at(moduleName)(methodName, args);
  }

 private:
  std::unordered_map<std::string, NativeModuleCallFn> modules_;
};

class UITemplateProcessor {
 public:
  static ShadowNode::Shared buildShadowTree(
      const std::string &jsonStr,
      int rootTag,
      const folly::dynamic &params,
      const ComponentDescriptorRegistry &componentDescriptorRegistry,
      const NativeModuleRegistry &nativeModuleRegistry,
      const std::shared_ptr<const ABI44_0_0ReactNativeConfig> ABI44_0_0ReactNativeConfig);

 private:
  static ShadowNode::Shared runCommand(
      const folly::dynamic &command,
      Tag rootTag,
      std::vector<SharedShadowNode> &nodes,
      std::vector<folly::dynamic> &registers,
      const ComponentDescriptorRegistry &componentDescriptorRegistry,
      const NativeModuleRegistry &nativeModuleRegistry,
      const std::shared_ptr<const ABI44_0_0ReactNativeConfig> ABI44_0_0ReactNativeConfig);
};
} // namespace ABI44_0_0React
} // namespace ABI44_0_0facebook
