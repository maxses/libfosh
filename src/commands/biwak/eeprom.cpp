/**---------------------------------------------------------------------------
 *
 * @file       eeprom.cpp
 * @brief      Libfosh command for dumping eeprom
 *
 *             Hardcoded stuff. Avoid including this command at the moment.
 *
 *  \date      20260527
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/biwak/eeprom.hpp>
#include <stdio.h>
#include <lepto/log.h>


/*--- Implementation--------------------------------------------------------*/


int CCommandEeprom::exec(int argc, const char *argv[]) const /* virtual */
{
   char cdata;
   int status;

   if( argc >= 2 )
   {
      if( !strcmp(argv[1], "read") )
      {
         read();
      }
#if 0
      if( argv[1][0]== 'w')
      {
         slave.i2cWriteData( 0, "Hello World", 11);
      }

      if( argv[1][0]== 't')
      {
         slave.setSlaveAddress(0x50);

         printf("8 bit address width:\n");
         slave.setAddressWidth( CI2cSlave::EAddressSize::_8Bits );
         slave.i2cWriteData( 0, "Hello World", 11);
         dump( slave );

         printf("16 bit address width:\n");
         slave.setAddressWidth( CI2cSlave::EAddressSize::_16Bits );
         slave.i2cWriteData( 0, "Hello World", 11);
         dump( slave );
      }
#endif
   }
   else
   {
      dump( );
   }
   
   return(0);
}

// The fosh commands are executed 'const'
char eepromData[ 0x80 ];
char base64String[ 0xAC ];


void CCommandEeprom::dump( ) const
{
   char cdata;
   int status;
#if 1
   printf("Dump:\n");
   printf("    | -0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -A -B -C -D -E -F\n");
   printf("----|------------------------------------------------\n");
   for(int i1=0; i1< 8; i1++)
   {
      printf(" %X- | ", i1);
      for(int i2=0; i2<0x10; i2++)
      {
         status=m_eeprom.readData( m_eeprom.getStartAddress() + ( (i1*0x10)+i2 ), &cdata, 1);
         if(status)
         {
            printf("-- ");
         }
         else
         {
            printf("%02X ", cdata);
         }
      }
      printf( " | ");
      for(int i2=0; i2<0x10; i2++)
      {
         m_eeprom.readData( m_eeprom.getStartAddress() + ( (i1*0x10)+i2 ), &cdata, 1);
         {
            printf( "%c", ( ( cdata >='0' ) && ( cdata <='Z' ) ) ? cdata : '.' );
         }
      }
      printf("\n");
   }
#endif
   return;
}


void CCommandEeprom::read( ) const
{
   int status;
   
   status=m_eeprom.readData( m_eeprom.getStartAddress(), eepromData
            , sizeof(eepromData) );
   if(status)
   {
      printf( LDS("Err %d\n", "Error: %d\n"), status);
   }
   else
   {
      m_base64.encode((uint8_t*)eepromData, 0x80, (char*)base64String, 0xac);
      printf("%s\n", base64String);
   }
   
   return;
}


/*--- Fin ------------------------------------------------------------------*/
