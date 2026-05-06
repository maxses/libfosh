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
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <lepto/lepto.h>


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
      //struct SAlias;
      //const char **m_pAliases;
      
   #if IS_ENABLED( CONFIG_FOSH_COMMAND_ALIASES )
      
   public:
      struct SAlias{
         const char* name;
         const char* desc;
      };
   private:
      const SAlias *m_pAliases;
       
   #endif // ? CONFIG_FOSH_COMMAND_ALIASES
      
   public:
      CCommand(const char *name, const char *helpString);
      ~CCommand()=default;
      const char*getName( int index = 0 ) const
      {
         #if IS_ENABLED( CONFIG_FOSH_COMMAND_ALIASES )
         if(!index)
            return(m_pName);
         
         return( m_pAliases[index-1].name );
         #else
         return(m_pName);
         #endif
      }
      const char*getHelpString() const
      {
         return(m_pHelpString);
      }

      virtual int exec(int argc, const char * argv[]) const = 0;
      static void printHelp(const char*name, const char*desc);
      virtual void printHelp() const;
      static bool matches(const char *str, const char *me, bool shortcut=false);
      int matches(const char *str, bool shortcut=false) const;
      
      #if IS_ENABLED( CONFIG_FOSH_COMMAND_ALIASES )
      
      CCommand* setAliases( const SAlias aliases[] )
      {
         m_pAliases=aliases;
         return( this );
      }

      #endif
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_HPP
