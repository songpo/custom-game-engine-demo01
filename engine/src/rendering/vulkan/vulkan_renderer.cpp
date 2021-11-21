//
// Created by liuso on 2021/11/21.
//

#include "vulkan_renderer.h"

#include <VkBootstrap.h>
#include <sp_engine/service_locator.h>
#include "vulkan_initializers.h"
#include "vulkan_types.h"
#include "vulkan_utilities.h"

namespace SP {

void VulkanRenderer::Init(RendererSettings settings) {
  _settings = settings;

  initCore();
  createSwapChain();
  createCommands();
  createDefaultRenderPass();
  createFrameBuffers();
  createSyncStructures();
  createPipeLines();
}
void VulkanRenderer::Shutdown() {
  vkDeviceWaitIdle(_device);

  vkDestroyFence(_device, _render_fence, nullptr);
  vkDestroySemaphore(_device, _render_semaphore, nullptr);
  vkDestroySemaphore(_device, _present_semaphore, nullptr);

  for (auto buffer: _frame_buffers) {
    vkDestroyFramebuffer(_device, buffer, nullptr);
  }

  vkDestroyRenderPass(_device, _render_pass, nullptr);

  vkDestroyCommandPool(_device, _command_pool, nullptr);
  vkDestroySwapchainKHR(_device, _swap_chain, nullptr);

  for (auto imageView: _swap_chain_image_views) {
    vkDestroyImageView(_device, imageView, nullptr);
  }

  vkDestroyDevice(_device, nullptr);
  vkDestroySurfaceKHR(_instance, _surface, nullptr);
  vkb::destroy_debug_utils_messenger(_instance, _debug_messenger);
  vkDestroyInstance(_instance, nullptr);
}
void VulkanRenderer::RenderFrame() {
  VK_CHECK(vkWaitForFences(_device, 1, &_render_fence, true, 1000000000)); // 1
  VK_CHECK(vkResetFences(_device, 1, &_render_fence));                     // 0

  uint32_t swapChainImageIndex;
  VK_CHECK(vkAcquireNextImageKHR(_device, _swap_chain, 1000000000, _present_semaphore, nullptr, &swapChainImageIndex));

  VK_CHECK(vkResetCommandBuffer(_main_command_buffer, 0));

  VkCommandBuffer cmdBuffer = _main_command_buffer;

  VkCommandBufferBeginInfo commandBufferBeginInfo{VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
  commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  VK_CHECK(vkBeginCommandBuffer(cmdBuffer, &commandBufferBeginInfo));

  float flashColor = abs(sin((float) _frame_number / 120.f));
  VkClearValue clearValue{
      .color = {0.f, flashColor, flashColor, 1.f}
  };

  VkRenderPassBeginInfo renderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
  renderPassBeginInfo.renderPass = _render_pass;
  renderPassBeginInfo.renderArea = {
      .offset = {
          .x = 0,
          .y = 0
      },
      .extent = _window_extent
  };
  renderPassBeginInfo.framebuffer = _frame_buffers[swapChainImageIndex];
  // Connect clear values
  renderPassBeginInfo.clearValueCount = 1;
  renderPassBeginInfo.pClearValues = &clearValue;

  vkCmdBeginRenderPass(cmdBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

  // Draw call
  vkCmdEndRenderPass(cmdBuffer);
  VK_CHECK(vkEndCommandBuffer(cmdBuffer));

  VkSubmitInfo submitInfo{VK_STRUCTURE_TYPE_SUBMIT_INFO};

  VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  submitInfo.pWaitDstStageMask = &waitStage;

  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = &_present_semaphore;

  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = &_render_semaphore;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &_main_command_buffer;

  VK_CHECK(vkQueueSubmit(_graphics_queue, 1, &submitInfo, _render_fence));

  VkPresentInfoKHR presentInfoKhr{VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};
  presentInfoKhr.swapchainCount = 1;
  presentInfoKhr.pSwapchains = &_swap_chain;

  presentInfoKhr.waitSemaphoreCount = 1;
  presentInfoKhr.pWaitSemaphores = &_render_semaphore;

  presentInfoKhr.pImageIndices = &swapChainImageIndex;

  VK_CHECK(vkQueuePresentKHR(_graphics_queue, &presentInfoKhr));

  _frame_number++;
}
void VulkanRenderer::initCore() {
  // Initialize the instance
  vkb::InstanceBuilder builder;

  auto instanceBuilder = builder.set_app_name(_settings.ApplicationName.c_str())
      .request_validation_layers(true)
      .require_api_version(1, 2, 0)
      .use_default_debug_messenger()
      .build();

  vkb::Instance vkb_inst = instanceBuilder.value();

  _instance = vkb_inst.instance;
  _debug_messenger = vkb_inst.debug_messenger;

  // Request vulkan surface
  std::unordered_map<SurfaceArgs, std::any> surfaceArgs{
      {SurfaceArgs::INSTANCE, _instance},
      {SurfaceArgs::OUT_SURFACE, &_surface},
  };

  ServiceLocator::GetWindow()->RequestDrawSurface(surfaceArgs);

  // Select physical device
  vkb::PhysicalDeviceSelector vkbPhysicalDeviceSelector{vkb_inst};
  vkb::PhysicalDevice vkbPhysicalDevice = vkbPhysicalDeviceSelector
      .set_minimum_version(1, 1)
      .set_surface(_surface)
      .select()
      .value();

  // Create a vulkan device
  vkb::DeviceBuilder vkbDeviceBuilder{vkbPhysicalDevice};
  vkb::Device vkbDevice{vkbDeviceBuilder.build().value()};

  _device = vkbDevice.device;
  _physical_device = vkbPhysicalDevice.physical_device;

  _graphics_queue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
  _graphics_queue_family = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
}
void VulkanRenderer::createSwapChain() {
  auto[width, height] = ServiceLocator::GetWindow()->GetWindowExtents();

  _window_extent.width = width;
  _window_extent.height = height;

  vkb::SwapchainBuilder vkbSwapChainBuilder{
      _physical_device,
      _device,
      _surface
  };
  vkb::Swapchain vkbSwapChain = vkbSwapChainBuilder
      .use_default_format_selection()
      .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
      .set_desired_extent(width, height)
      .build()
      .value();

  // Store swap_chain an all it's related images
  _swap_chain = vkbSwapChain.swapchain;
  _swap_chain_images = vkbSwapChain.get_images().value();
  _swap_chain_image_views = vkbSwapChain.get_image_views().value();
  _swap_chain_image_format = vkbSwapChain.image_format;
}
void VulkanRenderer::createCommands() {
  VkCommandPoolCreateInfo commandPoolCreateInfo = VulkanInitializers::GetCommandPoolCreateInfo(
      _graphics_queue_family,
      VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
  );
  VkResult commandPoolCreateResult = vkCreateCommandPool(_device, &commandPoolCreateInfo, nullptr, &_command_pool);
  VK_CHECK(commandPoolCreateResult);

  VkCommandBufferAllocateInfo commandBufferAllocateInfo = VulkanInitializers::GetCommandBufferAllocateInfo(
      _command_pool,
      1,
      VK_COMMAND_BUFFER_LEVEL_PRIMARY
  );
  VkResult commandBufferAllocateResult = vkAllocateCommandBuffers(
      _device,
      &commandBufferAllocateInfo,
      &_main_command_buffer
  );
  VK_CHECK(commandBufferAllocateResult);
}
void VulkanRenderer::createDefaultRenderPass() {
  VkAttachmentDescription colorAttachment{
      .format = _swap_chain_image_format,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
      .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
      .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
  };

  VkAttachmentReference colorAttachmentRef{
      .attachment = 0,
      .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
  };

  VkSubpassDescription subPass{
      .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
      .colorAttachmentCount = 1,
      .pColorAttachments = &colorAttachmentRef
  };

  VkRenderPassCreateInfo renderPassCreateInfo{VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
  renderPassCreateInfo.attachmentCount = 1;
  renderPassCreateInfo.pAttachments = &colorAttachment;
  renderPassCreateInfo.subpassCount = 1;
  renderPassCreateInfo.pSubpasses = &subPass;

  VK_CHECK(vkCreateRenderPass(_device, &renderPassCreateInfo, nullptr, &_render_pass));
}
void VulkanRenderer::createFrameBuffers() {
  VkFramebufferCreateInfo frameBufferCreateInfo{VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
  frameBufferCreateInfo.renderPass = _render_pass;
  frameBufferCreateInfo.attachmentCount = 1;
  frameBufferCreateInfo.width = _window_extent.width;
  frameBufferCreateInfo.height = _window_extent.height;
  frameBufferCreateInfo.layers = 1;

  const uint32_t swapChainImageCount = _swap_chain_images.size();
  _frame_buffers.resize(swapChainImageCount);

  for (int i = 0; i < swapChainImageCount; i++) {
    frameBufferCreateInfo.pAttachments = &_swap_chain_image_views[i];
    VK_CHECK(vkCreateFramebuffer(_device, &frameBufferCreateInfo, nullptr, &_frame_buffers[i]));
  }
}
void VulkanRenderer::createSyncStructures() {
  VkFenceCreateInfo fenceCreateInfo{VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
  fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  VK_CHECK(vkCreateFence(_device, &fenceCreateInfo, nullptr, &_render_fence));

  VkSemaphoreCreateInfo semaphoreCreateInfo{VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
  VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_present_semaphore));
  VK_CHECK(vkCreateSemaphore(_device, &semaphoreCreateInfo, nullptr, &_render_semaphore));
}
void VulkanRenderer::createPipeLines() {
  VkShaderModule triangleFragShader;
  if (!VulkanUtilities::LoadShaderModule("shaders/triangle.frag.spv", _device, triangleFragShader)) {
    std::cout << "Failed load triangle fragment shader module" << std::endl;
  } else {
    std::cout << "Load triangle fragment shader module success" << std::endl;
  }

  VkShaderModule triangleVertShader;
  if (!VulkanUtilities::LoadShaderModule("shaders/triangle.vert.spv", _device, triangleVertShader)) {
    std::cout << "Failed load triangle vertex shader module" << std::endl;
  } else {
    std::cout << "Load triangle shader vertex module success" << std::endl;
  }
}

}
