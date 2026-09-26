#ifndef FOSH_COMMAND_STOP_HPP
#define FOSH_COMMAND_STOP_HPP
/**---------------------------------------------------------------------------
 *
 * @file       stop.hpp
 * @brief      Libfosh command to put MCU into stop mode
 *
 *             Stop the MCU.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandStop: public CCommand
{
   public:
      CCommandStop(const char *_name)
         :CCommand( _name, "Stop device" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_STOP_HPP
