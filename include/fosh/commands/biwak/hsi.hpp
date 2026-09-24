#ifndef FOSH_COMMAND_HSI_HPP
#define FOSH_COMMAND_HSI_HPP
/**---------------------------------------------------------------------------
 *
 * @file       hsi.hpp
 * @brief      Libfosh command for setting HSI calibration
 *
 *  \date      20260710
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>

#if defined(STM32)
   #include <biwak/voc.h>
   #include <biwak/flash_spi.hpp>
   #include <biwak/rcc.h>
   #include <HALWrapper/stm32_rcc.h>
   #include <HALWrapper/stm32_gpio.h>
   #include <HALWrapper/stm32_sup.h>
   #include <lepto/signal.hpp>
#else
   #include <biwak/i2c.hpp>
   #include <biwak/i2c_slave.h>
#endif


/*--- Declaration ----------------------------------------------------------*/


class CCommandHsi: public CCommand
{
   public:
      CSignal<void, int> signalSetHsiConfig;
      CCommandHsi(const char *_name)
         :CCommand( _name, "Set HSI calibration" )
      {}
      virtual int exec(int argc, const char *argv[]) const
      {
         if( argc < 2 )
         {
            printf("hsi <calibration>\n");
         }
         
         int cal=strtod( argv[1], nullptr );
         adjustClockCalibration( cal );
         
         printf("HSI calib. set to %d\n", cal);
         signalSetHsiConfig.emitSignal( cal );
         return(0);
      }
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_I2C_HPP
