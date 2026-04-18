/**---------------------------------------------------------------------------
 *
 * @file       allCommands.cpp
 * @brief      Add all available addable commands to an fosh instance
 *
 *             Just for testing
 *
 * @date       20260416
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/fosh.hpp>
#include <fosh/command.hpp>
#include <lepto/lepto.h>               // IS_ENABLED
#include <fosh/commands/biwak/date.hpp>
#if defined STM32
#include <fosh/commands/biwak/reset.hpp>
#include <fosh/commands/biwak/stop.hpp>
#include <fosh/commands/biwak/standby.hpp>
#endif
#include <fosh/commands/log.hpp>
#include <fosh/commands/biwak/alarm.hpp>
#include <fosh/allCommands.hpp>
#include <biwak/rtc.hpp>


/*--- Implementation -------------------------------------------------------*/


void addAllCommands( CFosh* pFosh )
{
   pFosh->addCommand( new CCommandDate( "date", *libcBiwakRtc ) );
   #if defined STM32
      pFosh->addCommand( new CCommandReset( "reset" ) );
      pFosh->addCommand( new CCommandStop( "stop" ) );
      pFosh->addCommand( new CCommandStandby( "standby" ) );
   #endif
   pFosh->addCommand( new CCommandLog( "log" ) );
   pFosh->addCommand( new CCommandAlarm( "alarm", *libcBiwakRtc ) );
}


/*--- Fin ------------------------------------------------------------------*/
