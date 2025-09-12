#ifndef FOSH_COMMAND_CLEAR_HPP
#define FOSH_COMMAND_CLEAR_HPP
/**---------------------------------------------------------------------------
 *
 * @file       clear.hpp
 * @brief      Libfosh command for clearing the screen
 *
 *             Ansi commands are used so this command works also on UART 
 *             terminals.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>
#include <lepto/ansi.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandClear: public CCommand
{
   public:
      CCommandClear(const char *_name)
         :CCommand( _name, "Clear screen" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
      virtual void printHelp() const
      {
         printf("Usage: \n");
      }
};


int CCommandClear::exec(int argc, const char *argv[]) const /* virtual */
{
   printf( ANSI_RESET ANSI_CLEARSCREEN ANSI_HOME );
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_COMMAND_CLEAR_HPP
