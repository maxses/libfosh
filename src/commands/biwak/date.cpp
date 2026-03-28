/**---------------------------------------------------------------------------
 *
 * @file       date.cpp
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
#include <fosh/commands/biwak/date.hpp>
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


int CCommandDate::exec(int argc, const char *argv[]) const /* virtual */
{

   if(argc>1)
      setDate(argv[1]);

   getDate();

   return( 0 );
}


int CCommandDate::getDate() const
{
   int year, month, day;
   int hour, minute, second;
   m_rtc.getDate(year, month, day);
   m_rtc.getTime(hour, minute, second);
   printf("%d.%d.%d %02d:%02d:%02d UTC\n", day, month, year,
          hour, minute, second);

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
      //int year = strtol(buf, &end, 10);
      printf("Buf: %s; %d\n", buf, year);
   
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
   
      //time_t mytime = time(0);
      //struct tm* tm_ptr = localtime(&mytime);
   
      /*
      if (tm_ptr)
      {
         tm_ptr->tm_mon  = month - 1;
         tm_ptr->tm_mday = day;
         tm_ptr->tm_year = year - 1900;
         tm_ptr->tm_hour = hour;
         tm_ptr->tm_min  = min;
         tm_ptr->tm_sec  = sec;
         tm_ptr->tm_wday = 0;
         tm_ptr->tm_yday = 0;
         tm_ptr->tm_isdst = 0;
   
         //const struct timeval tv = {mktime(tm_ptr), 0};
         struct timeval tv = {0, 0};
         tv.tv_sec=mktime(tm_ptr);
         printf("Secs: %d\n",(int)tv.tv_sec);
         sta=settimeofday(&tv, 0);
      }
      */
      printf("Year: %d\n", year);
      m_rtc.setDate(year, month, day);
      sta=m_rtc.setTime(hour, min, sec);
   }

   return(sta);
}


/*--- Fin -------------------------------------------------------------------*/
