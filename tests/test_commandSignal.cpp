//----------------------------------------------------------------------------
//
// \brief   Test for libfosh
///
/// \date   20260506
/// \author Maximilian Seesslen <src@seesslen.net>
///
//----------------------------------------------------------------------------


//---Includes-----------------------------------------------------------------


#if defined ( CATCH_V3 )
   #include <catch2/catch_test_macros.hpp>
#elif defined ( CATCH_V2 )
   #include <catch2/catch.hpp>
#elif defined ( CATCH_V1 )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif

#include <fosh/fosh.hpp>
#include <fosh/command.hpp>
#include <fosh/commands/signal.hpp>
#include <fosh/commands/subSignal.hpp>


//---Implementation-----------------------------------------------------------


// CONFIG_FOSH_PSEUDO_VIRTUAL only supports CONFIG_FOSH_SIMPLE_SIGNAL_ONLY
#if ! IS_ENABLED( CONFIG_FOSH_PSEUDO_VIRTUAL )

class CMyApplication
{
      int m_executionCounter=0;
   public:
      CMyApplication()
      {
         
      }

      int executionCounter()
      {
         return( m_executionCounter );
      }

      int exec(int argc, const char * argv[])
      {
         (void)argc;
         (void)argv;

         m_executionCounter++;

         return(0);
      }
};


TEST_CASE( "Signal", "[default]" )
{
   SECTION( "simple" )
   {
      /*
       * Create a signal command with connection to application.
       * Verify that it was executed.
       */

      CFosh m_fosh;
      CMyApplication myApplication;

      m_fosh.addCommand( new CCommandSignal( "commandName", "Description",
         &myApplication, &CMyApplication::exec ) );

      const char* ar1[] = {"commandName" ,"arg1", nullptr};
      const char* ar2[] = {"commandNama" ,"arg1", nullptr};
      int sta;
      sta=m_fosh.commander().execCommand(2, ar1);

      REQUIRE ( sta == 0 );
      REQUIRE ( myApplication.executionCounter() == 1 );

      sta=m_fosh.commander().execCommand(2, ar2);

      REQUIRE ( sta == 22 );
      REQUIRE ( myApplication.executionCounter() == 1 );
   }
}; // TEST_CASE

#endif // ? ! CONFIG_FOSH_PSEUDO_VIRTUAL


//---fin----------------------------------------------------------------------
