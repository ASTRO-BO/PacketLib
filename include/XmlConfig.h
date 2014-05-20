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
#include <map>
#include "pugixml.h"

namespace PacketLib
{

class XmlConfig
{

	const static std::string _fixed32[];
	const static std::string _fixed64[];

	std::map<pugi::xml_node, int> _physicalIndex;

	void _cachePhysicalIndexes(pugi::xml_node node);
	void _writeFields(pugi::xml_node parent, std::fstream& fs);

	void _writeRBlock(pugi::xml_node rblock, std::fstream& fs, pugi::xml_document& doc);

public:

	std::string convert(const std::string& filename);
};

}

#endif
