#ifndef FOSH_COMMAND_TIME_HPP
#define FOSH_COMMAND_TIME_HPP
/**---------------------------------------------------------------------------
 *
 * @file       time.hpp
 * @brief      Libfosh command for getting/setting time
 *
 *             Libc functions are used.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandTime: public CCommand
{
   private:

   public:
      CCommandTime(const char *_name /*, CRtc &rtc*/ )
         :CCommand( _name, "time: get/set time and date (libc)" )
      {}
      virtual int exec(int argc, const char *argv[]) const;

      int setTime(const char* dataStr) const;  // format like MMDDYY
      int getTime() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_TIME_HPP
