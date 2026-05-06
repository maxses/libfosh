#ifndef FOSH_COMMAND_EXIT_HPP
#define FOSH_COMMAND_EXIT_HPP
/**---------------------------------------------------------------------------
 *
 * @file       exit.hpp
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


/*--- Declarations ---------------------------------------------------------*/


class CCommandExit: public CCommand
{
   public:
      CCommandExit(const char *_name)
         :CCommand( _name, "   date: get/set time and date\n" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_COMMAND_EXIT_HPP
