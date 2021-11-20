cmake_minimum_required(VERSION 3.20)
project(sp_engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/glm)
add_subdirectory(external/glfw)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        glm
        PRIVATE
        glfw
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        glm
        PRIVATE
        glfw
        )