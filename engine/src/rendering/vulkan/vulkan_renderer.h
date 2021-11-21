//
// Created by liuso on 2021/11/21.
//
#pragma once

#include "sp_engine/rendering/renderer.h"
#include <vulkan/vulkan.h>
#include <vector>

namespace SP {

class VulkanRenderer : public Renderer {

 public:
  void Init(RendererSettings settings) override;
  void Shutdown() override;
  void RenderFrame() override;

 private:
  void initCore();
  void createSwapChain();
  void createCommands();
  void createDefaultRenderPass();
  void createFrameBuffers();
  void createSyncStructures();

 private:
  // TODO Temporary frame number
  uint64_t _frame_number{0};

  RendererSettings _settings;

  /**
   * Core Vulkan
   */
  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debug_messenger;
  VkPhysicalDevice _physical_device;
  VkDevice _device;
  VkSurfaceKHR _surface;

  /**
   * SwapChain
   */
  VkSwapchainKHR _swap_chain;
  VkFormat _swap_chain_image_format;
  std::vector<VkImage> _swap_chain_images;
  std::vector<VkImageView> _swap_chain_image_views;
  VkExtent2D _window_extent;

  /**
   * Command pools and queues
   */
  VkQueue
      _graphics_queue;
  uint32_t _graphics_queue_family;
  VkCommandPool _command_pool;
  VkCommandBuffer _main_command_buffer;

  /**
   * Render passes
   */
  VkRenderPass _render_pass;
  std::vector<VkFramebuffer> _frame_buffers{3};

  /**
   * Synchronization objects
   */
  VkSemaphore _present_semaphore;
  VkSemaphore _render_semaphore;
  VkFence _render_fence;
};

}
