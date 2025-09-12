#ifndef FOSH_COMMAND_SPI_FLASH_HPP
#define FOSH_COMMAND_SPI_FLASH_HPP
/**---------------------------------------------------------------------------
 *
 * @file       spi_flash.hpp
 * @brief      Libfosh command for spi flash
 *
 *             Just prints some informaation like JEDEC ID.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <biwak/flash_spi.hpp>


/*--- Declarations ---------------------------------------------------------*/


class CCommandSf: public CCommand
{
      CFlashSpi &m_sf;
   public:
      CCommandSf(const char *_name, CFlashSpi &sf)
         :CCommand( _name, "   sf: access spi flash\n" )
         ,m_sf(sf)
      {}
      virtual int exec(int argc, const char *argv[]) const;
      virtual void printHelp() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_SPI_FLASH_HPP
