/**---------------------------------------------------------------------------
 *
 * @file       sd.cpp
 * @brief      Libfosh command for SD card
 *
 *             Hardcoded stuff. Avoid including this command for now.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


// #define LEPTO_LOG_DEBUG 1

#include <fosh/commands/biwak/sd.hpp>
#include <lepto/log.h>
#include <lepto/lepto.h>
#include <lepto/print.h>
#include <string.h>
#include <inttypes.h>            // strtoimax


/*--- Implementation -------------------------------------------------------*/


constexpr CCommandSd::SSubCommands CCommandSd::m_subCommands[];


uint8_t CCommandSd::m_data[0x200];


int CCommandSd::exec(int argc, const char *argv[]) const /* virtual */
{
   /*
    * The command itself is included in the argc.
    * config -> argc=1
    */

   lDebug("argc: %d", argc);

   if(argc == 0)
   {
      return( execSubCommand(0, argc, argv) );
   }

   for(int i1=0; i1<arraySize(m_subCommands); i1++)
   {
      if( (! strcmp (argv[1], m_subCommands[i1].string ) )
      || ( ( strlen(argv[1]) == 1 ) && ( argv[1][0] == m_subCommands[i1].string[0] ) ) )
      {
         --argc;
         ++argv;
         if( ( ( argc -1 ) < m_subCommands[i1].minArgs )
          || ( ( argc -1 ) > m_subCommands[i1].maxArgs ) )
         {
            printf("%s: invalid amount of arguments\n", getName());
            
            printf("\nUsage:\n");
            printUsage();
            
            return(-1);
         }
         return ( execSubCommand(m_subCommands[i1].id, argc, argv) );
         break;
      }
   }
   printf("%s: Unknown option '%s'\n", getName(), argv[1]);
   printf("\nUsage:\n");
   printUsage();
   return( -1 );
}


int CCommandSd::optArg(int &dest, int argPos, int argc, const char *argv[]) const
{
   if( argc > argPos )
   {
      char *end;
      dest=strtoimax(argv[ argPos ], &end, 0);
      if( end != argv[ argPos ] + strlen(argv[argPos]) )
      {
         lCritical("Could not read integer");
         return(-1);
      }
   }
   return(0);
}


int CCommandSd::execSubCommand(int id, int argc, const char *argv[]) const /* virtual  */
{
   lDebug( "Calling subcommand with id %d; argc: %d", id, argc );
   lDebug( "   command: %s", argv[0] );
   int block=0;
   int sta=0;

   switch(id)
   {
      case ESubCommands::erase:
      case ESubCommands::read:
      case ESubCommands::write:
      {
         if( optArg( block, 1, argc, argv) < 0 )
         {
               lCritical("Could not read integer");
               return(-1);
         }
         break;
      }
   }

   switch(id)
   {
      case ESubCommands::erase:
         sta=commandErase( block );
         break;
      case ESubCommands::read:
         sta=commandRead( block );
         break;
      case ESubCommands::write:
         sta=commandWrite( block );
         break;
      case ESubCommands::info:
      {
         sta=commandInfo();
         break;
      }
      case ESubCommands::scan:
         sta=commandScan( );
         break;
      case ESubCommands::test:
         sta=commandTest( );
         break;
      default:
      {
         lCritical("Unknown sub-command id: %d", id);
         sta=-1;
         break;
      }
   }

   return(sta);
}


int CCommandSd::commandErase( int block ) const
{
   lDebug("Erase Block: 0x%X", block);
   int sta=m_sd.erase(block);
   if(sta)
   {
      lCritical("sta=%d", sta);
      lCritical("errorCode=0x%X",   m_sd.errorCode() );
   }
   return(sta);
}

int CCommandSd::commandWrite( int block ) const
{
   lDebug("Write Block: 0x%X", block);
   int sta=m_sd.write(m_data, block, 1);
   if(sta)
   {
      lCritical("sta=%d", sta);
      lCritical("errorCode=0x%X",   m_sd.errorCode() );
   }
   return(sta);
}

int CCommandSd::commandRead( int block, bool dump /*=true*/ ) const
{
   lDebug("Read Block: 0x%X", block);
   memset(m_data, 0xff, 0x200);
   int sta=m_sd.read(m_data, block, 1);
   if(sta)
   {
      lCritical("sta=%d", sta);
      lCritical("errorCode=0x%X",   m_sd.errorCode() );
   }
   else
   {
      if(dump)
      {
         hexDump( m_data, 0x200);
      }
   }
   return(sta);
}


int CCommandSd::commandInfo(  ) const
{
   m_sd.info();
   return(0);
}


int CCommandSd::commandScan( ) const
{
   int sta;
   lDebug("Read Blocks");
   for(int i1=0; i1<15677440; i1++)
   {
      sta=commandRead(i1, false);

      if( ( i1 != 0 ) && ( ( i1 % 0x20 ) == 0 ) )
      {
         printf(".");
      }

      if( ( i1 != 0 ) && ( ( i1 % 0x1000 ) == 0 ) )
      {
         printf("\n");
      }

      if(sta)
      {
         lCritical("Error: sta=%d (block %d)", sta, i1);
         break;
      }
   }
   printf("\n");
   return(sta);
}

/**
 * @brief Test is data can be written or write is protected.
 * 
 *        If data could be written the origin data is restored.
 *        
 * @return 0
 */
int CCommandSd::commandTest( ) const
{
   const char* str="Hello World to be tested";
   char buf[ strlen(str) /*24*/];
   int sta;
   if( ( sta=m_sd.read( m_data, 0, 1) ) )
   {
         lWarning("Error reading data: %d", sta);
         return( sta );
   }
   if( !memcmp(m_data, str, strlen( str ) ) )
   {
      lFatal("Not handled");
   }
   memcpy( buf, m_data, strlen(str) );
   memcpy( m_data, str, strlen(str) );
   if( (sta=m_sd.write( m_data, 0, 1) ) )
   {
      lWarning("Error writing data: %d", sta);
      return( sta );
   }
   if( (sta=m_sd.read( m_data, 0, 1) ) )
   {
      lWarning("Error reading data: %d", sta);
      return( sta );
   }
   if( ! memcmp( m_data, buf, strlen(str) ) )
   {
      printf("Error: Data is still origin. Write did not do anything.\n");
      return( sta );
   }
   if( ! memcmp( m_data, str, strlen(str) ) )
   {
      printf("Ok, writing worked as expected.\n");
   }
   else
   {
      printf("Error: Data is neithor origin or expected change.\n");
   }
   
   memcpy( m_data, buf, strlen(str) );
   sta=m_sd.write( m_data, 0, 1);
      
   return( sta );
}


void CCommandSd::printUsage() const
{
   int cnt;
   
   #if IS_ENABLED( CONFIG_FOSH_CEATE_HELP )
   CCommand::printHelp();
   #endif

   for(int i1=0; i1<arraySize(m_subCommands); i1++)
   {
      cnt=printf("      %s %s %s   ", getName()
             , m_subCommands[i1].string
             , m_subCommands[i1].argumentsHelpString );
      for(int i2=0; i2<25-cnt; i2++ )
      {
         printf(" ");
      }
      cnt=printf("%s\n", m_subCommands[i1].helpString);
   }
}


/*--- Fin ------------------------------------------------------------------*/
