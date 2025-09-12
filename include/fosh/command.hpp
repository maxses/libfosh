#ifndef FOSH_COMMAND_HPP
#define FOSH_COMMAND_HPP
/**---------------------------------------------------------------------------
 *
 * @file       command.hpp
 * @brief      Libfosh abstract base command class
 *
 *             See class documentation.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Declaration ----------------------------------------------------------*/


/**
 * @brief A single command
 *
 *        Each command must be inherited from CCommand.
 */
class CCommand
{
   private:
      const char *m_pName;
      const char *m_pHelpString;
   public:
      CCommand(const char *name, const char *helpString);
      ~CCommand()=default;
      const char*getName() const
      {
         return(m_pName);
      }

      virtual int exec(int argc, const char * argv[]) const = 0;
      void printHelp() const;
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_HPP
