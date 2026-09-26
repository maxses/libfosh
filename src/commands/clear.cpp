/**---------------------------------------------------------------------------
 *
 * @file       clear.cpp
 * @brief      Libfosh command for clearing the screen
 *
 *             Ansi commands are used so this command works also on UART
 *             terminals.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/clear.hpp>


/*--- Implementation -------------------------------------------------------*/


int CCommandClear::exec(int argc, const char *argv[]) const /* virtual */
{
   (void)argc;
   (void)argv;

   printf( ANSI_RESET ANSI_CLEARSCREEN ANSI_HOME );
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
