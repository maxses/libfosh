/**---------------------------------------------------------------------------
 *
 * @file       spi_flash.cpp
 * @brief      Libfosh command for spi flash
 *
 *             Just prints some informaation like JEDEC ID.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/biwak/spi_flash.hpp>
#include <lepto/log.h>
#include <lepto/print.h>


/*--- Implementation -------------------------------------------------------*/


int CCommandSf::execSubCommand(ESfCommand command, int argc, const char *argv[]) const /* virtual */
{
   switch( command )
   {
      case eNone:
      case eInfo:
         return( info() );
         break;
      case eDump:
         return( dump(argc, argv) );
         break;
      case eWrite:
         return( write(argc, argv) );
         break;
      case eChipErase:
         return( chipErase() );
         break;
      case eSearch:
         return( search() );
         break;
      default:
         lWarning("Unknown command: %d", (int)command);
         break;
   }

   return(0);
}


int CCommandSf::info() const
{
   printf( "Id: 0x%X\n", m_sf.readId() );
   printf( "Jedec-Id: 0x%X\n", m_sf.readJedecId() );
   printf( "Size: %d\n", m_sf.size() );
   printf( "Erase block size: %d\n", m_sf.eraseBlockSize() );
   return(0);
}


int CCommandSf::dump(int argc, const char* argv[]) const
{
   printf("argc: %d\n", argc);
   printf("argv[0]: %s\n", argv[0]);
   int address;
   if( optArg( address, 1, argc, argv) < 0 )
   {
      lCritical("Could not parse block");
      return(-1);
   }
   char buf[0x100];
   memset(buf, 0x12, sizeof(buf));
   printf("Dumping address %d/0x%X\n", address, address);
   m_sf.readData( address /* * m_sf.eraseBlockSize() */, buf, 0x100 );
   hexDump(buf, 0x100);
   
   return(0);
}


int CCommandSf::write(int argc, const char* argv[]) const
{
   int address;
   if( optArg( address, 1, argc, argv) < 0 )
   {
      lCritical("Could not parse block");
      return(-1);
   }
   printf("Writing block %d/0x%X\n", address, address);
   m_sf.writeData( address , "Hello World", 11 );
   
   return(0);
}


int CCommandSf::chipErase() const
{
   return( m_sf.chipErase() );
}


int CCommandSf::search() const
{
   char buf[0x100];
   
   for(int i1=0; i1<m_sf.size()/m_sf.writePageSize(); i1++)
   {
      memset(buf, 0x12, sizeof(buf));
      m_sf.readData( i1 * m_sf.writePageSize(), buf, 0x100 );
      for(int i2=0; i2<0x100; i2++)
      {
         if( (unsigned char)buf[i2] != 0xff )
         {
            printf("Diff: Address %d\n", i1 * m_sf.writePageSize() );
            return(0);
         }
      }
      if(i1)
      {
         if( (i1 % ( 64 * 2 ) ) == 0 )
         {
            printf(".");
         }
         if( (i1 % ( 1024 * 4 ) ) == 0 )
         {
            printf(" %d KB\n", ( i1 * m_sf.writePageSize() ) / 1024);
         }
      }
   }
   
   printf("No data at all\n");
   
   return( 0 );
}


/*--- Fin ------------------------------------------------------------------*/
