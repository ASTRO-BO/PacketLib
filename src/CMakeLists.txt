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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}static STATIC ${SOURCES})
set_target_properties(${PROJECT_NAME}static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
target_link_libraries(${PROJECT_NAME} ${LIBS} -fPIC)

# make install
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h")
install(FILES ${HEADERS} DESTINATION include/packet)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(TARGETS ${PROJECT_NAME}static DESTINATION lib)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../doc DESTINATION .)
