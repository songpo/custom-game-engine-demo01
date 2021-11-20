//
// Created by liuso on 2021/11/21.
//

#include <string>
#include "sp_engine/platform/game.h"
#include "sp_engine/service_locator.h"
#include "multiplatform_window.h"

Game::Game() : Game("My Game") {

}
Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(true) {
  initializeServices();
}
Game::~Game() {
  shutdownServices();
}
void Game::Run() {
//  SP::WindowData window_data;
//  window_data.width = 800;
//  window_data.height = 600;
//  window_data.title = _title;

  SP::WindowData window_data {
      .title = _title,
      .width = 800,
      .height = 600
  };

  // Open the window
  SP::ServiceLocator::GetWindow()->OpenWindow(window_data);

  // Run the application
  while (_running) {
    // Update the window
    if (SP::ServiceLocator::GetWindow()->Update()) {
      _running = false;
      continue;
    }

    // Calculate deltaTime
    float deltaTime = 0.0f;

    // Update game state
    Update(deltaTime);

    // Update physics
    PhysicsUpdate(deltaTime);

    // Draw
    Draw();
  }
}

void Game::initializeServices() {
  // Provide a window
  SP::ServiceLocator::Provide(new SP::MultiPlatformWindow());

  // Initialize input stream

  // Initialize the render
}
void Game::shutdownServices() {
  SP::ServiceLocator::ShutdownServices();
}
