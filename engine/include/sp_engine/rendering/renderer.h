//
// Created by liuso on 2021/11/21.
//
#pragma once

#include <string>

namespace SP {

struct RendererSettings {
  std::string ApplicationName;
};

class Renderer {

 public:
  virtual void Init(RendererSettings settings) = 0;
  virtual void Shutdown() = 0;
  virtual void RenderFrame() = 0;
};

}

