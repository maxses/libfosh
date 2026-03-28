/**---------------------------------------------------------------------------
 *
 * @file       alarm.cpp
 * @brief      Libfosh command for reading/seting the RTC alarm
 *
 *  \date      20251203
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes --------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/biwak/alarm.hpp>
#include <stdio.h>
#include <time.h>       // time.h, localtime, strftime
#include <string.h>     // strncpy
#include <sys/time.h>   // settimeofday
#include <stdlib.h>      // atoi

#ifdef STM32
   //#include <arena/platform.h>
   #include <biwak/rtc.hpp>
#endif


/*--- Implementation --------------------------------------------------------*/


int CCommandAlarm::exec(int argc, const char *argv[]) const /* virtual */
{

   if(argc>1)
      setAlarm(argv[1]);

   getAlarm();

   return( 0 );
}


int CCommandAlarm::getAlarm() const
{
   int year, month, day;
   int hour, minute, second;
   m_rtc.getDate(year, month, day);
   m_rtc.getAlarmTime(hour, minute, second);
   printf("%d.%d.%d %02d:%02d:%02d UTC\n", day, month, year,
          hour, minute, second);
   
   if( m_rtc.isAlarmTriggered() )
   {
      printf ( "Warning: Alarm already triggered\n" );
   }
   
   //printf("Alarm is %sarmed\n", m_rtc.isAlarmActive() ? "" : "not " );
   //printf ( "ISR: 0x%X\n", m_rtc.getIsr() );

   return(0);
}


void CCommandAlarm::usage() const
{
   printf( "Usage: alarm <hhmmss>\n" );
   printf( "       alarm +|-<ss>\n" );
   printf( "e.g.   alarm 180800\n" );
   printf( "       alarm +10\n" );
}


int CCommandAlarm::setAlarm(const char* dataStr) const // format like YYYYMMDD-hhmmss
{
   int sta=-1;
   char buf[5] = {0,0,0,0,0};
   int hour;
   int min;
   int sec;
   
   if( ( ! strcmp(dataStr, "-h") ) || ( ! strcmp(dataStr, "--help") ) )
   {
      usage();
      return(0);
   }
   
   if( !strcmp(dataStr, "off") )
   {
      printf("Setting alarm off\n");
      sta=HAL_RTC_DeactivateAlarm( m_rtc.getHandler(), RTC_ALARM_A);
      return(sta);
   }
   
   if( ( dataStr[0] == '+' ) || ( dataStr[0] == '-' ) )
   {
      int seconds = atoi( dataStr );
      
      if( ! seconds )
      {
         usage();
      }
      else
      {
         printf("Seting relative alarm %d\n", seconds);
         m_rtc.setRelativeAlarm( seconds );
      }
   }
   else
   {
      if( strlen(dataStr) != 6 )
      {
         printf( "Error, size does not match; '%s', %d\n", dataStr, (int)sizeof(dataStr) );
         usage();
         return(sta);
      }
      
      buf[2]=0;
      strncpy(buf, dataStr, 2);
      hour = atoi(buf);
   
      buf[2]=0;
      strncpy(buf, dataStr + 2, 2);
      min = atoi(buf);
   
      buf[2]=0;
      strncpy(buf, dataStr + 4, 2);
      sec = atoi(buf);
   
      m_rtc.setAlarm(hour, min, sec);
   }

  return(sta);
}


/*--- Fin -------------------------------------------------------------------*/
