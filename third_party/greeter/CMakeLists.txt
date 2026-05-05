cmake_minimum_required(VERSION 3.17)
project(Greeter VERSION 1.0.0 LANGUAGES CXX)

# ─── Standar C++ ─────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ─── Helper modules ───────────────────────────────────────────────────────────
# GNUInstallDirs: menyediakan variabel standar seperti CMAKE_INSTALL_LIBDIR,
# CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_INCLUDEDIR, dll.
include(GNUInstallDirs)

# CPM.cmake: package manager ringan berbasis CMake untuk fetch dependensi
include(cmake/CPM.cmake)

# ─── Dependensi ───────────────────────────────────────────────────────────────
# fmt: library formatting string modern untuk C++
CPMAddPackage("gh:fmtlib/fmt#10.2.1")

# ─── Library target ───────────────────────────────────────────────────────────
# Kumpulkan semua source file dari subdirektori Module*
file(GLOB_RECURSE SOURCES "Module*/*.cpp")

# Build sebagai shared library (.so / .dylib / .dll)
add_library(Greeter SHARED ${SOURCES})

# Alias namespace agar konsumen bisa pakai Greeter::Greeter via find_package
# maupun add_subdirectory secara konsisten
add_library(Greeter::Greeter ALIAS Greeter)

# ─── Properti target ──────────────────────────────────────────────────────────
# Windows: auto-export semua simbol tanpa perlu __declspec(dllexport) manual
set_target_properties(Greeter PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# ─── Include directories ──────────────────────────────────────────────────────
# BUILD_INTERFACE  : path saat dikonsumsi via add_subdirectory (build tree)
# INSTALL_INTERFACE: path saat dikonsumsi via find_package (install tree)
target_include_directories(Greeter PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ─── Linkage ──────────────────────────────────────────────────────────────────
# PUBLIC: fmt juga di-propagate ke target yang me-link Greeter
target_link_libraries(Greeter PUBLIC fmt::fmt)

# ─── Install rules ────────────────────────────────────────────────────────────
# Install shared library ke lib/ (Linux/macOS) atau bin/ (Windows)
install(TARGETS Greeter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install semua header dari direktori ini ke include/greeter/
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/greeter
    FILES_MATCHING PATTERN "*.h"
)
