cmake_minimum_required(VERSION 3.15)



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(OpenGL_GL_PREFERENCE GLVND)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ZenithEngine)
add_subdirectory(./zenith_engine)
add_subdirectory(./testbed)
target_link_libraries(Game PUBLIC ZenithEngine)
target_include_directories(Game PUBLIC ./zenith_engine/src)
