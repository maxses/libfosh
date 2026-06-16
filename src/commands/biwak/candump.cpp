/**---------------------------------------------------------------------------
 *
 * @file       candump.cpp
 * @brief      Libfosh command for dumping CAN traffic
 *
 *  \date      20260607
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/biwak/candump.hpp>
#include <lepto/log.h>
#include <biwak/can.hpp>
#include <cstdio>
#include <string.h>


/*--- Implementation--------------------------------------------------------*/


CCommandCanDump::CCommandCanDump(const char *name, CCan &can)
   :CCommand( name, "Dump CAN traffic" )
   ,m_can(can)
{
}


int CCommandCanDump::exec(int argc, const char *argv[]) const /* virtual */
{
   int in;
   
   if( argc != 1 )
   {
      if( ! strcmp( argv[1], "-w" ) )
      {
         SCanMessage message( 0x90, 0x0, (uint8_t*)"12345678" );
         printf("Send message\n");
         m_can.transmit( message );
      }
   }
   else
   {
      while( ( in = getc(stdin) ) == EOF )
      {
         SCanMessage *message;
         
         while( ( message=m_can.m_rxBuffer.frontEntry() ) )
         {
            printf( "  can0  %3X   [%d]  ", (unsigned int)message->getId(), message->getLen() );
            for(int i1=0; i1<message->getLen(); i1++)
            {
               printf( "%02X ", message->getData()[i1]);
            }
            printf( "\n" );
            
            m_can.m_rxBuffer.dropFront();
         }
      }
   }
   
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
