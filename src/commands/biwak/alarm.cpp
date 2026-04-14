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
   #if ! IS_ENABLED( CONFIG_BIWAK_RTC_LOCALTIME )
   int hour, minute, second;
   
   m_rtc.getAlarmTime(hour, minute, second);
   #endif
   
   #if IS_ENABLED( CONFIG_BIWAK_RTC_LOCALTIME )
      struct tm ts;
      m_rtc.getLocalAlarmTime( ts );
      printf("%d.%d.%d %02d:%02d:%02d"
             , ts.tm_mday, ts.tm_mon+1, ts.tm_year+1900
             , ts.tm_hour, ts.tm_min, ts.tm_sec );

      #if 0
         printf(" (%02d:%02d:%02d UTC)"
             , hour, minute, second);
      #endif
      
      printf("\n");

   #else
      m_rtc.getDate(year, month, day);
      printf("%d.%d.%d %02d:%02d:%02d UTC\n", day, month, year,
             hour, minute, second);
   #endif
      
   if( m_rtc.isAlarmTriggered() )
   {
      printf ( "Warning: Alarm already triggered\n" );
   }

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
      #if defined STM32
      sta=HAL_RTC_DeactivateAlarm( m_rtc.getHandler(), RTC_ALARM_A);
      #else
      sta=22;
      #endif
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
      
      #if IS_ENABLED( CONFIG_BIWAK_RTC_LOCALTIME )
         struct tm ts{
             .tm_sec=sec,
             .tm_min=min,
             .tm_hour=hour,
             .tm_mday=0,
             .tm_mon=0,
             .tm_year=0,
             .tm_wday=0,
             .tm_yday=0,
             .tm_isdst=0
         };
         m_rtc.setLocalAlarmTime( ts );
      #else
         m_rtc.setAlarm(hour, min, sec);
      #endif
   }

  return(sta);
}


/*--- Fin -------------------------------------------------------------------*/
