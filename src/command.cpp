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
#include <lepto/lepto.h>               // IS_ENABLED


/*--- Implementation -------------------------------------------------------*/


CCommand::CCommand(const char *name, const char *helpString)
   :m_pName(name)
   ,m_pHelpString(helpString)
{

}


void CCommand::printHelp() const /*virtual*/
{
   #if IS_ENABLED( CONFIG_LEPTO_LOG_DOWNSIZE )
      fputs("   ", stdout);
      fputs(m_pName, stdout);
      fputs(": ", stdout);
      fputs(m_pHelpString, stdout);
      fputs("\n", stdout);
   #else
      int cnt;
      cnt=printf("   %s", m_pName);
      for(int i1=0; i1<25-cnt; i1++ )
      {
         printf(" ");
      }
      printf("%s\n", m_pHelpString);
   #endif
      
   return;
}


/*--- Fin ------------------------------------------------------------------*/
