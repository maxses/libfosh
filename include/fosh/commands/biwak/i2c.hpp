#ifndef FOSH_COMMAND_I2C_HPP
#define FOSH_COMMAND_I2C_HPP
/**---------------------------------------------------------------------------
 *
 * @file       i2c.hpp
 * @brief      Libfosh command for dumping i2c devices
 *
 *             Hardcoded stuff. Avoid including this command for now.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>

#if defined(STM32)
   //#include <arena/platform.h>
   #include <biwak/voc.h>
   #include <biwak/flash_spi.hpp>
#else
   #include <biwak/i2c.hpp>
   #include <biwak/i2c_slave.h>
#endif

#include <string.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandI2c: public CCommand
{
      CI2c &m_i2c;
   public:
      CCommandI2c(const char *_name, CI2c &i2c)
         :CCommand( _name, "   i2c: scan devices\n" )
         ,m_i2c(i2c)
      {}
      virtual int exec(int argc, const char *argv[]) const;
      void dump(const CI2cSlave &slave) const;
      virtual void printHelp() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_I2C_HPP
