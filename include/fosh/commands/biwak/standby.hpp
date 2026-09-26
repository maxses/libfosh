#ifndef FOSH_COMMAND_STANDBY_HPP
#define FOSH_COMMAND_STANDBY_HPP
/**---------------------------------------------------------------------------
 *
 * @file       standby.hpp
 * @brief      Libfosh command to put MCU into standby
 *
 *             Put MCU into standby.
 *
 *  \date      20251203
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandStandby: public CCommand
{
   public:
      CCommandStandby(const char *_name)
         :CCommand( _name, "Standby device" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_STANDBY_HPP
