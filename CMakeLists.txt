cmake_minimum_required(VERSION 3.5.1)
project(latte)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(Parser ${CMAKE_SOURCE_DIR}/src/Parser.cpp)
add_library(Printer ${CMAKE_SOURCE_DIR}/src/Printer.cpp)
add_library(Lexer ${CMAKE_SOURCE_DIR}/src/Lexer.cpp)
add_library(Absyn ${CMAKE_SOURCE_DIR}/src/Absyn.cpp)
add_library(Compiler ${CMAKE_SOURCE_DIR}/src/Compiler.cpp src/Label.cpp src/Function.cpp src/ConstIntVariable.cpp src/ConstVariable.cpp src/ConstBoolVariable.cpp src/ConstStringVariable.cpp src/RegisterVariable.cpp src/Variable.cpp src/CompilationException.hpp src/NullPtrVariable.cpp src/Structure.cpp src/ExtraTypes.cpp)

add_executable(exec ${CMAKE_SOURCE_DIR}/src/Executable.cpp)
target_link_libraries(exec Parser Printer Lexer Absyn Compiler)
