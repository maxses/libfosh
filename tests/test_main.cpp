//----------------------------------------------------------------------------
///
/// \file   test_main.cpp
///
/// \brief  Main file for miniminutniks unit tests
///
/// \date   20260506
/// \author Maximilian Seesslen <src@seesslen.net>
///
//----------------------------------------------------------------------------


//---Documentation------------------------------------------------------------


//---Includes ----------------------------------------------------------------


#define CATCH_CONFIG_RUNNER

#if defined ( CATCH_V3 )
   #include <catch2/catch_test_macros.hpp>
   #include <catch2/catch_session.hpp>
#elif defined ( CATCH_V2 )
   #include <catch2/catch.hpp>
#elif defined ( CATCH_V1 )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif

#include <lepto/lepto.h>

#if defined USE_BIWAK
#include <biwak/biwak.h>
#endif


//--- Implementaion ----------------------------------------------------------


int main( int argc, char* argv[] )
{
   leptoInit();
   #if defined USE_BIWAK
      biwakInit();
   #endif

   int result = Catch::Session().run( argc, argv );
   return result;
}


//--- Fin --------------------------------------------------------------------
