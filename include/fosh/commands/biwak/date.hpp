#ifndef FOSH_COMMAND_DATE_HPP
#define FOSH_COMMAND_DATE_HPP
/**---------------------------------------------------------------------------
 *
 * @file       date.hpp
 * @brief      Libfosh command for reading/writing date
 *
 *             Currently the MCUs RTC is used directly. This could be changed 
 *             to use syscalls in the future.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes --------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <biwak/rtc.hpp>


/*--- Declaration -----------------------------------------------------------*/


class CCommandDate: public CCommand
{
   private:
      CRtc &m_rtc;

   public:
      CCommandDate(const char *_name, CRtc &rtc)
         :CCommand( _name, "date: get/set time and date (rtc)" )
         ,m_rtc(rtc)
      {}
      virtual int exec(int argc, const char *argv[]) const;
      void usage() const;
      int setDate(const char* dataStr) const;  // format like MMDDYY
      int getDate() const;
};


/*--- Fin -------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_DATE_HPP
