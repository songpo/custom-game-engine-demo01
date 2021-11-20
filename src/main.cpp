//
// Created by liuso on 2021/11/20.
//
#include <iostream>
#include <utility>
#include "sp_engine/platform/entry_point.h"
#include "sp_engine/platform/game.h"

class MyGame : public Game {
 public:
  explicit MyGame(std::string title) : Game(std::move(title)) {
    std::cout << "Hello, welcome to my game!" << std::endl;
  }

 protected:
  void Update(float deltaTime) override {
//    std::cout << "I'm updating!" << std::endl;
  }
};

Game* CreateGame() {
  return new MyGame("Test change window title!");
}
