/**---------------------------------------------------------------------------
 *
 * @file       exit.cpp
 * @brief      Libfosh command for showing memory info
 *
 *             E.g. Analyze heap and stack
 *
 * @date       20260507
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/memory.hpp>
#include <stdio.h>                    // printf
#include <unistd.h>                   // sbrk()
#if USE_BIWAK
#include <biwak/linker_script.h>
#endif

/*--- Implementation -------------------------------------------------------*/


int CCommandMemory::exec(int argc, const char *argv[]) const /* virtual override */
{
   register long sp asm("sp");

   #if STM32
      printf("Heap start: %p\n", &__heap_start );
      printf("Heap end  : %p\n", &__heap_end );
   #endif
      printf("Stack br    %p\n", &stackBarrier );
   #if STM32
      printf("End RAM   : %p\n", &_eram);
   #endif
      printf("sbrk : %p\n", sbrk(0));
      printf("sp   : %p\n", (void*)sp);

   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
