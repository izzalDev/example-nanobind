cmake_minimum_required(VERSION 3.17)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/greeter)

find_package(Python COMPONENTS Interpreter Development
  REQUIRED)
find_package(nanobind CONFIG REQUIRED)
nanobind_add_module(_core src/main.cpp)
target_link_libraries(_core PRIVATE Greeter::Greeter)

nanobind_add_stub(_core_stub
    MODULE _core
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/_core.pyi
    DEPENDS _core Greeter::Greeter
)

install(TARGETS _core DESTINATION ${SKBUILD_PROJECT_NAME})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/_core.pyi
    DESTINATION ${SKBUILD_PROJECT_NAME})
