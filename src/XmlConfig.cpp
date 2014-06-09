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

#include "XmlConfig.h"

#include <iostream>
#include <cstdlib>
#include <vector>

namespace PacketLib
{

using namespace pugi;
using namespace std;

const std::string XmlConfig::_fixed32[] = { "uint32", "int32", "float" };
const std::string XmlConfig::_fixed64[] = { "uint64", "int64", "double" };

void XmlConfig::_cachePhysicalIndexes(xml_node node)
{
	unsigned int index = 0;
	for(pugi::xml_node_iterator it=node.begin(); it != node.end(); ++it)
	{
		if(string(it->name()).compare("field") != 0)
			continue;

		_physicalIndex[*it] = index;

		// if 32bits fields
		string typeStr = it->attribute("type").value();
		bool found = false;
		for(unsigned int i=0; i<3; i++)
		{
			if(typeStr.compare(_fixed32[i]) == 0)
			{
				index+=2;
				found = true;
				break;
			}
		}
		if(found)
			continue;

		// if 64bits fields
		for(unsigned int i=0; i<3; i++)
		{
			if(typeStr.compare(_fixed64[i]) == 0)
			{
				index+=4;
				found = true;
				break;
			}
		}
		if(found)
			continue;

		// else (<= 16bits fields)
		index++;
	}
}

void XmlConfig::_writeFields(xml_node parent, fstream& fs)
{
	unsigned int index = 0;
	for(pugi::xml_node_iterator it=parent.begin(); it != parent.end(); ++it)
	{
		if(string(it->name()).compare("field") != 0)
			continue;

		// write 32bits fields
		fs << "-- field " << index << endl;
		string name = it->attribute("name").value();
		fs << name << endl;
		string typeStr = it->attribute("type").value();
		bool found = false;
		for(unsigned int i=0; i<3; i++)
		{
			if(typeStr.compare(_fixed32[i]) == 0)
			{
				fs << "16" << endl;
				fs << "none" << endl;
				index++;

				fs << "-- field " << index << endl;
				fs << name+"__2" << endl;
				fs << "16" << endl;
				fs << "none" << endl;
				index++;

				found = true;
				break;
			}
		}
		if(found)
			continue;

		// write 64bits fields
		for(unsigned int i=0; i<3; i++)
		{
			if(typeStr.compare(_fixed64[i]) == 0)
			{
				fs << "16" << endl;
				fs << "none" << endl;

				fs << "-- field " << index << endl;
				fs << name+"__2" << endl;
				fs << "16" << endl;
				fs << "none" << endl;
				index++;

				fs << "-- field " << index << endl;
				fs << name+"__3" << endl;
				fs << "16" << endl;
				fs << "none" << endl;
				index++;

				fs << "-- field " << index << endl;
				fs << name+"__4" << endl;
				fs << "16" << endl;
				fs << "none" << endl;
				index++;

				found = true;
				break;
			}
		}
		if(found)
			continue;

		// write <= 16 bits fields
		string::size_type spos = typeStr.find_first_of("0123456789");
		string::size_type epos = typeStr.find_last_of("0123456789");
		int nbits = atoi(typeStr.substr(spos, epos+1).c_str());
		fs << nbits << endl;

		xml_attribute constvalue = it->attribute("constvalue");
		if(!constvalue)
			fs << "none" << endl;
		else
			fs << constvalue.value() << endl;
		index++;
	}
}

void XmlConfig::_writeRBlock(xml_node rblock, fstream& fs, xml_document& doc)
{
#ifdef DEBUG
	if(string(rblock.name()).compare("rblock") == 0)
		std::cout << "Writing " << rblock.attribute("name").value() << ".rblock .." << endl;
#endif

	fs << "[RBlock Configuration]" << endl;
	fs << "-- fixed part present (yes | no)" << endl;
	if(rblock.child("field"))
		fs << "yes" << endl;
	else
		fs << "no" << endl;
	fs << "-- variable part present (yes | no). If yes, add [RBlockX] sections." << endl;
	vector<xml_node> rblocks;
	for(pugi::xml_node_iterator it=rblock.begin(); it != rblock.end(); ++it)
		if(string(it->name()).compare("rblock") == 0)
			rblocks.push_back(*it);
	if(rblocks.size() > 0)
	{
		fs << "yes" << endl;
		fs << "--number of rblock (if variable part is present)" << endl;
		fs << rblocks.size() << endl;
	}
	else
		fs << "no" << endl;
	if(rblock.child("field"))
	{
		fs << "[Fixed Part]" << endl;
		_writeFields(rblock, fs);
	}

	if(rblocks.size() > 0)
	{
		for(unsigned int i=0; i<rblocks.size(); i++)
		{
			fs << "[RBlock" << i+1 << "]" << endl;
			fs << "--type of number of blocks of this variable part: fixed = number of block fixed equals to max number of block (fixed | variable)" << endl;
			xml_attribute idref = rblocks[i].attribute("idref");
			if(idref)
				fs << "variable" << endl;
			else
				fs << "fixed" << endl;
			fs << "--number of blocks for fixed value into variable part, max number of blocks for variable value into variable part" << endl;
			fs << rblocks[i].attribute("maxnumberofblocks").value() << endl;
			fs << "-- for variable block, number of level of headers in which is present the field with the number of blocks of the variable part (0: fixed part)" << endl;
			if(!idref)
				fs << "0" << endl;
			else
			{
#ifdef DEBUG
				cout << "rblock name='" << rblocks[i].attribute("name").value() << "' idref='" << rblocks[i].attribute("idref").value() << "' ";
#endif
				string query = string("//field[@id=\"")+idref.value()+"\"]";
				xml_node numberofblocksid = doc.select_nodes(query.c_str())[0].node();
				xml_node nodetmp = rblocks[i];
				unsigned int level = 0;

				while(nodetmp.parent() != numberofblocksid.parent())
				{
					// if the parent is a packet means that the id is not in the fixed part of the
					// recursive rblocks nor the sourcedatafield. So test the datafieldheader
					// and header, otherwise complain.
					if(string(nodetmp.parent().name()).compare("packet") == 0)
					{
						string idparentnodename = numberofblocksid.parent().name();
						if(idparentnodename.compare("datafieldheader") == 0)
						{
							// we have already add 1 level because nodetmp in this case is
							// the sourcedatafield node
						}
						else if(idparentnodename.compare("header") == 0)
						{
							// we add just one level for the same reason above
							level++;
						}
						else
						{
							cerr << "Error on id association. Id '" << idref.value() << "' doesn't exists. ";
							cerr << "idref defined by rblock '" << rblocks[i].attribute("name").value() << "'." << endl;
							exit(0);
						}

						break;
					}
					level++;
					nodetmp = nodetmp.parent();
				}
#ifdef DEBUG
				cout << "levels=" << level << endl;
#endif
				fs << level << endl;
				fs << "-- for variable block, index of field of the header which rappresent the number of events (the number of blocks) of the packet" << endl;
				fs << _physicalIndex[numberofblocksid] << endl;
				fs << "-- for variable block, value to sum to get the real number of events (blocks)" << endl;
				xml_attribute offset = numberofblocksid.attribute("numberofblocksoffset");
				if(offset)
					fs << offset.value() << endl;
				else
					fs << "0" << endl;
			}
			string rblockFilename=rblocks[i].attribute("name").value();
			rblockFilename+=".rblock";
			fs << rblockFilename << endl;

			fstream rfs;
			rfs.open(rblockFilename.c_str(), ios_base::out);
			_writeRBlock(rblocks[i], rfs, doc);
			rfs.close();
		}
	}
}

std::string XmlConfig::convert(const std::string& filename)
{
    xml_document doc;

    if (!doc.load_file(filename.c_str()))
    {
        cerr << "Cannot load " << filename << endl;
        return "";
    }

	// cache all the field physical indexes
	xpath_node_set fieldParents = doc.select_nodes("//*[field]");
	for(xpath_node_set::const_iterator it = fieldParents.begin(); it != fieldParents.end(); ++it)
		_cachePhysicalIndexes(it->node());

	xml_node stream = doc.child("stream");
	string streamFilename = string(stream.attribute("name").value()) + ".stream";

	xml_node header = stream.child("header");
	string headerFilename = string(header.attribute("name").value()) + ".header";

	/// Write header file
	fstream hfs;
	hfs.open(headerFilename.c_str(), ios_base::out);
#ifdef DEBUG
    cout << "Writing " << headerFilename << " .." << endl;
#endif
	hfs << "-- name of header" << endl;
	hfs << header.attribute("description").value() << endl;
	hfs << "-- number of field with dimension of packet (or first field if dim of packet is stored in a 32 bit field)" << endl;
	string query = string("//field[@id=\"")+header.attribute("idref").value()+"\"]";
	xml_node packetLength = header.select_nodes(query.c_str())[0].node();
	hfs << _physicalIndex[packetLength] << endl;
	hfs << "-- 16 or 32 bit size dimension of the packet lenght" << endl;
	string typeStr = packetLength.attribute("type").value();
	string::size_type spos = typeStr.find_first_of("0123456789");
	string::size_type epos = typeStr.find_last_of("0123456789");
	int nbits = atoi(typeStr.substr(spos, epos+1).c_str());
	hfs << nbits << endl;
	hfs << "[Field]" << endl;
	_writeFields(header, hfs);
	// query for compression algorithm / compression level
	xpath_node_set compression_algorithm = header.select_nodes("field[@id=\"packetlib:compression_algorithm\"]");
	xpath_node_set compression_level = header.select_nodes("field[@id=\"packetlib:compression_level\"]");

	/// Write packet files
	vector<string> packetFilenames;
	xml_node packet = stream.child("packet");
	fstream pfs;
	while(packet)
	{
		string packetFilename = string(packet.attribute("name").value()) + ".packet";
		packetFilenames.push_back(packetFilename);
		pfs.close();
		pfs.open(packetFilename.c_str(), ios_base::out);
#ifdef DEBUG
	    cout << "Writing " << packetFilename << " .." << endl;
#endif
		pfs << "-- name of packet - " << packet.attribute("description").value() << endl;
		pfs << packet.attribute("name").value() << endl;
		pfs << "[PacketHeader]" << endl;
		pfs << "-- file that contains the description of the header" << endl;
		pfs << headerFilename << endl;
		pfs << "[DataFieldHeader]" << endl;
		xml_node datafieldheader = packet.child("datafieldheader");
		_writeFields(datafieldheader, pfs);
		pfs << "[SourceDataField]" << endl;
		pfs << "-- type of packet: noblock, block, rblock (with recoursive block)" << endl;
		pfs << "rblock" << endl;
		xml_node sourcedatafield = packet.child("sourcedatafield");
		_writeRBlock(sourcedatafield, pfs, doc);
		pfs << "[Identifiers]" << endl;
		xpath_node_set packetids = packet.select_nodes("identifiers/identifier");
		unsigned int counter = 0;
		for(xpath_node_set::const_iterator it = packetids.begin(); it != packetids.end(); ++it)
		{
			pfs << "-- ID" << counter << endl;
			pfs << "-- field number" << endl;
			xml_node identifier = it->node();
			string query = string("//field[@id=\"")+identifier.attribute("idref").value()+"\"]";
			xml_node fieldid = doc.select_nodes(query.c_str())[0].node();
			pfs << _physicalIndex[fieldid] << endl;
			pfs << "-- type (0 header, 1 data field, 2 source data field)" << endl;
			string parentName = fieldid.parent().name();
			int index = -1;
			if(parentName.compare("header") == 0)
				index = 0;
			else if(parentName.compare("datafieldheader") == 0)
				index = 1;
			else if(parentName.compare("sourcedatafield") == 0)
				index = 2;
			pfs << index << endl;
			pfs << "-- value" << endl;
			pfs << identifier.attribute("value").value() << endl;

			counter++;
		}
		xml_node tail = packet.child("tail");
		if(tail)
		{
			pfs << "[Tail]" << endl;
			_writeFields(tail, pfs);
		}

		// if not defined in the header find in datafieldheader
		int algindex = 0;
		if(compression_algorithm.empty())
		{
			compression_algorithm = datafieldheader.select_nodes("field[@id=\"packetlib:compression_algorithm\"]");
			algindex = 1;
		}
		// and sourcedatafield
		if(compression_algorithm.empty())
		{
			algindex = 2;
			compression_algorithm = sourcedatafield.select_nodes("@field[id=\"packetlib:compression_algorithm\"]");
		}

		// if not defined in the header find in datafieldheader
		int lvlindex = 0;
		if(compression_level.empty())
		{
			compression_level = datafieldheader.select_nodes("field[@id=\"packetlib:compression_level\"]");
			lvlindex = 1;
		}
		// and sourcedatafield
		if(compression_level.empty())
		{
			lvlindex = 2;
			compression_level = sourcedatafield.select_nodes("@field[id=\"packetlib:compression_level\"]");
		}

		if(!compression_algorithm.empty() && !compression_level.empty())
		{
			pfs << "[Compression]" << endl;
			pfs << _physicalIndex[compression_algorithm[0].node()] << endl;
			pfs << algindex << endl;
			pfs << _physicalIndex[compression_level[0].node()] << endl;
			pfs << lvlindex << endl;
		}

		packet=packet.next_sibling();
	}

	/// Write stream file
	fstream sfs;
	sfs.open(streamFilename.c_str(), ios_base::out);
#ifdef DEBUG
    cout << "Writing " << streamFilename << " .." << endl;
#endif
	sfs << "[Configuration]" << endl;
	bool prefix = false;
	sfs << "--prefix" << endl;
	if(prefix)
		sfs << "true" << endl;
	else
		sfs << "false" << endl;
	sfs << "--stream format bigendian" << endl;
	xml_attribute bigendian = stream.attribute("bigendian");
	if(!bigendian)
		sfs << "false" << endl;
	else
		sfs << bigendian.value() << endl;
	sfs << "--dimension of prefix" << endl;
	xml_attribute prefixsize = stream.attribute("prefixsize");
	if(!prefixsize)
		sfs << "0" << endl;
	else
		sfs << prefixsize.value() << endl;
	sfs << "[Header Format]" << endl;
	sfs << headerFilename << endl;
	sfs << "[Packet Format]" << endl;
	for(unsigned int i=0; i<packetFilenames.size(); i++)
		sfs << packetFilenames[i] << endl;

#ifdef DEBUG
	cout << "Conversion complete." << endl;
#endif
	return streamFilename;
}

}
