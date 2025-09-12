#ifndef FOSH_COMMAND_TIME_HPP
#define FOSH_COMMAND_TIME_HPP
/**---------------------------------------------------------------------------
 *
 * @file       time.hpp
 * @brief      Libfosh command for getting/setting time
 *
 *             Currently the MCUs RTC is used directly. This could be changed
 *             to use syscalls in the future.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <biwak/rtc.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandTime: public CCommand
{
   private:
      CRtc &m_rtc;

   public:
      CCommandTime(const char *_name, CRtc &rtc)
         :CCommand( _name, "time: get/set time and date (libc)" )
         ,m_rtc(rtc)
      {}
      virtual int exec(int argc, const char *argv[]) const;

      int setTime(const char* dataStr) const;  // format like MMDDYY
      int getTime() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_TIME_HPP
