#ifndef FOSH_EXAMPLE_HELLO_HPP
#define FOSH_EXAMPLE_HELLO_HPP
/**---------------------------------------------------------------------------
 *
 * @file       hello.hpp
 * @brief      Libfosh example
 *
 *             Print hello world
 *
 * @date       20260706
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/fosh.hpp>
#include <fosh/allCommands.hpp>
#include <fosh/commands/signal.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CHello: public CFosh
{
   public:
      CHello()
      {
         addAllCommands( this );
         addCommand( new CCommandSignal(
                        "hello",
                        "Print hello world string", this, &CHello::commandHello ) );
         addCommand( new CCommandSignal(
                        "key",
                        "Print ASCII codes of input", this, &CHello::commandKey ) );
      }

      int commandHello( int argc, const char *argv[] )
      {
         printf( "Hello world!\n" );
         printf( "   argc: %d\n", argc );
         for(int i1=0; i1<argc; i1++)
         {
            printf( "   argv[%d]: '%s'\n", i1, argv[i1] );
         }

         return(0);
      };

      int commandKey( int argc, const char *argv[] )
      {
         int input;
         (void)argc;
         (void)argv;

         printf( "Press <Enter> to abort\n" );
         do{
            input=getc(stdin);

            if( input != -1 )
            {
               printf( "0x%X\n", input );
            }

         }while( input != '\n' );

         return(0);
      }
};




/*--- Fin ------------------------------------------------------------------*/
#endif // ? FOSH_EXAMPLE_HELLO_HPP
