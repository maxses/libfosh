#ifndef FOSH_COMMAND_CANDUMP_HPP
#define FOSH_COMMAND_CANDUMP_HPP
/**---------------------------------------------------------------------------
 *
 * @file       candump.hpp
 * @brief      Libfosh command for dumping CAN traffic
 *
 *  \date      20260607
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>


/*--- Declaration ----------------------------------------------------------*/


class CCan;

class CCommandCanDump: public CCommand
{
      CCan &m_can;
      
   public:
      CCommandCanDump(const char *name, CCan &eeprom);
      virtual int exec(int argc, const char *argv[]) const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_CANDUMP_HPP
