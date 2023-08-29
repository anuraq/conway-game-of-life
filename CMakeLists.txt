# Setup the minimum version required of CMake to generate the Makefile
cmake_minimum_required (VERSION 3.6)

# Raises a FATAL_ERROR if version < 2.8
# cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

project(Conway_Life)

# find_package(SFML)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${PROJECT_SOURCE_DIR} src)

set(SOURCES "src/main.cpp")

add_executable(conway ${SOURCES})
# target_include_directories(opengl_exe PRIVATE include)
# target_link_options(opengl_exe PRIVATE -lglfw -lOpenGL)

# Link SFML libraries to your executable
target_link_libraries(conway sfml-graphics sfml-window sfml-system)
