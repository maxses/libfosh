#ifndef FOSH_SUB_COMMAND_HPP
#define FOSH_SUB_COMMAND_HPP
/**---------------------------------------------------------------------------
 *
 * @file       subCommand.hpp
 * @brief      Libfosh command template for subcommands
 *
 *             An command has an second argument specifying an subcommand.
 *             Example:
 *                sf dump 0x100
 *
 *  \date      20250914
 * @author     Maximilian Seesslen <mes@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <lepto/signal.hpp>
#include <inttypes.h>                  // strtoimax()


/*--- Declaration ----------------------------------------------------------*/


template <typename EEnum>
class CCommandSubCommands: public CCommand
{
   protected:
      struct SSubCommandDesc{
         EEnum command;
         const char* name;
         const char* desc;
         int minArgs;
         int maxArgs;
         const char* argumentsHelpString;
      };
  private:
      const SSubCommandDesc* m_subCommands = nullptr;
      
   public:
      CCommandSubCommands(const char *_name, const char *desc )
          :CCommand( _name, desc )
      {
         //m_signal.connect(slotObject, _methodPtr);
      }
      
      virtual int exec(int argc, const char *argv[]) const override final;
      virtual int execSubCommand(EEnum command, int argc, const char *argv[]) const = 0;
      void setSubcommands(const SSubCommandDesc* subCommands)
      {
         m_subCommands = subCommands;
         return;
      }
      virtual void printHelp() const override;
      static int optArg(int &dest, int argPos, int argc, const char *argv[]);
};


template <typename EEnum>
int CCommandSubCommands<EEnum>::exec(int argc, const char *argv[]) const /* virtual */
{
   /*
    * The command itself is included in the argc.
    * config -> argc=1
    */
   
   if( !m_subCommands )
   {
      lWarning( "Subcommands are not set" );
      return(-1);
   }
   
   lDebug("argc: %d", argc);
   
   if(argc <= 1)
   {
      return( execSubCommand((EEnum)0, argc, argv) );
   }
   
   for(int i1=0; m_subCommands[i1].name; i1++)
   {
      if( (! strcmp (argv[1], m_subCommands[i1].name ) )
          || ( ( strlen(argv[1]) == 1 ) && ( argv[1][0] == m_subCommands[i1].name[0] ) ) )
      {
         --argc;
         ++argv;
         if( ( ( argc -1 ) < m_subCommands[i1].minArgs )
             || ( ( argc -1 ) > m_subCommands[i1].maxArgs ) )
         {
            printf("%s: invalid amount of arguments\n", getName());
            printf("\nUsage:\n");
            printHelp();
            return(-1);
         }
         return ( execSubCommand(m_subCommands[i1].command, argc, argv) );
         break;
      }
   }
   printf("%s: unknown argument '%s'\n", getName(), argv[1]);
   printf("\nUsage:\n");
   printHelp();
   return( -1 );
}


template <typename EEnum>
void CCommandSubCommands<EEnum>::printHelp() const /* virtual  */
{
   int cnt=0;
   
   #if IS_ENABLED( CONFIG_LEPTO_LOG_DOWNSIZE )
      fputs( "   ", stdout );
      fputs( getName(), stdout );
      printf( " [ " );
      for(int i1=0; m_subCommands[i1].name; i1++)
      {
         if( i1 )
         {
            printf( "| " );
         }
         printf( "%s ", m_subCommands[i1].name );
      }
      printf( "]");
      
      fputs(": ", stdout);
      fputs( getHelpString(), stdout );
      fputs("\n", stdout);
   #else
      cnt+=printf( "   %s",getName());
      /*
      if( m_subCommands[i1].argumentsHelpString )
      {
         cnt+=printf("%s", m_subCommands[i1].argumentsHelpString);
      }
      else
      */
      {
         cnt+=printf( " [ " );
         for(int i1=0; m_subCommands[i1].name; i1++)
         {
            if( i1 )
            {
               cnt+=printf( "| " );
            }
            cnt+=printf( "%s ", m_subCommands[i1].name );
         }
         cnt+=printf( "]");
      }
      
      for(int i1=0; i1<25-cnt; i1++ )
      {
         printf(" ");
      }
      printf( "%s\n", getHelpString() );
   #endif
   
   for(int i1=0; m_subCommands[i1].name; i1++)
   {
      cnt=printf( "      %s ", m_subCommands[i1].name);
      if( m_subCommands[i1].argumentsHelpString )
      {
         cnt+=printf("%s", m_subCommands[i1].argumentsHelpString);
      }
      else
      {
         for( int i2=0; i2<m_subCommands[i1].minArgs; i2++ )
         {
            cnt+=printf("<arg%d> ", i2);
         }
      }
      for(int i1=0; i1<25-cnt; i1++ )
      {
         printf(" ");
      }
      printf( "%s\n"
             , m_subCommands[i1].desc );
   }
   return;
}


template <typename EEnum>
int CCommandSubCommands<EEnum>::optArg(int &dest, int argPos, int argc, const char *argv[])
{
   if( argc > argPos )
   {
      char *end;
      dest=strtoimax(argv[ argPos ], &end, 0);
      if( end != argv[ argPos ] + strlen(argv[argPos]) )
      {
         lCritical("Could not read integer");
         return(-1);
      }
   }
   return(0);
}


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_SUB_COMMAND_HPP
