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
#include <lepto/print.h>


/*--- Implementation--------------------------------------------------------*/


// The fosh commands are executed 'const'
char CCommandEeprom::eepromData[ 0x10 ];
char CCommandEeprom::base64String[ 0x10 + 8 + 2 ];


int CCommandEeprom::exec(int argc, const char *argv[]) const /* virtual */
{
   if( argc >= 2 )
   {
      if( !strcmp(argv[1], "read") )
      {
         read();
      }
      else if( !strcmp(argv[1], "write") )
      {
         write( argc, argv );
      }
      else if( !strcmp(argv[1], "info") )
      {
         info( );
      }
      else
      {
         printf("Unknown subcommand '%s'\n", argv[1]);
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


void CCommandEeprom::dump( ) const
{
   char cdata;
   int status;
#if 1
   printf("Dump:\n");
   
   #if IS_ENABLED( CONFIG_FOSH_PRINT_HEADERS )
      printf("    | -0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -A -B -C -D -E -F\n");
      printf("----|------------------------------------------------\n");
   #endif
   
   for(int i1=0; i1< 8; i1++)
   {
      printf(" %X- | ", i1);
      for(int i2=0; i2<0x10; i2++)
      {
         status=m_eeprom.readData( getStartAddress() + ( (i1*0x10)+i2 ), &cdata, 1);
         if(status)
         {
            printf("-- ");
         }
         else
         {
            printf("%02X ", (int)(unsigned char)cdata);
         }
      }
      printf( " | ");
      for(int i2=0; i2<0x10; i2++)
      {
         m_eeprom.readData( getStartAddress() + ( (i1*0x10)+i2 ), &cdata, 1);
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
   
   for(int i1=0; i1 < (int)( flashSize() / sizeof(eepromData) ); i1++)
   {
      status=m_eeprom.readData( getStartAddress() + ( sizeof(eepromData) * i1 )
               , eepromData , sizeof(eepromData) );
      if(status)
      {
         printf( LDS("Err %d\n", "Error: %d\n"), status);
      }
      else
      {
         m_base64.encode((uint8_t*)eepromData, sizeof(eepromData), (char*)base64String, sizeof(base64String));
         printf("%s\n", base64String);
      }
   }
   
   return;
}


void CCommandEeprom::write( int argc, const char *argv[] ) const
{
   int status;
   int c;
   int inPos=0;
   int outPos=0;
   int size;
   
   (void)argc;
   (void)argv;

   #if 0
   if( argc < 4 )
   {
      printf("Usage: eeprom write <offset> <base64>\n");
      return;
   }
   printf("Offset: 0x%X\n", strtol( argv[2], nullptr, 0 ) );
   #endif

   #if 1
   
   // Needed for stm32l0 internal eeprom; nor flash not supported.
   m_eeprom.erasePage( getStartAddress(), 1 );
       
   while( outPos < flashSize() )
   {
      inPos=0;
      do
      {
         while( ( c = getchar( ) ) == -1 )
         {
         }
         base64String[ inPos++ ] = c;
      }while( ( inPos < (int)sizeof(base64String) ) && ( c != '\n' ) && ( c != '\r' ) );
      
      if( inPos >= (int)sizeof(base64String) )
      {
         printf("Overflow\n");
         return;
      }
      base64String[ --inPos ] = 0;
      if( inPos <= 0 )
      {
         break;
      }
      
      // printf( "String: %s; %d\n", base64String, strlen(base64String) );

      size=m_base64.decode( (char*)base64String, strlen(base64String), (uint8_t*)eepromData, sizeof(eepromData) );
      
      if( size<=0)
      {
         lCritical( LDS("CNDe", "Could not decode") );
         return;
      }
      
      if( size > (int)sizeof(eepromData) )
      {
         lFatal( LDS("UP", "Unplausible") );
      }

      status=m_eeprom.writeData( getStartAddress() + outPos
               , eepromData , size );
      outPos+=size;
      if(status)
      {
         lCritical( LDS("WErr %d", "Write error: %d"), status);
         return;
      }

      printf("Wrote %d bytes; Output now @0x%X\n", size, outPos);
      // hexDump(eepromData, size);
   }

   printf("Finished\n");

   #endif

   return;
}


void CCommandEeprom::info( ) const
{
   printf("Size: %d Bytes\n", flashSize());
}


/*--- Fin ------------------------------------------------------------------*/
