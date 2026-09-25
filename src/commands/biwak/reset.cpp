/**---------------------------------------------------------------------------
 *
 * @file       exit.cpp
 * @brief      Libfosh command for exiting the shell
 *
 *             On MCUs the behaviour depends on the systems implementation. 
 *             This command just calls exit().
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/biwak/reset.hpp>

#if defined STM32
   #include <HALWrapper/stm32_hal.h>
#else
   #include <stdio.h>
#endif


/*--- Implementation -------------------------------------------------------*/


int CCommandReset::exec(int argc, const char *argv[]) const /* virtual */
{
   lUNUSED( argc );
   lUNUSED( argv );

   #if defined STM32
      NVIC_SystemReset();
   #else
      printf("Resetting device\n");
   #endif

   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
