#ifndef FOSH_COMMAND_EEPROM_HPP
#define FOSH_COMMAND_EEPROM_HPP
/**---------------------------------------------------------------------------
 *
 * @file       eeprom.hpp
 * @brief      Libfosh command for dumping eeprom devices
 *
 *             Hardcoded stuff. Avoid including this command for now.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>

#if defined(STM32)
   #include <biwak/flash_intern.hpp>
#else
   #include <biwak/flash_file.hpp>
#endif

#include <string.h>
#include <lepto/base64.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandEeprom: public CCommand
{
      // The fosh commands are executed 'const'
      static char eepromData[ 0x10 ];
      static char base64String[ 0x10 + 8 + 2 ];

      CFlash &m_eeprom;
      CBase64 m_base64;
      
   public:
      CCommandEeprom(const char *name, CFlash &eeprom)
         :CCommand( name, "Dump EEPROMs" )
         ,m_eeprom(eeprom)
      {}
      virtual int exec(int argc, const char *argv[]) const;
      void dump() const;
      void read( ) const;
      void write( int argc, const char *argv[] ) const;
      void info( ) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_EEPROM_HPP
