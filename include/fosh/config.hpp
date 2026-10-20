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


#if defined ( FOSH_LOCAL_CONFIG )
   #include <fosh/config_generated_local.h>
#else
   #include <fosh/config_generated.h>
#endif

#if ! defined( FOSH_CONFIGURED )
   #error FOSH_CONFIGURED is not set. There is something wrong with config header.
#endif


/*--- Fin ------------------------------------------------------------------*/
#endif // ! ? FOSH_CONFIG_HPP
