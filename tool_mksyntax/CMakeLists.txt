set (prog mksyntax)

set (srcs mksyntax.c)

add_executable(${prog} ${srcs})

target_include_directories(${prog} PUBLIC
	${CMAKE_SOURCE_DIR}/shell)
