/**---------------------------------------------------------------------------
 *
 * @file       i2c.cpp
 * @brief      Libfosh command for dumping i2c devices
 *
 *             Hardcoded stuff. Avoid including this command at the moment.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/biwak/i2c.hpp>


/*--- Implementation--------------------------------------------------------*/


int CCommandI2c::exec(int argc, const char *argv[]) const /* virtual */
{
   char cdata;
   int status;
   CI2cSlave slave(m_i2c, 0);

   if( argc >= 2 )
   {
      if( !strcmp(argv[1], "dump") )
      {
         // slave.setSlaveAddress(0x57);
         slave.setSlaveAddress(0x50);
         slave.setAddressWidth( CI2cSlave::EAddressSize::_8Bits );
         dump( slave );
      }
      
      if( !strcmp(argv[1], "d16") )
      {
         slave.setSlaveAddress(0x50);
         slave.setAddressWidth( CI2cSlave::EAddressSize::_16Bits );
         dump( slave );
      }
      
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
   }
   else
   {
      printf( "Scanning I2C devices...\n");
      slave.setAddressWidth( CI2cSlave::EAddressSize::_8Bits );
      for(int i1=0; i1<0x7f; i1++)
      {
         slave.setSlaveAddress(i1);
         // Reading zero bytes does not work
         status=slave.i2cReadData( &cdata, 1);
         if( status==0 )
         {
            printf( "Found slave at address 0x%02x\n", i1);
         }
      }
   }

   return(0);
}


void CCommandI2c::dump(const CI2cSlave &slave) const
{
   char cdata;
   int status;

   printf("Dump:\n");
   printf("    | -0 -1 -2 -3 -4 -5 -6 -7 -8 -9 -A -B -C -D -E -F\n");
   printf("----|------------------------------------------------\n");
   for(int i1=0; i1< 8; i1++)
   {
      printf(" %X- | ", i1);
      for(int i2=0; i2<0x10; i2++)
      {
         status=slave.i2cReadData( (i1*0x10)+i2, &cdata, 1);
         if(status)
         {
            printf("-- ");
         }
         else
         {
            printf("%02X ", cdata);
         }
      }
      printf("\n");
   }
}


/*--- Fin ------------------------------------------------------------------*/
