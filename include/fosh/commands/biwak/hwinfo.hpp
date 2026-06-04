#ifndef FOSH_COMMAND_HWINFO_HPP
#define FOSH_COMMAND_HWINFO_HPP
/**---------------------------------------------------------------------------
 *
 * @file       hwinfo.hpp
 * @brief      Libfosh command for dumping hwinfo
 *
 *  \date      20250529
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>
#include <hwinfo/hwinfo.h>

#if defined(STM32)
   #include <biwak/flash_intern.hpp>
#else
   #include <biwak/flash_file.hpp>
#endif


#if IS_ENABLED( CONFIG_BIWAK_I2C_RETAIN_ONLY )
#define CFlashX CFlashI2c
#elif IS_ENABLED( CONFIG_BIWAK_RETAIN_INTERN_ONLY )
#define CFlashX CEepromIntern
#else
#define CFlashX CFlash
#endif


/*--- Declaration ----------------------------------------------------------*/


struct SEepromHwInfoCustom: public SEepromBoardInfo
{
   char reserved[ 0x40 - sizeof(SEepromBoardInfo) - RETAIN_HEADER_SIZE ];
} HWINFO_PACKED;


struct SEepromSettings
{
   char reserved[ 0x20 - RETAIN_HEADER_SIZE ];
} HWINFO_PACKED;


class CCommandHwInfo: public CCommand
{
      CFlashX &m_eeprom;
      SEepromHwInfoCustom m_hwData;
      SEepromSettings m_settings;
      
      CRetain *m_pRetainHwData;
      CRetain *m_pRetainSettings;
      
   public:
      CCommandHwInfo(const char *name, CFlashX &eeprom);
      virtual int exec(int argc, const char *argv[]) const;
      void dump() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_HWINFO_HPP
