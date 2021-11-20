//
// Created by liuso on 2021/11/20.
//
#ifndef SP_ENGINE_SERVICE_LOCATOR_H_
#define SP_ENGINE_SERVICE_LOCATOR_H_

#include <memory>
#include "sp_engine/platform/windows.h"

class ServiceLocator {
 public:
  static inline const std::unique_ptr<Window> &GetWindow() { return _window };

  static inline void Provide(Window *window) {
    if (nullptr != _window) {
      return;
    }

    _window = std::unique_ptr<Window>(window);
  }

 private:

  static inline std::unique_ptr<Window> _window = nullptr;
};

#endif //SP_ENGINE_SERVICE_LOCATOR_H_
