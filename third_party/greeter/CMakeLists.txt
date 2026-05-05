cmake_minimum_required(VERSION 3.17)
project(Greeter VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 10.2.1)
FetchContent_MakeAvailable(fmt)

file(GLOB_RECURSE SOURCES "Module*/*.cpp")
add_library(Greeter SHARED ${SOURCES})
target_link_libraries(Greeter PUBLIC fmt::fmt)
target_include_directories(Greeter PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>)
add_library(Greeter::Greeter ALIAS Greeter)
