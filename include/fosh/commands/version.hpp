#ifndef FOSH_COMMAND_VERSION_HPP
#define FOSH_COMMAND_VERSION_HPP
/**---------------------------------------------------------------------------
 *
 * @file       version.hpp
 * @brief      Libfosh command for showing git version information
 *
 * @date       20260608
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include "git_version.h"


/*--- Declarations ---------------------------------------------------------*/


class CCommandVersion: public CCommand
{
   public:
      CCommandVersion(const char *_name)
         :CCommand( _name, "Show info git version" )
      {}
      virtual int exec(int argc, const char *argv[]) const override;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_COMMAND_VERSION_HPP
