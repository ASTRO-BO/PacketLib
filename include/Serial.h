/***************************************************************************
                          Serial.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
#ifndef SERIAL_h_h_ZC2002
#define SERIAL_h_h_ZC2002
#include "PacketLibDefinition.h"
#include <termios.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#define	SER1		"/dev/ttyS1"
#define	SER2		"/dev/ttyS2"

namespace PacketLib
{

//##ModelId=3C0F6BDB0029
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Serial.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: Serial.h,v 1.3 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.3 $
//##	\brief Represent a serial I/O port

class Serial
{

public:
    // Common parameters
    static const int
    b1200		= 1200,
         b1800		= 1800,
              b2400		= 2400,
                   b4800		= 4800,
                        b9600		= 9600,
                             b19200	= 19200,
                              b38400	= 38400,
                               b57600	= 57600,
                                b76800	= 76800,
                                 b115200 = 115200;

    static const int
    SERIAL1	= 1,
    SERIAL2	= 2;

    static const int
    RDO		= 0,		// Read only
       WRO		= 1,		// Write only
          RDWR	= 2;		// Read & Write

    // Construction & Destruction
    Serial();
    Serial( char* path, int oflag );
    Serial( int dev, int oflag );
    ~Serial();

    // Open & Close serial connection
    int 	open( char* path, int oflag );
    int 	open( int dev, int oflag );
    void	close();

    // Svuota il buffer della seriale (ad es. prima dell'acquisizione)
    int 	dump();

    int 	set( speed_t baud );
    int		write( void* buf, int nbyte );
    int		read( void* buf, int nbyte );

private:

protected:
    int		fd;
};
}
#endif
