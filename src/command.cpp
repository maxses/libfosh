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


/*--- Implementation -------------------------------------------------------*/


CCommand::CCommand(const char *name, const char *helpString)
   :m_pName(name)
   ,m_pHelpString(helpString)
{

}


void CCommand::printHelp() const
{
   fputs("   ", stdout);
   fputs(m_pName, stdout);
   fputs(": ", stdout);
   fputs(m_pHelpString, stdout);
   fputs("\n", stdout);

   return;
}


/*--- Fin ------------------------------------------------------------------*/
