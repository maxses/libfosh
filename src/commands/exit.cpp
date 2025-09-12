/**---------------------------------------------------------------------------
 *
 * @file       exit.cpp
 * @brief      Libfosh command for exiting the shell
 *
 *             On MCUs the behaviour depends on the systems implementation. 
 *             This command just calls exit().
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/exit.hpp>
#include <stdlib.h>                    // atioi(), exit()


/*--- Implementation -------------------------------------------------------*/


int CCommandExit::exec(int argc, const char *argv[]) const /* virtual */
{
   int retCode=0;
   
   if( argc>1 )
   {
      retCode = atoi( argv[1] );
   }
   
   exit( retCode );
   
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
