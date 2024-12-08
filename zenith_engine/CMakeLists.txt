
file(GLOB_RECURSE Src CONFIGURE_DEPENDS ./src/*cpp)
add_library(ZenithEngine SHARED ${Src})

find_package(SDL3 REQUIRED SDL3-shared)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(ZenithEngine PUBLIC SDL3::SDL3 GLEW::GLEW OpenGL::GLU OpenGL::GL)
target_include_directories(ZenithEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/)
