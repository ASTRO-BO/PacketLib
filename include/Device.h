/***************************************************************************
                          Device.h
                             -------------------
    begin                : Mon Mar 4 2002
    copyright            : (C) 2002, 2013 by Andrea Bulgarelli
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

#ifndef _DEVICE_H
#define _DEVICE_H

namespace PacketLib
{
///	\brief This class represent a Device for IO system.
class Device
{
public:
    Device(bool bigendian);

     virtual bool isClosed() const;

    virtual bool isEOF() const;
    /// Write property of bool endsession.
    virtual void setEndSession( const bool& _newVal);

    /// Read property of bool endsession.
    virtual const bool& getEndSession() const;

    virtual bool isBigEndian() const;

protected:

    bool eof;

    bool closed;

    bool bigendian;

    /// This variable indicates when a measurement session is terminated
    /// The device class have this attribute because this information is passed
    /// with the device.
    bool endsession;
};
}
#endif
