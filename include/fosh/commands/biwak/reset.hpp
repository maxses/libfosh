#ifndef FOSH_COMMAND_RESET_HPP
#define FOSH_COMMAND_RESET_HPP
/**---------------------------------------------------------------------------
 *
 * @file       reset.hpp
 * @brief      Libfosh command for restarting MCU
 *
 *             Reset the MCU.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>
#include <HALWrapper/stm32_hal.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandReset: public CCommand
{
   public:
      CCommandReset(const char *_name)
         :CCommand( _name, "Reset device" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


int CCommandReset::exec(int argc, const char *argv[]) const /* virtual */
{
   lUNUSED( argc );
   lUNUSED( argv );
   
   NVIC_SystemReset();
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_RESET_HPP
