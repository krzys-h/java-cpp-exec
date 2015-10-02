cmake_minimum_required(VERSION 2.8)

project(java-cpp-exec C CXX)

find_package(JNI)
find_package(Java)
include(UseJava)

add_jar(java-cpp-exec-link Compiler.java)

add_definitions(-std=c++11)
include_directories(${JNI_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${JNI_LIBRARIES})
