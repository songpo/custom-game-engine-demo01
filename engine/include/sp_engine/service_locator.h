//
// Created by liuso on 2021/11/20.
//

#include <memory>
#include "sp_engine/platform/windows.h"

namespace SP {

  class ServiceLocator {
   public:
    static inline const std::unique_ptr<Window> &GetWindow() { return _window; };

    static inline void Provide(Window *window) {
      if (nullptr != _window) {
        return;
      }

      _window = std::unique_ptr<Window>(window);
    }

    static inline void ShutdownServices() {
      // ensure we shut down services in the correct order
      // usually opposite order of initialized.
      shutdownWindow();
    }

   private:
    static inline void shutdownWindow() {
      _window.reset();
      _window = nullptr;
    }

    static inline std::unique_ptr<Window> _window = nullptr;
  };

}

