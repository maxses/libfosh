#ifndef FOSH_COMMAND_MEMORY_HPP
#define FOSH_COMMAND_MEMORY_HPP
/**---------------------------------------------------------------------------
 *
 * @file       memory.hpp
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


/*--- Declarations ---------------------------------------------------------*/


class CCommandMemory: public CCommand
{
   public:
      CCommandMemory(const char *_name)
         :CCommand( _name, "Show info about memory" )
      {}
      virtual int exec(int argc, const char *argv[]) const override;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_COMMAND_MEMORY_HPP
