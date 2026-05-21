#ifndef FOSH_COMMAND_LIST_HPP
#define FOSH_COMMAND_LIST_HPP
/**---------------------------------------------------------------------------
 *
 * @file       signal.hpp
 * @brief      Generic Libfosh command to provide further command via signals
 *
 *             Use lepto signals to declare commands. This avoids to implement 
 *             a new class for simple commands over and over.
 *             Example:
 *                fosh.addCommand( new CCommandSignal("hello", "Hello world", hello ) );
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/signal.hpp>
#include <fosh/fosh.hpp>


/*--- Declaration ----------------------------------------------------------*/

template <class slotClass >
struct SCommandDesc
{
   const char *name;
   const char *desc;
   slotClass *slotObject;
   int (slotClass::*_methodPtr)( int, const char *[] );
};

template <class slotClass >
int addCommandList(
      CFosh* fosh,
      SCommandDesc<slotClass> commands[]
)
{
   int i1=0;
   while( commands[i1].name )
   {
      fosh->addCommand( new CCommandSignal(
         commands[i1].name,
         commands[i1].desc,
         commands[i1].slotObject,
         commands[i1]._methodPtr
      ) );
      i1++;
   }
   return(i1);
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_LIST_HPP
