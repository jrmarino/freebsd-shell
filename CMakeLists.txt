cmake_minimum_required(VERSION 3.16)
project(freebsd-shell)

SET(CMAKE_SKIP_BUILD_RPATH TRUE)

add_subdirectory(tool_mknodes)
add_subdirectory(tool_mksyntax)
add_subdirectory(shell)
