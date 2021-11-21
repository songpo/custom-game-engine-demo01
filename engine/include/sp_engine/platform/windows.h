//
// Created by liuso on 2021/11/20.
//

#pragma once

#include <any>
#include <tuple>
#include <string>
#include <unordered_map>

namespace SP {

enum SurfaceArgs {
  INSTANCE,
  ALLOCATORS,
  OUT_SURFACE
};

struct WindowData {
  std::string title;
  uint32_t width;
  uint32_t height;
};

class Window {
 public:
  virtual void OpenWindow(WindowData) = 0;
  virtual bool Update() = 0;

  virtual std::pair<int, int> GetWindowExtents() = 0;
  virtual void RequestDrawSurface(std::unordered_map<SurfaceArgs, std::any>) = 0;
};

}


