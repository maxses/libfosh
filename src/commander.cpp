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
   int matchCount=0;
   const CCommand *matchCommand=nullptr;
   int commandIndex;
   int matchCommandIndex;

   if(argc)
   {
      if( !memcmp(argv[0], "help", strlen(argv[0])) )
      {
         return( printHelp() );
      }

      // Empty command / line
      if( (!argv[0]) || (!argv[0][0]) )
         return( 0 );
      
      for (const CCommand *command : commandList)
      {
         if ( ( commandIndex=command->matchingIndex( argv[0] ) ) >= 0 )
         {
            lDebug( "Executing '%s' index %d\n", argv[0], commandIndex );
            sta=command->exec( argc, argv );
            executed=true;
         }
         else
         {
            if( ( commandIndex=command->matchingIndex( argv[0], true ) ) >= 0 )
            {
               matchCommand=command;
               matchCommandIndex=commandIndex;
               matchCount++;
            }
         }
      }

      if( !executed )
      {
         if( matchCount == 1 )
         {
            lDebug("Executing '%s' (Shortcut)\n", matchCommand->getName( matchCommandIndex ) );
            
            // Use full command instead of possible abbreviation
            argv[0]=matchCommand->getName( matchCommandIndex );
            
            sta=matchCommand->exec( argc, argv );
            executed=true;
         }
         else
         {
            lDebug( LDS("UKC '%s'", "Unknown command '%s'"), argv[0]);
            fputs( LDS("Unknown com.\n", "Unknown command\n"), stdout);
         }
      }
   }

   #if USE_BIWAK
      // Flush log buffers
      // logEventLoop();
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
