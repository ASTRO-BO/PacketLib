/***************************************************************************
                          Serial.h  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001, 2013 by Andrea Bulgarelli
    email                : bulgarelli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software for non commercial purpose              *
 *   and for public research institutes; you can redistribute it and/or    *
 *   modify it under the terms of the GNU General Public License.          *
 *   For commercial purpose see appropriate license terms                  *
 *                                                                         *
 ***************************************************************************/
 
#ifndef _SERIAL_H
#define _SERIAL_H
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

///	\brief Represent a serial I/O port

class Serial
{

public:
    /// Common parameters
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
    /// Read only
    RDO		= 0,		
       /// Write only
       WRO		= 1,		
          /// Read & Write
          RDWR	= 2;		

    /// Construction & Destruction
    Serial();
    Serial( char* path, int oflag );
    Serial( int dev, int oflag );
    ~Serial();

    /// Open & Close serial connection
    int 	open( char* path, int oflag );
    int 	open( int dev, int oflag );
    void	close();

    /// Svuota il buffer della seriale (ad es. prima dell'acquisizione)
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
