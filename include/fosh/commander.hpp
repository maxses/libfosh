#ifndef FOSH_COMMANDER_HPP
#define FOSH_COMMANDER_HPP
/**---------------------------------------------------------------------------
 *
 * @file       commander.hpp
 * @brief      Libfosh container for all commands
 *
 *             Holds a list of all available commands. 
 *             The commander is asked to run a command by given strings.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <lepto/list.hpp>

#if ! defined CONFIG_FOSH_COMMANDS
   #define CONFIG_FOSH_COMMANDS  7
#endif


/*--- Declaration ----------------------------------------------------------*/


class CCommand;

class CCommander
{
      CList<const CCommand *> commandList;

   public:
      CCommander();
      int registerCommands();
      int execCommand( int argc, const char *argv[] );
      const CCommand *findCommand( const char *cmd, int &matchCommandIndex );
      int printHelp();
      void addCommand(const CCommand *command)
      {
         commandList.push_back( command );
         return;
      }

};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMANDER_HPP
