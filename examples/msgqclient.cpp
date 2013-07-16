/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Thu Dec  5 08:23:25 CET 2002
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
    char* mtext = new char[SENDER_MSGQ_LEN];

    MSGQ msgq(true); //creo l'oggetto

    msgq.open(10000, SENDER_MSGQ_LEN); //apro la message queue

    //setto i valori da scrivere
    for(int i = 0; i < SENDER_MSGQ_LEN; i++)
      mtext[i] = 35;

    //scrivo il packet
    msgq.writeMessage(mtext, (long)SENDER_MSG_TYPE);

    cout << "End of the program" << endl;
  }
  catch(PacketException* e) {
    cout << e->geterror() << endl;
  }
}
