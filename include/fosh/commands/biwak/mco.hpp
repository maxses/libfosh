#ifndef FOSH_COMMAND_MOC_HPP
#define FOSH_COMMAND_MOC_HPP
/**---------------------------------------------------------------------------
 *
 * @file       moc.hpp
 * @brief      Libfosh command for enabling MCO, the clock output pin
 *
 *             Hardcoded stuff.
 *
 *  \date      20260710
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>

#if defined(STM32)
   //#include <arena/platform.h>
   #include <biwak/voc.h>
   #include <biwak/flash_spi.hpp>
   #include <biwak/rcc.h>
   #include <HALWrapper/stm32_rcc.h>
   #include <HALWrapper/stm32_gpio.h>
#else
   #include <biwak/i2c.hpp>
   #include <biwak/i2c_slave.h>
#endif


/*--- Declaration ----------------------------------------------------------*/


class CCommandMco: public CCommand
{
   public:
      CCommandMco(const char *_name)
         :CCommand( _name, "Enable MCO" )
      {}
      virtual int exec(int argc, const char *argv[]) const
      {
         #if defined STM32
            GPIO_InitTypeDef GPIO_InitStructure;
            
            // 1. Clock für GPIOA aktivieren
            __HAL_RCC_GPIOA_CLK_ENABLE();
            
            // 2. PA8 als Alternate Function Push-Pull (AF_PP) mit 50 MHz konfigurieren
            GPIO_InitStructure.Pin = GPIO_PIN_8;
            GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
            GPIO_InitStructure.Pull = GPIO_NOPULL;
            
            HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
            
            // 3. Wähle die gewünschte Taktquelle für den MCO-Pin aus 
            // (Hier als Beispiel: Systemtakt SYSCLK)
            //HAL_RCC_MCOConfig( RCC_MCO );
            HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
         #endif
         
         lInfo("MCO enabled\n");
         return(0);
      }
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_I2C_HPP
