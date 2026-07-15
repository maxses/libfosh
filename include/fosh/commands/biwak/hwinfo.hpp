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

#if IS_ENABLED( CONFIG_FOSH_HWINFO_LIB )
   #include <hwinfo/hwinfo.h>
#endif


/*--- Declaration ----------------------------------------------------------*/


struct SEepromHwInfoCustom: public SEepromHwInfoBase
{
   char reserved[ 0x40 - sizeof( SEepromHwInfoBase ) - RETAIN_HEADER_SIZE ];
} HWINFO_PACKED;


struct SEepromConfigCustom: public SEepromConfigBase
{
   char reserved[ 0x20 - RETAIN_HEADER_SIZE - sizeof( SEepromConfigBase ) ];
} HWINFO_PACKED;


class CCommandHwInfo: public CCommand
{
   #if IS_ENABLED( CONFIG_FOSH_HWINFO_LIB )
      CHwInfo& m_hwInfo;
   #else
      CFlashX &m_eeprom;
      SEepromHwInfoCustom m_hwData;
      SEepromConfigCustom m_config;
      
      CRetain *m_pRetainHwData;
      CRetain *m_pRetainConfig;
   #endif
   
   public:
   
      #if IS_ENABLED( CONFIG_FOSH_HWINFO_LIB )
         CCommandHwInfo(const char *name, CHwInfo&);
      #else
         CCommandHwInfo(const char *name, CFlashX &eeprom);
      #endif
         
      virtual int exec(int argc, const char *argv[]) const;
      int printHwInfo() const;
      int printConfig() const;
      void dump() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_HWINFO_HPP
