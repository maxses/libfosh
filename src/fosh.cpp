/**---------------------------------------------------------------------------
 *
 * @file       fosh.cpp
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


#include <fosh/fosh.hpp>
#include <fosh/commander.hpp>
#include <fosh/command.hpp>
#include <lepto/ansi.h>

#if defined ( HOST )  || ! defined( STM32 )
   #include <termios.h>       // tcgetattr
   #include <errno.h>         // errno
   #include <fcntl.h>         // fcntl
#else
   #include <unistd.h>        // usleep
   #include <lepto/log.h>        // blink
#endif

#if USE_BIWAK
   #include <biwak/biwak.h>
#endif


/*--- Implementation -------------------------------------------------------*/


class CCommand;


CFosh::CFosh()
   #if IS_ENABLED(CONFIG_FOSH_LOGIN)
   :m_logedin(false)
   #endif
{
   // Disable ECHO on Linux systems
   #if ! defined( STM32 )
   struct termios term, term_orig;
   
   if(tcgetattr(0, &term_orig))
   {
      printf("tcgetattr failed (%d)\n", errno);
      m_inputTerminal=false;
      return;
    }

    term = term_orig;
    term.c_lflag &= ~( ICANON | ECHO );

    if (tcsetattr(0, TCSANOW, &term))
    {
      printf("tcsetattr failed\n");
      exit(-1);
    }

    int flags = fcntl(stdin->_fileno, F_GETFL, 0);
    fcntl(stdin->_fileno, F_SETFL, flags | O_NONBLOCK); // non blocking

   #endif

   return;
}


void CFosh::addCommand(const CCommand *pCommand)
{
   m_commander.addCommand(pCommand);
}


void CFosh::printPrompt()
{
   #if USE_BIWAK
      // flush buffered logs
      //biwakEventLoop();
   #endif

   #if IS_ENABLED(CONFIG_FOSH_LOGIN)
   if(m_logedin)
   {
   #endif
      
      fputs( "$ ", stdout);
      
   #if IS_ENABLED(CONFIG_FOSH_LOGIN)
   }
   else
   {
      fputs( "\nlogin: ", stdout);
   }
   #endif
   
   return;
}


void CFosh::eventLoop()
{
   int in;
   static bool firstLoop=true;

   if(firstLoop)
   {
      printPrompt();
      firstLoop=false;
   }
   
   #if ! defined( STM32 )
      if( !m_inputTerminal )
      {
         return;
      }
   #endif

   do
   {
      // Returns EOF if no data is available (Linux, Biwak)
      //in=getchar();
      in=getc(stdin);

      /* Needed for debugging */
      #if 0
      if( in != EOF )
      {
         printf("Input: 0x%X\n", in);
      }
      #endif

      if( in != -1 )
      {
         #if IS_ENABLED( CONFIG_FOSH_CATCH_ANSI )
            switch(m_mode)
            {
               case EMode::normal:
                  handleChar(in);
                  break;
               case EMode::preAnsi:
                  handlePreAnsi(in);
                  break;
               case EMode::ansi:
                  handleAnsi(in);
                  break;
               default:
                  lCritical( LDS("UKM %d", "Unknown mode: %d"), m_mode);
                  break;
            }
         #else
            handleChar(in);
         #endif // CONFIG_FOSH_CATCH_ANSI
      }
   }
   while( in != EOF );

   return;
};


void CFosh::handleChar(int in)
{
   switch(in)
   {
      case '\r':     // STM32
      case '\n':     // Linux
      {
         fputs("\r\n", stdout);
         if( command.length() )
         {
            int sta=execCommand();
            if(sta)
            {
               // Don't make it an error/info. Its just an command that failed.
               // If command does not exist, CCommander will show error.
               // If real command has issue, it wil probably print it by itself
               lDebug( LDS("ExCo %d", "Error exec. command: %d"), sta);
            }
         }
         command.clear();
         printPrompt();
         break;
      }
      case EOF:
         break;
      case 0:
         // Decode not finished
         break;
      case '\t':
      {
         int index;
         const CCommand *c=m_commander.findCommand( command.data(), index );
         if( c )
         {
            for(int i1=0; i1<command.length(); i1++ )
            {
               fputs(ANSI_DELETE " " ANSI_DELETE, stdout);
            }
            command=c->getName( index );
            fputs( command.data(), stdout );
         }

         break;
      }
      case 0x08:  // Backspace;  0x8 in Minicom
      case 0x7f:  //             0x7F in TIO
         if( command.length() )
         {
            command.remove(-1,1);
            fputs(ANSI_DELETE " " ANSI_DELETE, stdout);
         }
         break;
      #if IS_ENABLED( CONFIG_FOSH_CATCH_ANSI )
      case 0x1B: // ESC
      {
         m_mode=EMode::preAnsi;
         break;
      }
      #endif // CONFIG_FOSH_CATCH_ANSI
      default:
         command+=(char)in;
         putchar(in);
   };
   return;
}

#if IS_ENABLED( CONFIG_FOSH_CATCH_ANSI )

void CFosh::handlePreAnsi(int in)
{
   switch( in )
   {
      case '[':
      {
         m_mode=EMode::ansi;
         break;
      }
      default:
         m_mode=EMode::normal;
         printf("UK1:0x%X\n", in);
         break;
   };
   return;
}


void CFosh::handleAnsi(int in)
{
   switch( in )
   {
      case 'D': // Left cursor
      {
         m_mode=EMode::normal;
         break;
      }
      case 'C': // Right cursor
      {
         m_mode=EMode::normal;
         break;
      }
      case 'A': // Up cursor
      {
         m_mode=EMode::normal;
         break;
      }
      case 'B': // Down cursor
      {
         m_mode=EMode::normal;
         break;
      }
      default:
         m_mode=EMode::normal;
         printf("ANSI:0x%X / '%c'\n", in, in);
         break;
   };
   return;
}

#endif // CONFIG_FOSH_CATCH_ANSI

int CFosh::execCommand()
{
   char *line=command.data();
   
   #if IS_ENABLED(CONFIG_FOSH_LOGIN)
   if(!m_logedin)
   {
      login( command.data(), strlen(command.data()) );
      return(0);
   }
   #endif

   int argc=0;
   const char *argv[10];

   if(line[0])
   {
      argv[argc++]=&line[0];
      for(int i1=0; line[i1] && argc<10; i1++)
         if(line[i1]==' ')
         {
            line[i1]=0;
            argv[argc++]=&line[i1+1];
         }
   }
   return ( m_commander.execCommand( argc, argv) );
}

#if IS_ENABLED(CONFIG_FOSH_LOGIN)

void CFosh::login(const void *buf, int size)
{
   if(!memcmp(buf, "admin", strlen("admin")))
   {
      m_logedin=true;
      fputs( LDS("Ok\n", "Successfully logged in\n"), stdout );
   }
   else
   {
      fputs( LDS( "use 'admin'\n",
               "Login not successfull. Type 'admin' to log in.\n"), stdout );
      fputs("\n", stdout);
   }

   return;
}

#endif // ? CONFIG_FOSH_LOGIN


/*--- Fin ------------------------------------------------------------------*/
