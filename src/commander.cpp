/**---------------------------------------------------------------------------
 *
 * @file       commander.cpp
 * @brief      Libfosh container for all commands
 *
 *             Holds a list of all available commands. 
 *             The commander is asked to run a command by given strings.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commander.hpp>
#include <fosh/command.hpp>
#include <stdio.h>         // printf
#include <lepto/log.h>
#if USE_BIWAK
   #include <biwak/biwak.h>
#endif


/*--- Implementation -------------------------------------------------------*/


using namespace std;

CCommander::CCommander()
   :commandList( CONFIG_FOSH_COMMANDS /* List size */ )
{

};


int CCommander::execCommand( int argc, const char *argv[] )
{
   bool executed=false;
   int sta=-1;

   if(argc)
   {
      if(!strcmp(argv[0], "help"))
         return( printHelp() );

      // Empty command / line
      if( (!argv[0]) || (!argv[0][0]) )
         return( 0 );

      for (const CCommand *command : commandList)
      {
         if ( ! strcmp( argv[0], command->getName() ) )
         {
            sta=command->exec( argc, argv );
            executed=true;
         }
      }

      if( !executed )
      {
         fputs( LDS("CNFC", "Could not find command '"), stdout);
         fputs(argv[0], stdout);
         fputs("'\n", stdout);
      }
   }

   #if USE_BIWAK
      // Flush log buffers
      biwakEventLoop();
   #endif

   return(sta);
}


int CCommander::printHelp()
{
   for (const CCommand *command : commandList)
   {
      command->printHelp(  );
   }

   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
