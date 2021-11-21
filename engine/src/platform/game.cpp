//
// Created by liuso on 2021/11/21.
//

#include <string>
#include "sp_engine/platform/game.h"
#include "sp_engine/service_locator.h"
#include "multiplatform_window.h"
#include "rendering/vulkan/vulkan_renderer.h"

namespace SP {

Game::Game() : Game("My Game") {

}
Game::Game(std::string windowTitle) : _title(std::move(windowTitle)), _running(true) {
  initializeServices();
}
Game::~Game() {
  shutdownServices();
}
void Game::Run() {
  // Run the application
  while (_running) {
    // Update the window
    if (ServiceLocator::GetWindow()->Update()) {
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
    ServiceLocator::GetRenderer()->RenderFrame();
  }
}

void Game::initializeServices() {
  // Provide a window
  ServiceLocator::Provide(new MultiPlatformWindow());

  // Open the window
  ServiceLocator::GetWindow()->OpenWindow(
      {
          .title = _title,
          .width = 800,
          .height = 600
      }
  );

  // Initialize input stream

  // Initialize the render
  RendererSettings settings{
      .ApplicationName = _title
  };

  ServiceLocator::Provide(new VulkanRenderer(), settings);
}
void Game::shutdownServices() {
  ServiceLocator::ShutdownServices();
}

}
