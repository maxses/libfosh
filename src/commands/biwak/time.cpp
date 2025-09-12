/**---------------------------------------------------------------------------
 *
 * @file       time.cpp
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
#include <fosh/commands/biwak/time.hpp>
#include <stdio.h>
#include <time.h>       // time.h, localtime, strftime
#include <string.h>     // strncpy
#include <sys/time.h>   // settimeofday
#include <stdlib.h>      // atoi

#ifdef STM32
   //#include <arena/platform.h>
   #include <biwak/rtc.hpp>
#endif


/*--- Implementation -------------------------------------------------------*/


int CCommandTime::exec(int argc, const char *argv[]) const /* virtual */
{

   if(argc>1)
      setTime(argv[1]);

   getTime();

   return( 0 );
}

int CCommandTime::getTime() const
{
   time_t t = time( nullptr );
   struct tm *tm = localtime(&t);
   //char s[64];
   //strftime(s, sizeof(s), "%c", tm);
   //printf("%s\n", s);0x63FA0B70
   if(!tm)
   {
      printf("Could not create time\n");
      return(-1);
   }
   else
   {    
      printf("ptr: %p\n", tm);
   }
   printf("%d.%d.%d %02d:%02d:%02d (DST:%d) \n"
          , (int)tm->tm_mday, (int)tm->tm_mon+1, (int)tm->tm_year + 1900
          , (int)tm->tm_hour, (int)tm->tm_min, (int)tm->tm_sec, (tm->tm_isdst ? 1 : 0) );
   printf("Epoch: 0x%llX\n", t );

   timeval tv;
   gettimeofday(&tv, 0);
   printf("Epoch2: 0x%llX\n", tv.tv_sec);

   return(0);
}


 
int CCommandTime::setTime(const char* dataStr) const // format like YYYYMMDD-hhmmss
{
   int sta=-1;

   char buf[5] = {0,0,0,0,0};

   if(strlen(dataStr)!=15)
   {
      printf( "Error, size does not match; '%s', %u\n", dataStr, sizeof(dataStr) );
      printf( "Usage: Time <YYYYMMDD-hhmmss>\n" );
      printf( "e.g.   Time 20170326-180800\n" );
      printf( "       Time +\"%%Y%%m%%d-%%H%%M%%S\"\n" );
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
   m_rtc.setTime(year, month, day);
   m_rtc.setTime(hour, min, sec);

  return(sta);
} 


/*--- Fin ------------------------------------------------------------------*/
