#ifndef FOSH_COMMAND_STOP_HPP
#define FOSH_COMMAND_STOP_HPP
/**---------------------------------------------------------------------------
 *
 * @file       reset.hpp
 * @brief      Libfosh command to put MCU into stop mode
 *
 *             Stop the MCU.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <stdlib.h>
#include <HALWrapper/stm32_hal.h>


/*--- Declaration ----------------------------------------------------------*/


class CCommandStop: public CCommand
{
   public:
      CCommandStop(const char *_name)
         :CCommand( _name, "Stop device" )
      {}
      virtual int exec(int argc, const char *argv[]) const;
};


int CCommandStop::exec(int argc, const char *argv[]) const /* virtual */
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
      
   // HAL_PWR_EnterSTOPMode( PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI );
   HAL_PWR_EnterSTOPMode( PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI );
      
   // biwakInit brings device up, but periphery is still uninitialized.
   NVIC_SystemReset();
   
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_STOP_HPP
