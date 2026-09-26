#ifndef FOSH_ALL_COMMAND_HPP
#define FOSH_ALL_COMMAND_HPP
/**---------------------------------------------------------------------------
 *
 * @file       all.hpp
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
#include <fosh/fosh.hpp>
#include <fosh/command.hpp>

#if defined STM32
   #include <fosh/commands/biwak/date.hpp>
   #include <fosh/commands/biwak/time.hpp>
   #include <fosh/commands/biwak/reset.hpp>
   #include <fosh/commands/biwak/stop.hpp>
   #include <fosh/commands/biwak/standby.hpp>
   #include <fosh/commands/biwak/alarm.hpp>
   #include <fosh/commands/biwak/spi_flash.hpp>
   #include <fosh/commands/biwak/i2c.hpp>
   #include <fosh/commands/biwak/sd.hpp>
   #include <fosh/commands/biwak/eeprom.hpp>
   #include <biwak/rtc.hpp>
#else
   #include <fosh/commands/exit.hpp>
   #include <fosh/commands/memory.hpp>
#endif

#include <fosh/commands/version.hpp>
#include <fosh/commands/clear.hpp>
#include <fosh/commands/log.hpp>
#include <fosh/commands/signal.hpp>


/*--- Declaration ----------------------------------------------------------*/


void addAllCommands( CFosh* fosh );


/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_ALL_COMMAND_HPP
