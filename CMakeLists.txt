cmake_minimum_required(VERSION 3.17)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

# ─── Standar C++ ──────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── Dependensi ───────────────────────────────────────────────────────────────
# Greeter: shared library C++ yang di-wrap ke Python
add_subdirectory(third_party/greeter)

# Python: diperlukan nanobind untuk binding ke interpreter aktif
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# nanobind: framework untuk membuat Python extension module dari C++
find_package(nanobind CONFIG REQUIRED)

# ─── Python extension module ───────────────────────────────────────────────────
nanobind_add_module(_core src/main.cpp)
target_link_libraries(_core PRIVATE Greeter::Greeter)

# ─── Copy shared library ke output direktori _core ────────────────────────────
# Diperlukan saat stub generation agar _core bisa di-import dan menemukan
# libGreeter di direktori yang sama
add_custom_command(TARGET _core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Greeter>
        $<TARGET_FILE_DIR:_core>
    VERBATIM
)

# ─── Stub generation (.pyi) ───────────────────────────────────────────────────
# Generate type stub untuk editor support dan static analysis (mypy, pyright)
nanobind_add_stub(_core_stub
    MODULE _core
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/_core.pyi
    DEPENDS _core Greeter::Greeter
    PYTHON_PATH $<TARGET_FILE_DIR:_core>
)

# ─── Install rules ────────────────────────────────────────────────────────────
# Extension module utama
install(TARGETS _core DESTINATION ${SKBUILD_PROJECT_NAME})

# Shared library Greeter harus ikut di-bundle dalam wheel agar bisa ditemukan
# saat runtime (khususnya Windows yang tidak punya rpath)
install(TARGETS Greeter RUNTIME DESTINATION ${SKBUILD_PROJECT_NAME})

# Type stub untuk tooling
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/_core.pyi
    DESTINATION ${SKBUILD_PROJECT_NAME}
)
