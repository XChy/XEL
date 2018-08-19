project(XEL)
cmake_minimum_required(VERSION 2.8)

option(BUILD_SHARED_LIBRARY "Set to switch to build shared library" ON)
option(BUILD_STATIC_LIBRARY "Set to switch to build static library" OFF)

include_directories(./)
set(SRC
    XEL/XELEngine.cpp
    XEL/XELContext.cpp
    XEL/XString.cpp
    XEL/Token.cpp
    XEL/EvaluateNode.cpp
    XEL/NodeCreator.cpp
    XEL/XELError.cpp
    XEL/Variant.cpp
    XEL/Parser.cpp
    XEL/Tokenizer.cpp
    XEL/XELObject.cpp
    XEL/XELContainerObject.cpp
    XEL/XELValOrVar
    )

if (BUILD_SHARED_LIBRARY)
    add_definitions(-DXEL_SHARED_LIBRARY)
    message(STATUS "Build shared library")

    add_library(XEL_SHARED SHARED ${SRC})
    SET_TARGET_PROPERTIES(XEL_SHARED PROPERTIES OUTPUT_NAME "XEL")
endif()

if(BUILD_STATIC_LIBRARY)
    add_definitions(-DXEL_STATIC_LIBRARY)
    message(STATUS "Build static library")

    add_library(XEL_STATIC STATIC ${SRC})
    SET_TARGET_PROPERTIES(XEL_STATIC PROPERTIES OUTPUT_NAME "XEL")
endif()

if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Release )
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -g -Wall -Wno-unused-variable -pthread")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -O2 -pthread -fopenmp")
endif()


add_definitions(-std=c++11)
