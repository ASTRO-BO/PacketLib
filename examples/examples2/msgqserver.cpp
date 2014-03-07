/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Thu Dec  5 08:00:28 CET 2002
    copyright            : (C) 2002 by Andrea Bulgarelli
    email                : bulgarelli@bo.iasf.cnr.it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream.h>
#include <stdlib.h>
#include "MSGQ.h"
#include "PacketException.h"

using namespace PacketLib;

#define  SENDER_MSGQ_LEN  255
#define  SENDER_MSG_TYPE  10

int main(int argc, char *argv[])
{
  try {
    char* buf;

    MSGQ msgq(true);
    msgq.create(10000, SENDER_MSGQ_LEN);
    cout << "Wait for a message..." << endl;

    buf = msgq.readMessage(SENDER_MSG_TYPE);

    for(int i=0; i< SENDER_MSGQ_LEN; i++)
      cout << buf[i];

    msgq.destroy();
    cout << "End of the program" << endl;
  }
  catch(PacketException* e) {
    cout << e->geterror() << endl;
  }

}
