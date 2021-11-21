cmake_minimum_required(VERSION 3.20)
project(sp_engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/glm)
add_subdirectory(external/glfw)
add_subdirectory(external/vk-bootstrap)

# Library find functions
# 增加这个设置是因为不设置，会报错找不到Vulkan_LIBRARY
#set(Vulkan_LIBRARY $ENV{VULKAN_SDK}/Lib/vulkan-1.lib)
#find_library(Vulkan_LIBRARY NAMES "vulkan-1" PATHS "$ENV{VULKAN_SDK}/Lib" NO_DEFAULT_PATH)
find_library(Vulkan_LIBRARY NAMES "vulkan-1")
find_package(Vulkan REQUIRED)


#file(GLOB_RECURSE SOURCE_FILES "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp")
file(GLOB SOURCE_FILES src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp src/*/*/*/*/*.cpp)
#aux_source_directory(src SOURCE_FILES)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Vulkan_INCLUDE_DIRS}
        glfw
        vk-bootstrap
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        glm
        PRIVATE
        ${Vulkan_LIBRARIES}
        glfw
        vk-bootstrap
        )