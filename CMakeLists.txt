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