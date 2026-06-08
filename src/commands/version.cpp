/**---------------------------------------------------------------------------
 *
 * @file       version.cpp
 * @brief      Libfosh command for showing git version information
 *
 * @date       20260608
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/version.hpp>
#include <stdio.h>                    // printf


/*--- Implementation -------------------------------------------------------*/


int CCommandVersion::exec(int argc, const char *argv[]) const /* virtual override */
{
   (void)argc;
   (void)argv;
   
   printf( "Root project: \"" GIT_PROJECT  "\"\n");
   printf( "Version:      " GIT_SEMI "\n");

   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
