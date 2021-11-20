//
// Created by liuso on 2021/11/20.
//

#pragma once

#include "sp_engine/service_locator.h"
#include "sp_engine/platform/game.h"

int main(int argc, char** argv) {
  // 创建应用
  auto *game = CreateGame();

  // 运行应用
  game->Run();

  // 应用运行完成后，删除应用
  delete game;

}