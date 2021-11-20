cmake_minimum_required(VERSION 3.20)
project(glfw_demo01)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(engine)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} sp_engine)

target_include_directories(${PROJECT_NAME} PRIVATE sp_engine)
