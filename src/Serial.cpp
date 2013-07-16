using namespace std;

#include "Serial.h"
#include "PacketLibDemo.h"

using namespace PacketLib;

//------------------------------------------------------------------------------
//
//		Implementation of class Serial
//
//------------------------------------------------------------------------------

Serial::Serial() {

	fd = -1;
}

Serial::Serial( char* path, int oflag ) {

	fd = -1;
	Serial::open( path, oflag );
}

Serial::Serial( int dev, int oflag ) {

	fd = -1;
	Serial::open( dev, oflag );
}

Serial::~Serial() {

	Serial::close();
}

int Serial::open( char* path, int oflag ) {
	DEMORET0;
	if( fd >= 0)
		return fd;

	fd = ::open( path, oflag | O_RDWR );
	set(B38400);
	return fd;
}

int Serial::open( int dev, int oflag ) {
	DEMORET0;
	if( fd >= 0)
		return fd;

	switch( dev ) {

	case SERIAL1:
		fd = ::open( SER1, oflag );
		break;

	case SERIAL2:
		fd = ::open( SER2, oflag );
		break;

	default:
		return -1;
	}

	return fd;
}

void Serial::close() {

	::close( fd );
	fd = -1;
}


int Serial::write( void* buf, int nbyte ) {
	return ::write( fd, buf, nbyte );
}

int Serial::read( void* buf, int nbyte) {
	return ::read( fd, buf, nbyte );
}

int Serial::set( speed_t speed ) {

	struct termios 	par;
	tcgetattr( fd, &par );

	cfsetispeed( &par, speed );
	cfsetospeed( &par, speed );

	// Disable software handshacking control
	par.c_iflag &= ( ~IXOFF);
	par.c_iflag &= ( ~IXON );
	par.c_lflag &= ( ~IEXTEN );

	tcsetattr( fd, TCSANOW, &par );
	
	return 0;	 
}

int Serial::dump() {
	
	char*	pbuff = new char[10];
	int		bdump = 0;
	
	int bread = ::read( fd, pbuff, 10 );
	while( bread != -1 ) {
		bdump += bread;
		bread = ::read( fd, pbuff, 10 );
	}

	delete[] pbuff;	
	return bdump;
}
