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
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/subCommands.hpp>
#include <biwak/flash_spi.hpp>


/*--- Declarations ---------------------------------------------------------*/


enum ESfCommand{
   eNone,
   eInfo,
   eDump,
   eErase,
   eRead,
   eWrite,
   eChipErase,
   eSearch,
};

class CCommandSf: public CCommandSubCommands<ESfCommand>
                  //<ESfCommand>
{
      CFlashSpi &m_sf;
      
      const SSubCommandDesc m_subCommands[6]{
          (SSubCommandDesc){ eInfo, "info", "Show information", 0, 0, "" },
          (SSubCommandDesc){ eDump, "dump", "Dump part of erase block", 1, 1, "<address>" },
          (SSubCommandDesc){ eWrite, "write", "Write pattern to block", 1, 1, "<address>" },
          (SSubCommandDesc){ eChipErase, "chiperase", "Erase the whole chip", 0, 0, ""},
          (SSubCommandDesc){ eSearch, "search", "Search for nonempty page", 0, 0, ""},
          (SSubCommandDesc){ eInfo, nullptr, nullptr, 0, 0, "" },
      };
      
   public:
      CCommandSf(const char *_name, CFlashSpi &sf)
         :CCommandSubCommands( _name, "Access spi flash" )
         ,m_sf(sf)
      {
         setSubcommands(m_subCommands);
      }
      virtual int execSubCommand(ESfCommand command, int argc, const char *argv[]) const;
      
      int info() const;
      int dump(int argc, const char* argv[]) const;
      int write(int argc, const char* argv[]) const;
      int search() const;
      int chipErase() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_SPI_FLASH_HPP
