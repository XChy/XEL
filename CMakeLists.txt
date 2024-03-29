project(XEL)
cmake_minimum_required(VERSION 3.5)

option(BUILD_TEST "Set to complie the test sample" ON)
option(BUILD_SHARED_LIBRARY "Set to switch to build shared library" ON)
option(BUILD_STATIC_LIBRARY "Set to switch to build static library" OFF)

include_directories(./)
file(GLOB_RECURSE SRC "XEL/*.cpp")
if(BUILD_SHARED_LIBRARY)
  add_definitions(-DXEL_SHARED_LIBRARY)
  message(STATUS "Build shared library")

  add_library(XEL_SHARED SHARED ${SRC})
  set_target_properties(XEL_SHARED PROPERTIES OUTPUT_NAME "XEL")
endif()

if(BUILD_STATIC_LIBRARY)
  add_definitions(-DXEL_STATIC_LIBRARY)
  message(STATUS "Build static library")

  add_library(XEL_STATIC STATIC ${SRC})
  set_target_properties(XEL_STATIC PROPERTIES OUTPUT_NAME "XEL")
endif()

if(BUILD_TEST)
  add_definitions(-DXEL_TEST)
  message(STATUS "Build test sample")

  add_executable(XEL_TEST test/test.cpp ${SRC})
  set_target_properties(XEL_TEST PROPERTIES OUTPUT_NAME "XEL_TEST")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_DEBUG
      "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11  -fsanitize=address -g -Wall -Wno-unused-variable -pthread"
  )
  set(CMAKE_CXX_FLAGS_RELEASE
      "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -O2 -pthread -fopenmp")
endif()

set(CMAKE_CXX_STANDARD 11)
