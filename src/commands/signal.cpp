/**---------------------------------------------------------------------------
 *
 * @file       signal.cpp
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


/*--- Implementation -------------------------------------------------------*/


int CCommandSignal::exec(int argc, const char *argv[]) const /* virtual */
{
   return( m_signal.emitSingle(argc, argv) );
}


/*--- Fin ------------------------------------------------------------------*/
