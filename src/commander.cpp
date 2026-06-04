/**---------------------------------------------------------------------------
 *
 * @file       commander.cpp
 * @brief      Libfosh container for all commands
 *
 *             Holds a list of all available commands. 
 *             The commander is asked to run a command by given strings.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
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
   int sta=22;
   // Making this variables char instead of int saves 140 bytes on miniminutnik
   int matchCommandIndex=-1;

   if(argc)
   {
      if( !memcmp(argv[0], "help", strlen(argv[0])) )
      {
         return( printHelp() );
      }
      const CCommand *command=findCommand(argv[0], matchCommandIndex);
      if( command )
      {
         lDebug("Executing '%s' (Shortcut)\n", matchCommand->getName( matchCommandIndex ) );

         // Use full command instead of possible abbreviation
         argv[0]=command->getName( matchCommandIndex );
         sta=command->exec( argc, argv );
      }
      else
      {
         lDebug( LDS("UK CMD '%s'", "Unknown command '%s'"), argv[0]);
         fputs( LDS("UK CMD\n", "Unknown command\n"), stdout);
      }
   }

   #if USE_BIWAK
      // Flush log buffers which may be created by the executed command.
      // Otherwise the fosh prompt my get disturbed.
      logEventLoop();
   #endif

   return(sta);
}


const CCommand *CCommander::findCommand( const char* cmd, int &matchCommandIndex )
{
   int commandIndex;
   #if IS_ENABLED( CONFIG_FOSH_AUTO_COMPLETION )
      const CCommand *matchCommand=nullptr;
      int matchCount=0;
   #endif

   // Empty command / line
   if( (!cmd) || (!cmd[0]) )
   {
      return( nullptr );
   }

   for (const CCommand *command : commandList)
   {
      if ( ( commandIndex=command->matchingIndex( cmd ) ) >= 0 )
      {
         lDebug( "Executing '%s' index %d\n", cmd, commandIndex );
         matchCommandIndex=commandIndex;
         return( command );
      }

      #if IS_ENABLED( CONFIG_FOSH_AUTO_COMPLETION )

      else
      {
         if( ( commandIndex=command->matchingIndex( cmd, true ) ) >= 0 )
         {
            matchCommand=command;
            matchCommandIndex=commandIndex;
            matchCount++;
         }
      }

      #endif // ? CONFIG_FOSH_AUTO_COMPLETION
   }

   #if IS_ENABLED( CONFIG_FOSH_AUTO_COMPLETION )

   if( matchCount == 1 )
   {
      return(matchCommand);
   }

   #endif // ? CONFIG_FOSH_AUTO_COMPLETION

   return( nullptr );
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
