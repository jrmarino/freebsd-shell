set (prog freesh)

set (genhdrs
	${CMAKE_CURRENT_BINARY_DIR}/builtins.h
	${CMAKE_CURRENT_BINARY_DIR}/nodes.h
	${CMAKE_CURRENT_BINARY_DIR}/syntax.h
	${CMAKE_CURRENT_BINARY_DIR}/token.h)
set (gensrcs
	${CMAKE_CURRENT_BINARY_DIR}/builtins.c
	${CMAKE_CURRENT_BINARY_DIR}/nodes.c
	${CMAKE_CURRENT_BINARY_DIR}/syntax.c)

set (srcs
	${genhdrs} ${gensrcs}
	alias.c arith_yacc.c arith_yylex.c cd.c echo.c
	error.c eval.c exec.c expand.c histedit.c input.c
	jobs.c kill.c mail.c main.c memalloc.c miscbltin.c
	mystring.c options.c output.c qsort_s.c parser.c printf.c
	redir.c show.c test.c trap.c var.c
)

set_source_files_properties(${genhdrs} PROPERTIES GENERATED true)
set_source_files_properties(${gensrcs} PROPERTIES GENERATED true)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/builtins.h 
               ${CMAKE_CURRENT_BINARY_DIR}/builtins.c
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/mkbuiltins
                builtins.def
	COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/mkbuiltins
		${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/nodes.h 
               ${CMAKE_CURRENT_BINARY_DIR}/nodes.c
	DEPENDS ${CMAKE_BINARY_DIR}/tool_mknodes/mknodes
                ${CMAKE_CURRENT_SOURCE_DIR}/nodetypes
                ${CMAKE_CURRENT_SOURCE_DIR}/nodes.c.pat
	COMMAND ${CMAKE_BINARY_DIR}/tool_mknodes/mknodes
                ${CMAKE_CURRENT_SOURCE_DIR}/nodetypes
                ${CMAKE_CURRENT_SOURCE_DIR}/nodes.c.pat
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/syntax.h 
               ${CMAKE_CURRENT_BINARY_DIR}/syntax.c
	DEPENDS ${CMAKE_BINARY_DIR}/tool_mksyntax/mksyntax
	COMMAND ${CMAKE_BINARY_DIR}/tool_mksyntax/mksyntax
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/token.h 
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/mktokens
	COMMAND /bin/sh ${CMAKE_CURRENT_SOURCE_DIR}/mktokens
)


add_executable(${prog} ${srcs})
# add_executable(${prog} ${gensrcs} ${genhdrs})
target_include_directories(${prog} PUBLIC
	${CMAKE_SOURCE_DIR}/shell
	${CMAKE_BINARY_DIR}/shell
	/raven/include
)
target_compile_definitions(${prog} PUBLIC SHELL)
target_link_libraries (${prog} -Wl,-rpath,/raven/lib /raven/lib/libedit.so)

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${prog} DESTINATION bin RENAME sh)
install(FILES sh.1 DESTINATION share/man/man1)
