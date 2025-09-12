#ifndef FOSH_COMMAND_INFO_HPP
#define FOSH_COMMAND_INFO_HPP
/**---------------------------------------------------------------------------
 *
 * @file       info.hpp
 * @brief      Libfosh command for dumping device information
 *
 *             Biwak info functions are calles.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandInfo: public CCommand
{
   private:

   public:
      CCommandInfo(const char *_name)
         :CCommand( _name, "Print system info" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_INFO_HPP
