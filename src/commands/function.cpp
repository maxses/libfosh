/**---------------------------------------------------------------------------
 *
 * @file       function.hpp
 * @brief      Generic Libfosh command using an function pointer
 *
 *             This avoids to implement 
 *             a new class for simple commands over and over.
 *             Example:
 *                fosh.addCommand( new CCommandFunction("hello", "Hello world", &hello ) );
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/function.hpp>


/*--- Implementation -------------------------------------------------------*/


#if ! IS_ENABLED( CONFIG_FOSH_PSEUDO_VIRTUAL )

int CCommandFunction::exec(int argc, const char *argv[]) const /* virtual */
{
   return( m_pFunction(argc, argv) );
}

#endif // ! ? CONFIG_FOSH_PSEUDO_VIRTUAL


/*--- Fin ------------------------------------------------------------------*/
