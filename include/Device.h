/***************************************************************************
                          Device.h  -  description
                             -------------------
    begin                : Mon Mar 4 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
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

#ifndef DEVICE_H
#define DEVICE_H

namespace PacketLib {
//##ModelId=3C87743F01CC
//##Documentation
//##	$Date: 2005/03/09 10:57:50 $
//##	$Header: /home/repository/cvs/gtb/PacketLib/include/Device.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Id: Device.h,v 1.2 2005/03/09 10:57:50 bulgarelli Exp $
//##	$Revision: 1.2 $
//##	\brief This class represent a Device for IO system.
class Device
{
    public:
        //##ModelId=3C87744002A0
        Device(bool bigendian);

        //##ModelId=3C87744002A2
        virtual bool isClosed() const;

        //##ModelId=3C87744002AB
        virtual bool isEOF() const;
        //##ModelId=3ACCD75E02EE
        //##Documentation
        //## Write property of bool endsession.
        virtual void setEndSession( const bool& _newVal);

        //##ModelId=3ACCD75E031C
        //##Documentation
        //## Read property of bool endsession.
        virtual const bool& getEndSession() const;

        //##ModelId=3EADC1270262
        virtual bool isBigEndian() const;

    protected:

        //##ModelId=3C8774400282
        bool eof;

        //##ModelId=3C8774400296
        bool closed;

        //##ModelId=3C8774400297
        bool bigendian;

        //##ModelId=3ACCD75E0242
        //##Documentation
        //## This variable indicates when a measurement session is terminated
        //## The device class have this attribute because this information is passed
        //## with the device.
        bool endsession;
};
}
#endif
