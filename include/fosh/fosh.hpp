#ifndef FOSH_FOSH_HPP
#define FOSH_FOSH_HPP
/**---------------------------------------------------------------------------
 *
 * @file       fosh.hpp
 * @brief      Libfosh class
 *
 *             This class handles the input. When an command is entered into 
 *             the command line, the 'commander' is asked to actually exec the 
 *             command.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <lepto/string.hpp>
#include <lepto/signal.hpp>
#include <lepto/eventLoop.hpp>
#include <fosh/commander.hpp>

// Default behaviour: use login prompt
#if ! defined( CONFIG_FOSH_LOGIN )
   #define CONFIG_FOSH_LOGIN           1
#endif


/*--- Declaration ----------------------------------------------------------*/


class CCommand;

class CFosh: public CEventLoop
{
   private:
      CString command;
      CCommander m_commander;
      
      #if IS_ENABLED(CONFIG_FOSH_LOGIN)
      bool m_logedin;
      #endif
      
      #if ! defined( MCU_STM32 )
      bool m_inputTerminal=true;
      #endif

      #if IS_ENABLED( CONFIG_FOSH_CATCH_ANSI )
      enum class EMode{
         normal,
         preAnsi,
         ansi
      };
      EMode m_mode=EMode::normal;
      #endif // CONFIG_FOSH_CATCH_ANSI


   public:
      CFosh();
      //CSignal <int, int, char *> signalExecCommand;

      virtual_eventLoop void eventLoop() override_eventLoop;

      void handleChar(int c);
      #if IS_ENABLED( CONFIG_FOSH_CATCH_ANSI )
      void handlePreAnsi(int c);
      void handleAnsi(int c);
      #endif // CONFIG_FOSH_CATCH_ANSI

      void dump(const void *buf, int size);
      int execCommand();
      void printPrompt();
      
      #if IS_ENABLED(CONFIG_FOSH_LOGIN)
      void login(const void *buf , int size);
      #endif
      
      void addCommand(const CCommand *pCommand);

      template <typename E>
      struct SCommandDesc{
         E value;
         const char* name;
         int argc;
      };

      template <typename E>
      static E getCommandEnum( int argc, const char* argv[], const SCommandDesc<E>* commands, int count )
      {
         if( argc <= 1 )
         {
            return( E::None );
         }

         for(int index=0; index<count; index++)
         {
            if( ! strcmp(argv[1], commands[index].name ) )
            {
               if( argc-2 < commands[index].argc )
               {
                  lDebug("Invalid args: Is: %d; should: %d\n", argc - 2, commands[index].argc);
                  return( E::InvalidArguments );
               }
               return( commands[index].value );
            }
         }

         return( E::UnknownCommand );
      }
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ! ? FOSH_FOSH_HPP
