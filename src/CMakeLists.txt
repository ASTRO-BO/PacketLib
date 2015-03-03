set(SOURCES ByteStream.cpp File.cpp InputPacketStream.cpp InputTextFile.cpp OutputPacketStream.cpp
			PacketBufferV.cpp PacketHeader.cpp SDFBlock.cpp SocketServer.cpp ConfigurationFile.cpp
			FileStream.cpp InputPacketStreamFile.cpp MSGQ.cpp OutputSerial.cpp PacketDataField.cpp
			PacketIdentifier.cpp SHM.cpp SourceDataField.cpp DataFieldHeader.cpp FileStreamPointer.cpp
			InputSerial.cpp MemoryBuffer.cpp OutputSocketClient.cpp PacketException.cpp
			PacketNotRecognized.cpp Serial.cpp Utility.cpp Device.cpp Input.cpp InputSocketServer.cpp
			Output.cpp Packet.cpp PacketExceptionFileFormat.cpp PacketStream.cpp Socket.cpp pugixml.cpp
			Field.cpp InputFile.cpp InputText.cpp OutputFile.cpp PacketBufferQ.cpp PacketExceptionIO.cpp
			PartOfPacket.cpp SocketClient.cpp
			lz4.c lz4hc.c)

# libpacket.a and libpacket.so
include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES})
add_library(${CMAKE_PROJECT_NAME}static STATIC ${SOURCES})
set_target_properties(${CMAKE_PROJECT_NAME}static PROPERTIES OUTPUT_NAME ${CMAKE_PROJECT_NAME})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

# make install
file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
install(FILES ${HEADERS} DESTINATION include/packet)
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION lib)
install(TARGETS ${CMAKE_PROJECT_NAME}static DESTINATION lib)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc DESTINATION .)
