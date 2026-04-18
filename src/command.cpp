/**---------------------------------------------------------------------------
 *
 * @file       command.cpp
 * @brief      Libfosh abstract base command class
 *
 *             Quite trivial.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdio.h>
#include <string.h>                    // strcmp
#include <lepto/lepto.h>               // IS_ENABLED


/*--- Implementation -------------------------------------------------------*/


CCommand::CCommand(const char *name, const char *helpString)
   :m_pName(name)
   ,m_pHelpString(helpString)
   #if IS_ENABLED( CONFIG_FOSH_COMMAND_ALIASES )
      ,m_pAliases(nullptr)
   #endif
{

}


/* static */
void CCommand::printHelp(const char*name, const char*desc)
{
   #if IS_ENABLED( CONFIG_LEPTO_LOG_DOWNSIZE )
      fputs( "   ", stdout);
      fputs( name, stdout);
      fputs( ": ", stdout);
      fputs( desc, stdout);
      fputs( "\n", stdout);
   #else
      int cnt;
      cnt=printf("   %s", name);
      for(int i1=0; i1<25-cnt; i1++ )
      {
         printf(" ");
      }
      printf("%s\n", desc);
   #endif
      
   return;
}

void CCommand::printHelp() const /*virtual*/
{
   printHelp( m_pName, m_pHelpString);

   #if IS_ENABLED( CONFIG_FOSH_COMMAND_ALIASES )
   
   if( m_pAliases )
   {
      const SAlias *aliases=m_pAliases;
      while( aliases->name )
      {
         printHelp( aliases->name, aliases->desc);
         aliases++;
      }
   }

   #endif
   
   return;
}


/* static */
bool CCommand::matches(const char *str, const char *me, bool shortcut /*=false*/ )
{
   if( ! shortcut )
   {
      return( !strcmp( str, me ) );
   }
   
   return( ! memcmp( str, me, strlen( str ) ) );
}


int CCommand::matches(const char *str, bool shortcut /*=false*/ ) const
{
   int index=0;
   
   if( matches( str, getName( 0 ), shortcut ) )
   {
      return( index );
   }

   #if IS_ENABLED( CONFIG_FOSH_COMMAND_ALIASES )
   
   if( m_pAliases )
   {
      const SAlias *aliases=m_pAliases;
      while( aliases->name )
      {
         index++;
         if( matches( str, aliases->name, shortcut ) )
         {
            return( index );
         }
         aliases++;
      }
   }

   #endif // ? CONFIG_FOSH_COMMAND_ALIASES
   
   return -1;
}


/*--- Fin ------------------------------------------------------------------*/
