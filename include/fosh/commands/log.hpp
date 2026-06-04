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
 * @author     Maximilian Seesslen <mes@seesslen.net>
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


int CCommandLog::exec(int argc, const char *argv[]) const /* virtual */
{
   const char *message;
   if( argc < 2 )
   {
      lWarning("No argument specified");
      return(0);
   }
   
   if( argc < 3 )
   {
      message="No Text";
   }
   else
   {
      message=argv[2];
   }
   
   if( ! strcmp(argv[1], "warning") )
   {
      lWarning( message );
   }
   else
   if( ! strcmp(argv[1], "critical") )
   {
      lCritical( message );
   }
   else
   if( ! strcmp(argv[1], "fatal") )
   {
      lFatal( message );
   }
   else
   if( ! strcmp(argv[1], "calm") )
   {
      lLog(ELogCategory::Calm | 0, "Calm down" );
   }
   else
   {
      lWarning("Unknown log category: %s", argv[1]);
   }

   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_COMMAND_CLEAR_HPP
