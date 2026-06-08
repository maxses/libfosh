/**---------------------------------------------------------------------------
 *
 * @file       hwinfo.cpp
 * @brief      Libfosh command for showing hwinfo
 *
 *  \date      20260529
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <hwinfo/hwinfo.h>
#include <fosh/commands/biwak/hwinfo.hpp>
#include <stdio.h>
#include <lepto/log.h>
#include <biwak/retain.h>
//#include <lepto/print.h>


/*--- Implementation--------------------------------------------------------*/


CCommandHwInfo::CCommandHwInfo(const char *name, CFlashX &eeprom)
   :CCommand( name, "Dump HWInfo" )
   ,m_eeprom(eeprom)
{
   m_pRetainHwData = new CRetain( m_eeprom, 0, 1 );
   m_pRetainHwData->setData(&m_hwData, sizeof(m_hwData)
                            , HWINFO_LAYOUT_MAJOR, HWINFO_LAYOUT_MINOR );
   
#if defined (USE_FULL_ASSERT)
   lAssert( m_pRetainHwData->getTotalSize() == 0x40 );
#endif
   if(m_pRetainHwData->restore()<0)
   {
      lCritical( LDS("NVHD", "No valid hwdata") );
   }
   
   m_pRetainConfig = new CRetain( m_eeprom, 0, 2 );
   m_pRetainConfig->setData(&m_config, sizeof(m_config), 0, 0 );
   
   if(m_pRetainConfig->restore()<0)
   {
      lCritical( LDS("NVCF", "No valid settings") );
   } 
}


int CCommandHwInfo::exec(int argc, const char *argv[]) const /* virtual */
{
   int container;
   int sta=0;

#if 1
   printf("Layout major: %d\n", HWINFO_LAYOUT_MAJOR);
   
   container=m_pRetainHwData->restore();
   
   if( container<0 )
   {
      fputs("Could not load eeprom data\n", stdout);
      sta=-1;
   }
   else
   {
      printf("Container:   %d\n", container);
#endif
      // printf("Data size:   0x%X\n", m_pRetainHwData->getTotalSize());
      // printf("Spare:       0x%X\n", m_pRetainHwData->spare());
      printf("ArticleID:   0x%X\n", m_hwData.main.articleId);
      printf("Boardcode:   0x%X\n", m_hwData.main.boardCode);
      // printf("Revision :   0x%X\n", m_hwData.main.boardRevision);
      #if HWINFO_LAYOUT_MAJOR == 7
      printf("Variant:     0x%X\n", (int)m_hwData.config.variant);
      #else
      printf("Variant:     0x%X\n", m_hwData.product.variant);
      #endif
      printf("Serialno.:   0x%X\n", (int)m_hwData.production.serialNumber);
   }
   
   return(sta);
}


void CCommandHwInfo::dump( ) const
{
}


/*--- Fin ------------------------------------------------------------------*/
