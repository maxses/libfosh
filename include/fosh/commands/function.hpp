#ifndef FOSH_COMMAND_FUNCTION_HPP
#define FOSH_COMMAND_FUNCTION_HPP
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
 * @date       20260524
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandFunction: public CCommand
{
   private:
      int (*m_pFunction)( int, const char ** );

   public:

      /** \brief  Constructor setting the function pointer
       * 
       * example: 
       *     new CCommandFunction( "eraseflash", "Erase media flash", &eraseFlash )
       */
      CCommandFunction(const char *_name, const char *desc, int (*functionPtr)( int, const char ** ))
          :CCommand( _name, desc )
      {
         m_pFunction = functionPtr;
      }
      
      virtual int exec(int argc, const char *argv[]) const override final;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_FUNCTION_HPP
