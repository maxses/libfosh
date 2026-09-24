#ifndef FOSH_COMMAND_SUB_SIGNAL_HPP
#define FOSH_COMMAND_SUB_SIGNAL_HPP
/**---------------------------------------------------------------------------
 *
 * @file       subSignal.hpp
 * @brief      Generic Libfosh command to provide further command via signals
 *
 * Combination of "CCommandSignal" and "CSubCommand".
 * An array can specify subcommands with name and custom enum.
 * The enum value will automatically be determined and put into the arguments.
 * Example:
 *    m_pConfigCommand=new CCommandSubSignal<ECommand>( "config",
 *             "Get/Set configuration", this, &CMiniMinutnik::commandConfig );
 *    m_pConfigCommand->setSubcommands( m_subCommands, m_subCommandCount );
 *    m_pFosh->addCommand( m_pConfigCommand );
 *
 * This feature costed 44 Bytes compared to direct CFosh::getCommandEnum()-method
 * on "Miniminutnik.
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <lepto/signal.hpp>


/*--- Declaration ----------------------------------------------------------*/


template <typename EEnum>
class CCommandSubSignal: public CCommand
{
   private:
      CSignal<int, EEnum, int, const char **> m_signal;

   public:
      struct SSubCommandDesc{
         EEnum command;
         const char* name;
         char minArgs;
         char maxArgs;

         #if IS_ENABLED( CONFIG_FOSH_CEATE_HELP )
            const char* desc;
            const char* argumentsHelpString;
         #endif
      };

   private:
      const SSubCommandDesc* m_subCommands = nullptr;
      int m_subCommandCount;

   public:

      #if IS_ENABLED( CONFIG_LEPTO_SIGNAL_FUNCTION )
       
      /** \brief  Constructor connecting the exec-signal to an function
       * 
       *          example: 
       *             new CCommandSignal( "hello", "Hello World"
       *                      , &hello )
       */
      CCommandSignal(const char *_name, const char *desc, int (*_funcPtr)( int, const char *[] ))
         :CCommand( _name, desc )
      {
         m_signal.connect( _funcPtr);
      }
      
      #endif // ? CONFIG_LEPTO_SIGNAL_FUNCTION
      
      /** \brief  Constructor connecting the exec-signal to an object slot
       * 
       *          example: 
       *             new CCommandSignal( "eraseflash", "Erase media flash"
       *                      , pCanDis, &CCanDis::eraseFlash )
       */
      template <class slotClass >
      CCommandSubSignal(const char *_name, const char *desc, slotClass *slotObject
                        , int (slotClass::*_methodPtr)( EEnum, int, const char ** ))
          :CCommand( _name, desc )
      {
         m_signal.connect(slotObject, _methodPtr);
      }
      
      virtual int exec(int argc, const char *argv[]) const override final;

      void setSubcommands(const SSubCommandDesc* subCommands, int subCommandCount)
      {
         m_subCommands = subCommands;
         m_subCommandCount = subCommandCount;
         return;
      }

      #if IS_ENABLED( CONFIG_FOSH_PRINT_HELP )
      virtual void printHelp() override
      {
         CCommand::printHelp();
         int index=0;
         while( m_subCommands[index].name )
         {
            int width=0;
            width+=printf("   ");
            width+=printf("   ");
            width+=printf("%s %s", m_subCommands[index].name
                             , m_subCommands[index].argumentsHelpString);
            for(int i1=0; i1<25-width; i1++)
            {
               printf(" ");
            }
            printf("%s\n", m_subCommands[index].desc);

            index++;
         }
      }
      #endif
};


template <typename EEnum>
int CCommandSubSignal<EEnum>::exec(int argc, const char *argv[]) const /* virtual */
{
   EEnum command=EEnum::None;
   /*
    * The command itself is included in the argc.
    * config -> argc=1
    */

   lAssert( m_subCommands );

   if(argc > 1)
   {
      for( int i1=0; i1<m_subCommandCount; i1++ )
      {
         if( ! strcmp (argv[1], m_subCommands[i1].name ) )
         {
            if( ( ( argc - 2 ) < m_subCommands[i1].minArgs )
                || ( ( argc - 2 ) > m_subCommands[i1].maxArgs ) )
            {
               command=EEnum::InvalidArguments;
               break;
            }
            command=m_subCommands[i1].command;
            break;
         }
      }
      if( command == EEnum::None )
      {
         command=EEnum::UnknownCommand;
      }
   }

   return( m_signal.emitSingle( command, argc, argv) );
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_SUB_SIGNAL_HPP
