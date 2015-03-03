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
