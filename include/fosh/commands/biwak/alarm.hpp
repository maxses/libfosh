#ifndef FOSH_COMMAND_ALARM_HPP
#define FOSH_COMMAND_ALARM_HPP
/**---------------------------------------------------------------------------
 *
 * @file       alarm.hpp
 * @brief      Libfosh command for reading/seting the RTC alarm
 *
 *  \date      20251203
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes --------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <biwak/rtc.hpp>


/*--- Declaration -----------------------------------------------------------*/


class CCommandAlarm: public CCommand
{
   private:
      CRtc &m_rtc;

   public:
      CCommandAlarm(const char *_name, CRtc &rtc)
         :CCommand( _name, "alarm: get/set the rtc alarm" )
         ,m_rtc(rtc)
      {}
      virtual int exec(int argc, const char *argv[]) const;
      void usage() const;
      int setAlarm(const char* dataStr) const;
      int getAlarm() const;
};


/*--- Fin -------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_ALARM_HPP
