/**---------------------------------------------------------------------------
 *
 * @file       info.cpp
 * @brief      Libfosh command for dumping device information
 *
 *             Biwak info functions are calles.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/biwak/info.hpp>
#include <biwak/biwak.h>

#if defined STM32
#include <HALWrapper/stm32_rcc.h>
#endif


/*--- Implementation -------------------------------------------------------*/


int CCommandInfo::exec(int argc, const char *argv[]) const /* virtual */
{
   printf("\n");

   #if defined STM32
      #if ! ( defined(STM32G4) || defined(STM32L0) || defined(STM32F1) \
                             || defined(STM32L1) || defined(STM32F4) )
         printf("LSEDRIVE: 0x%lX \n", LL_RCC_LSE_GetDriveCapability() );
      #endif
   #endif
         
   biwakPrintBaseInfo();
   biwakPrintClockInfo();
   biwakPrintMemoryInfo();
   biwakPrintFlashInfo();

   printf("\n");

   return( 0 );
}


const CCommand *createInstance_info()
{
   return( new CCommandInfo("info") );
}


/*--- Fin ------------------------------------------------------------------*/
