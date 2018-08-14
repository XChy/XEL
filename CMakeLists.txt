project(XEL)#工程名字
cmake_minimum_required(VERSION 2.8)#CMAKE版本

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
    XEL/Preprocessor.cpp)

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

#INSTALL(FILES XEL/XELEngine.cpp
#    XEL/XELContext.h
#    XEL/XString.h
#    XEL/XHashMap
#    XEL/xel_global.h
#    XEL/SharedData
#    XEL/Token.h
#    XEL/EvaluateNode.h
#    XEL/NodeCreator.h
#    XEL/XELError.h
#    XEL/Variant.h
#    XEL/Parser.h
#    XEL/Tokenizer.h
#    XEL/Preprocessor.h
#    DESTINATION XEL)

add_definitions(-std=c++11)
