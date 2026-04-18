#ifndef FOSH_COMMAND_STANDBY_HPP
#define FOSH_COMMAND_STANDBY_HPP
/**---------------------------------------------------------------------------
 *
 * @file       standby.hpp
 * @brief      Libfosh command to put MCU into standby
 *
 *             Put MCU into standby.
 *
 *  \date      20251203
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>
#include <HALWrapper/stm32_hal.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandStandby: public CCommand
{
   public:
      CCommandStandby(const char *_name)
         :CCommand( _name, "Stop device" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


int CCommandStandby::exec(int argc, const char *argv[]) const /* virtual */
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvolatile"
      
      __HAL_RCC_GPIOA_CLK_ENABLE();
      __HAL_RCC_GPIOB_CLK_ENABLE();
      __HAL_RCC_GPIOC_CLK_ENABLE();
      __HAL_RCC_TIM2_CLK_DISABLE();
      __HAL_RCC_I2C1_CLK_DISABLE();
      __HAL_RCC_USART2_CLK_DISABLE();
      #if defined __HAL_RCC_DBGMCU_CLK_DISABLE
      __HAL_RCC_DBGMCU_CLK_DISABLE();
      #endif
      __HAL_RCC_SYSCFG_CLK_DISABLE();
      // __HAL_RCC_PWR_CLK_SLEEP_ENABLE();
      HAL_DBGMCU_DisableDBGStandbyMode();
      
      __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
      
#pragma GCC diagnostic pop
      
   HAL_PWR_EnterSTANDBYMode();
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_STANDBY_HPP
