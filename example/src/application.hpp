#ifndef FOSH_EXAMPLE_APPLICATION_HPP
#define FOSH_EXAMPLE_APPLICATION_HPP
//----------------------------------------------------------------------------
///
/// \brief   Example application
///
///          Simplify main.cpp by having Qt-like exec().
///
/// \date   20260706
/// \author Maximilian Seesslen <mes@seesslen.net>
///
//----------------------------------------------------------------------------


//---Includes-----------------------------------------------------------------


#include <lepto/lepto.h>            // IS_ENABLED( )
#include <lepto/units.h>            // MSEC_PER_SEC
#include <lepto/eventLoop.hpp>
#include <unistd.h>                 // usleep()


//---Declaration--------------------------------------------------------------


class CApplication
{
   public:
      CApplication( int argc=0, const char* argv[]=nullptr )
      {
         lUNUSED( argc );
         lUNUSED( argv );
         
         leptoInit();
      }
      
      int exec()
          __attribute__ (( noreturn ))
        #if ! IS_ENABLED( CONFIG_LEPTO_GLOBAL_EVENT_LOOP ) && ! IS_ENABLED( CONFIG_FOSH_EXAMPLES )
          __attribute__(( error("Please enable CONFIG_LEPTO_GLOBAL_EVENT_LOOP in lepto configuration") ))
        #endif
      ;
};


int CApplication::exec()
{
   while(1) 
   {
      leptoEventLoop();
      
      CEventLoop::globalEventLoop();
      
      usleep(1000);
   }
}


//---fin----------------------------------------------------------------------
#endif // ? ! FOSH_EXAMPLE_APPLICATION_HPP
