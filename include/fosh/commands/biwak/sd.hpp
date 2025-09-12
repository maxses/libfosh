#ifndef FOSH_COMMAND_SD_HPP
#define FOSH_COMMAND_SD_HPP
/**---------------------------------------------------------------------------
 *
 * @file       sd.hpp
 * @brief      Libfosh command for SD card
 *
 *             Hardcoded stuff. Avoid including this command for now.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <biwak/sd.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandSd: public CCommand
{
   private:
      CSd &m_sd;
      enum ESubCommands
      {
         erase = 1,
         write,
         read,
         info,
         scan,
      };

      static constexpr struct SSubCommands
      {
         const char *string;
         int id;
         int minArgs;
         int maxArgs;
         const char *argumentsHelpString;
         const char *helpString;
      }m_subCommands[]=
      {
         { "erase", (int)ESubCommands::erase, 0, 1, "[block]", "erase single block"},
         { "write", (int)ESubCommands::write, 0, 1, "[block]", "write single block"},
         { "read" , (int)ESubCommands::read, 0, 1, "[block]", "read single block"},
         { "info" , (int)ESubCommands::info, 0, 0, "", "Show sd card info"},
         { "scan" , (int)ESubCommands::scan, 0, 0, "", "Scan whole card"},
      };

      static uint8_t m_data[0x200];

   public:
      CCommandSd( CSd &sd )
         :CCommand( "sd", "access sd card" )
         ,m_sd(sd)
      {}
      virtual int exec(int argc, const char *argv[]) const;
      virtual int execSubCommand(int id, int argc, const char *argv[]) const;
      int commandErase( int block ) const;
      int commandWrite( int block ) const;
      int commandRead( int block, bool dump=true ) const;
      int commandInfo(  ) const;
      int commandScan(  ) const;
      int optArg(int &dest, int argPos, int argc, const char *argv[]) const;
      virtual void printHelp() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_SD_HPP
