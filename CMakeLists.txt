PROJECT(QuestionAnswer)
cmake_minimum_required(VERSION 2.8)


INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES (malloc.h HAVE_MALLOC_H)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# GTK2
find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})

set(LIBPURPLE_DIR /home/xuewen/Develop/pidgin-2.10.2/build)
include_directories(${LIBPURPLE_DIR}/include/libpurple)

#SET(CMAKE_VERBOSE_MAKEFILE ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Find path of smc compriler
file(GLOB smc_path /opt/smc*)
set(smc_bin "${smc_path}/bin/Smc.jar")

if(smc_bin)
	message("%% Found state machine compiler at: ${smc_bin}")
else(smc_bin)
	message(FATAL_ERROR "Can't find state machine compiler")
endif(smc_bin)

include_directories(${smc_path}/lib/C++)

# add statemachine files
file(GLOB StateMachineFiles ${CMAKE_CURRENT_SOURCE_DIR}/StateMachines/*.sm )
set(StateMachineSources "")
function(smc sm_file)
    get_filename_component(fpath ${sm_file} PATH)
    get_filename_component(fname ${sm_file} NAME_WE)

    #message(STATUS "Add state compiler for: ${fpath}/${fname}_sm.cpp  ${fpath}/${fname}_sm.h")
	add_custom_command(
		OUTPUT ${fpath}/${fname}_sm.cpp  ${fpath}/${fname}_sm.h
		COMMAND java -jar ${smc_bin} -c++ ${sm_file}
		DEPENDS ${sm_file}
	)
	set(StateMachineSources ${StateMachineSources} ${fpath}/${fname}_sm.cpp  ${fpath}/${fname}_sm.h PARENT_SCOPE)
endfunction(smc)

foreach(sfile ${StateMachineFiles})
	smc(${sfile})
endforeach(sfile)

add_library(QuestionAnswer SHARED Main.cpp ${StateMachineSources})


install(TARGETS QuestionAnswer DESTINATION /home/xuewen/Develop/pidgin-2.10.2/build/lib/purple-2)


