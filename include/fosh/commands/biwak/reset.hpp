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


/*--- Declaration ----------------------------------------------------------*/


class CCommandReset: public CCommand
{
   public:
      CCommandReset(const char *_name)
         :CCommand( _name, "Reset device" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_RESET_HPP
