cmake_minimum_required(VERSION 3.15)
project(usage CXX)

find_package(eve REQUIRED CONFIG)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${CMAKE_PROJECT_NAME} eve::eve)

install(TARGETS ${CMAKE_PROJECT_NAME})