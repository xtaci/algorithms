cmake_minimum_required( VERSION 2.6 )
project( algorithm )

include_directories( "include" )
include_directories( "." )
if( MSVC )
	include_directories( "msvc" )
endif()

#add_executable(word_seg "src/word_seg_demo.cpp")
#add_executable(astar "src/astar_demo.cpp")

file( GLOB APP_SOURCES src/*.cpp )
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /FI\"msvc/alg_vs.h\"" ) 
message( ${CMAKE_CXX_FLAGS} )
foreach( appsourcefile ${APP_SOURCES} )
	get_filename_component( demo_name ${appsourcefile} NAME_WE )
	add_executable( ${demo_name} ${appsourcefile} )
endforeach( appsourcefile ${APP_SOURCES} )


/**


Assignment Requirements for the Algorithms project.
1. I need to make something that shows a nice DEMO. Demonstration. -> The way I can do this is by doing the following:
	1. I can start.
		2. I can try to figure out how to properly do dependency management (*Decompress a Directed Acyclic Graph -> DAG RFC. With Autocomplete.)


Dependency Management is likely the future. The reason; (We - I, etc.) say this is because proper surveys' can make OR break a companies routine etc. There's a lot of beauty to be able to be seen within this System.
Systems assignment for COE 379L (P.I. -> Marcus.)
**/