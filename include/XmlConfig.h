/***************************************************************************
    begin                : Tue May 20 2014
    copyright            : (C) 2014 Andrea Zoli
    email                : zoli@iasfbo.inaf.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PACKETLIB_XMLCONFIG_H
#define PACKETLIB_XMLCONFIG_H

#include <string>
#include <fstream>
#include "pugixml.h"

namespace PacketLib
{

class XmlConfig
{
	void _writeRBlock(pugi::xml_node rblock, std::fstream& fs, pugi::xml_document& doc);
	void _writeFields(pugi::xml_node parent, std::fstream& fs);

public:

	std::string convert(const std::string& filename);
};

}

#endif
