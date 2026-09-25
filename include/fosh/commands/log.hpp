#ifndef FOSH_COMMAND_LOG_HPP
#define FOSH_COMMAND_LOG_HPP
/**---------------------------------------------------------------------------
 *
 * @file       log.hpp
 * @brief      Libfosh command for generating logs
 *
 *             Mostly for testing logging and heartbeat and demonstration.
 *
 * @date       20260416
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>
#include <lepto/ansi.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandLog: public CCommand
{
   public:
      CCommandLog(const char *_name)
         :CCommand( _name, "Test logging behaviour" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_COMMAND_CLEAR_HPP
