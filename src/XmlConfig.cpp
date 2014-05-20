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
#include <bitset>
#include <vector>

namespace PacketLib
{

using namespace pugi;
using namespace std;

void XmlConfig::_writeFields(xml_node parent, fstream& fs)
{
	const string fixedStrings[] = { "uint32", "uint64", "int32", "int64", "float", "double" };

	unsigned int counter = 0;
	for(pugi::xml_node_iterator it=parent.begin(); it != parent.end(); ++it)
	{
		if(string(it->name()).compare("field") != 0)
			continue;

		fs << "-- field " << counter << endl;
		fs << it->attribute("name").value() << endl;
		string typeStr = it->attribute("type").value();
		bool found = false;
		for(unsigned int i=0; i<6; i++)
		{
			if(typeStr.compare(fixedStrings[i]) == 0)
			{
				fs << typeStr << endl;
				found = true;
				break;
			}
		}

		string::size_type spos = typeStr.find_first_of("0123456789");
		string::size_type epos = typeStr.find_last_of("0123456789");
		int nbits = atoi(typeStr.substr(spos, epos+1).c_str());

		if(!found)
			fs << nbits << endl;

		xml_attribute defaultt = it->attribute("default");
		if(!defaultt)
			fs << "none" << endl;
		else
		{
			bitset<64> x(atoi(defaultt.value()));
			fs << "0b" << x.to_string().substr(64-nbits, 64) << endl;
		}
		counter++;
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
				string query = string("//field[@id=\"")+idref.value()+"\"]";
				xml_node numberofblocksid = doc.select_nodes(query.c_str())[0].node();
				xml_node nodetmp = rblocks[i];
				unsigned int level = 0;
				while(nodetmp.parent() != numberofblocksid.parent())
					level++;
				fs << level << endl;
				fs << "-- for variable block, index of field of the header which rappresent the number of events (the number of blocks) of the packet" << endl;
				unsigned int index = 0;
				nodetmp = numberofblocksid;
				while(nodetmp.previous_sibling())
				{
					index++;
					nodetmp = nodetmp.previous_sibling();
				}
				fs << index << endl;
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

	xml_node stream = doc.child("stream");
	string streamFilename = string(stream.attribute("name").value()) + ".stream";
	fstream sfs;
	sfs.open(streamFilename.c_str(), ios_base::out);

	xml_node header = stream.child("header");
	string headerFilename = string(header.attribute("name").value()) + ".header";
	fstream hfs;
	hfs.open(headerFilename.c_str(), ios_base::out);

	xml_node packet = stream.child("packet");
	string packetFilename = string(packet.attribute("name").value()) + ".packet";
	fstream pfs;
	pfs.open(packetFilename.c_str(), ios_base::out);

	// Write stream file
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
	sfs << packetFilename << endl;

	// Write header file
#ifdef DEBUG
    cout << "Writing " << headerFilename << " .." << endl;
#endif
	hfs << "-- name of header" << endl;
	hfs << header.attribute("description").value() << endl;
	hfs << "-- number of field with dimension of packet (or first field if dim of packet is stored in a 32 bit field)" << endl;
	string query = string("//field[@id=\"")+header.attribute("idref").value()+"\"]";
	xml_node packetLength = doc.select_nodes(query.c_str())[0].node();
	unsigned int counter = 0;
	xml_node nodetmp = packetLength;
	while(nodetmp.previous_sibling())
	{
		counter++;
		nodetmp = nodetmp.previous_sibling();
	}
	hfs << counter << endl;
	hfs << "-- 16 or 32 bit size dimension of the packet lenght" << endl;
	string typeStr = packetLength.attribute("type").value();
	string::size_type spos = typeStr.find_first_of("0123456789");
	string::size_type epos = typeStr.find_last_of("0123456789");
	int nbits = atoi(typeStr.substr(spos, epos+1).c_str());
	hfs << nbits << endl;

	hfs << "[Field]" << endl;
	_writeFields(header, hfs);

	// Write packet file
#ifdef DEBUG
    cout << "Writing " << packetFilename << " .." << endl;
#endif
	pfs << "-- name of packet" << endl;
	pfs << packet.attribute("description").value() << endl;
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
	xpath_node_set packetids = doc.select_nodes("//field[@packetid]");
	counter = 0;
	for(xpath_node_set::const_iterator it = packetids.begin(); it != packetids.end(); ++it)
	{
		pfs << "-- ID" << counter << endl;
		pfs << "-- field number" << endl;
		xml_node node = it->node();
		unsigned int counter = 0;
		xml_node nodetmp = node;
		while(nodetmp.previous_sibling())
		{
			counter++;
			nodetmp = nodetmp.previous_sibling();
		}
		pfs << counter << endl;
		pfs << "-- type (0 header, 1 data field, 2 source data field)" << endl;
		string parentName = node.parent().name();
		int index = -1;
		if(parentName.compare("header") == 0)
			index = 0;
		else if(parentName.compare("datafieldheader") == 0)
			index = 1;
		else if(parentName.compare("sourcedatafield") == 0)
			index = 2;
		pfs << index << endl;
		pfs << "-- value" << endl;
		pfs << node.attribute("packetid").value() << endl;

		counter++;
	}
	pfs << "[Tail]" << endl;
	xml_node tail = packet.child("tail");
	_writeFields(tail, pfs);

	return streamFilename;
}

}
