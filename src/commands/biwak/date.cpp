/**---------------------------------------------------------------------------
 *
 * @file       date.cpp
 * @brief      Libfosh command for reading/writing date
 *
 *             The MCUs RTC is used directly. For libc functions use 'time'
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *---------------------------------------------------------------------------*/


/*--- Includes --------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <fosh/commands/biwak/date.hpp>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>        // atoi

#ifdef STM32
   //#include <arena/platform.h>
   #include <biwak/rtc.hpp>
#endif


/*--- Implementation --------------------------------------------------------*/


int CCommandDate::exec(int argc, const char *argv[]) const /* virtual */
{

   if(argc>1)
      setDate(argv[1]);

   getDate();

   return( 0 );
}


int CCommandDate::getDate() const
{
   #if ! IS_ENABLED( CONFIG_BIWAK_RTC_LOCALTIME )
   int year, month, day;
   int hour, minute, second;
   m_rtc.getDate(year, month, day);
   m_rtc.getTime(hour, minute, second);
   #endif

   #if IS_ENABLED( CONFIG_BIWAK_RTC_LOCALTIME )
      struct tm ts;
      m_rtc.getLocalTime( ts );
      printf("%d.%d.%d %02d:%02d:%02d"
         , ts.tm_mday, ts.tm_mon+1, ts.tm_year+1900
             , ts.tm_hour, ts.tm_min, ts.tm_sec );
      #if 0
         printf("(%02d:%02d:%02d)"
            , hour, minute, second);
      #endif
      printf("\n");

   #else
      printf("%d.%d.%d %02d:%02d:%02d UTC\n", day, month, year,
          hour, minute, second);
   #endif
   
   printf ( m_rtc.isValid() ? "(Valid)\n" : "(Not valid)\n" );

   return(0);
}


void CCommandDate::usage() const
{
   printf( "Usage: date <YYYYMMDD-hhmmss>\n" );
   printf( "e.g.   date 20170326-180800\n" );
   printf( "       date +\"%%Y%%m%%d-%%H%%M%%S\"\n" );
}


int CCommandDate::setDate(const char* dataStr) const // format like YYYYMMDD-hhmmss
{
   int sta=-1;

   char buf[5] = {0,0,0,0,0};
   
   if( ( ! strcmp(dataStr, "-h") ) || ( ! strcmp(dataStr, "--help") ) )
   {
      usage();
      return(0);
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
         printf("Seting relative time %d\n", seconds);
         sta=m_rtc.setRelativeTime( seconds );
      }
   }
   else
   {
      if(strlen(dataStr)!=15)
      {
         printf( "Error, size does not match; '%s', %d\n", dataStr, (int)sizeof(dataStr) );
         usage();
         return(sta);
      }
   
      strncpy(buf, dataStr + 0, 4);
      int year = atoi(buf);
      // int year = strtol(buf, &end, 10);
      // printf("Buf: %s; %d\n", buf, year);
   
      buf[2]=0;
      strncpy(buf, dataStr + 4, 2);
      int month = atoi(buf);
   
      buf[2]=0;
      strncpy(buf, dataStr + 6, 2);
      int day = atoi(buf);
   
      buf[2]=0;
      strncpy(buf, dataStr + 1 + 8, 2);
      int hour = atoi(buf);
   
      buf[2]=0;
      strncpy(buf, dataStr + 1 + 10, 2);
      int min = atoi(buf);
   
      buf[2]=0;
      strncpy(buf, dataStr + 1 + 12, 2);
      unsigned short sec = atoi(buf);
   
      // time_t mytime = time(0);
      // struct tm* tm_ptr = localtime(&mytime);
      printf("Year: %d\n", year);
      #if IS_ENABLED( CONFIG_BIWAK_RTC_LOCALTIME )
         struct tm ts{
            .tm_sec=sec,
            .tm_min=min,
            .tm_hour=hour,
            .tm_mday=day,
            .tm_mon=month-1,
            .tm_year=year-1900,
            .tm_wday=0,
            .tm_yday=0,
            .tm_isdst=0,
          
            #ifdef __TM_GMTOFF
            .tm_gmtoff=0,
            #endif
         
            #ifdef __TM_ZONE
            .tm_zone=0,
            #endif
         };
         m_rtc.setLocalTime( ts );
      #else
         m_rtc.setDate(year, month, day);
         sta=m_rtc.setTime(hour, min, sec);
      #endif
   }

   return(sta);
}


/*--- Fin -------------------------------------------------------------------*/
