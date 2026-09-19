#ifndef FOSH_CONFIG_HPP
#define FOSH_CONFIG_HPP
/**---------------------------------------------------------------------------
 *
 * @file       config.hpp
 * @brief      Include correct config header
 *
 * @date       20260919
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#if defined( FOSH_GENERATED_CONFIG )
   #include "config_generated_fosh.h"
#else
   #include <fosh/config.h>
#endif

#if ! defined( FOSH_CONFIGURED )
   #error FOSH_CONFIGURED is not set. There is something wrong with config header.
#endif


/*--- Fin ------------------------------------------------------------------*/
#endif // ! ? FOSH_CONFIG_HPP
