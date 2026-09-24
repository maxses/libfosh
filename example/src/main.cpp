/**---------------------------------------------------------------------------
 *
 * @file       main.cpp
 * @brief      Example for integration of libfosh
 *
 *  \date      20260706
 *  \author    Maximilian Seesslen <src@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/fosh.hpp>
#include <fosh/commands/signal.hpp>
#include <fosh/allCommands.hpp>
#include <lepto/eventLoop.hpp>
#include "application.hpp"
#include "hello.hpp"


/*--- Implementation -------------------------------------------------------*/


int main( int argc, const char* argv[] )
{
   CApplication bApp(argc, argv);
   
   CHello *pHello=new CHello;
   (void)pHello;

   return( bApp.exec() );
}


/*--- Fin ------------------------------------------------------------------*/
