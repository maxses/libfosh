/**---------------------------------------------------------------------------
 *
 * @file       allCommands.cpp
 * @brief      Add all available addable commands to an fosh instance
 *
 *             Just for testing
 *
 * @date       20260416
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/fosh.hpp>
#include <fosh/command.hpp>
#include <lepto/lepto.h>               // IS_ENABLED
#if defined STM32
#include <fosh/commands/biwak/date.hpp>
#include <fosh/commands/biwak/reset.hpp>
#include <fosh/commands/biwak/stop.hpp>
#include <fosh/commands/biwak/standby.hpp>
#include <fosh/commands/biwak/alarm.hpp>
#include <biwak/rtc.hpp>
#endif
#include <fosh/commands/log.hpp>
#include <fosh/allCommands.hpp>


/*--- Implementation -------------------------------------------------------*/


void addAllCommands( CFosh* pFosh )
{
   #if defined STM32
      pFosh->addCommand( new CCommandDate( "date", *libcBiwakRtc ) );
      pFosh->addCommand( new CCommandReset( "reset" ) );
      pFosh->addCommand( new CCommandStop( "stop" ) );
      pFosh->addCommand( new CCommandStandby( "standby" ) );
      pFosh->addCommand( new CCommandAlarm( "alarm", *libcBiwakRtc ) );
   #endif
   pFosh->addCommand( new CCommandLog( "log" ) );
}


/*--- Fin ------------------------------------------------------------------*/
