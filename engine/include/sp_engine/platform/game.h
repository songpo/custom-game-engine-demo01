//
// Created by liuso on 2021/11/21.
//

#pragma once

class Game {
 public:
  Game();
  explicit Game(std::string windowTitle);
  ~Game();

  void Run();

 protected:
  virtual void PhysicsUpdate(float deltaTime) {};
  virtual void Update(float deltaTime) { };
  virtual void Draw() { };

 private:
  static void initializeServices();
  static void shutdownServices();

 private:
  std::string _title;
  bool _running;

};

extern Game* CreateGame();
