cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

macro( MACRO_ENSURE_OUT_OF_SOURCE_BUILD _errorMessage )
string( COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" _insource )
if( _insource )
 message( SEND_ERROR "${_errorMessage}" )
 message( FATAL_ERROR
 "In-source builds are not allowed.
 
 This process created the file `CMakeCache.txt' and the directory `CMakeFiles and overwrite the Makefile.
 Please fix them with:
 
     rm -r CMakeCache.txt CMakeFiles
     git checkout Makefile
 
 CMake would overwrite the makefiles distributed with Compiler-RT.
 Please create a directory outside the source directory and run cmake
 from there, passing the path to this source directory as the last argument.
 Example for the lazy people:
 
     mkdir ../PacketLib_build
     cd ../PacketLib_build
     cmake ../PacketLib
 " )
endif( _insource )
endmacro( MACRO_ENSURE_OUT_OF_SOURCE_BUILD )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

MACRO_ENSURE_OUT_OF_SOURCE_BUILD( "In-source build error." )

project(packet)
set(packet_MAJOR_VERSION 4)
set(packet_MINOR_VERSION 5)
set(packet_PATCH_VERSION 0)
set(packet_VERSION
${packet_MAJOR_VERSION}.${packet_MINOR_VERSION}.${packet_PATCH_VERSION})
set(PROJECT_VERSION ${packet_VERSION})

add_subdirectory(src)
