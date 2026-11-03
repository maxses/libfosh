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

#if 1

class CMyApplication2
{
      int m_executionCounter[2]{};
   public:

      enum ECommand
      {
         None,
         command1,
         command2,
         UnknownCommand,
         InvalidArguments
      };

      CMyApplication2(const char* name)
      {
         
      }

      int executionCounter( int index )
      {
         return( m_executionCounter[index] );
      }

      int exec( CMyApplication2::ECommand eCommand, int argc, const char * argv[] )
      {
         (void)argc;
         (void)argv;
         
         switch( eCommand )
         {
            case ECommand::command1:
               m_executionCounter[0]++;
               break;
            case ECommand::command2:
               m_executionCounter[1]++;
               break;
            case ECommand::UnknownCommand:
               return(21);
               break;
            case ECommand::InvalidArguments:
               return(23);
               break;
            default:
               break;
         }

         return(0);
      }
};


TEST_CASE( "subSignal", "[default]" )
{
   SECTION( "subSignal" )
   {
      /*
       * Create a signal command with connection to application.
       * Verify that it was executed.
       */

      CFosh m_fosh;
      CMyApplication2 myApplication("name");

      CCommandSubSignal<CMyApplication2::ECommand>* subSignal;
      subSignal=new CCommandSubSignal<CMyApplication2::ECommand>(
               "commandSub", "Description", &myApplication, &CMyApplication2::exec );
      
      subSignal->setSubcommands(
          ( CCommandSubSignal<CMyApplication2::ECommand>::SSubCommandDesc[] ) {
            { CMyApplication2::ECommand::command1, "command1", 0, 0, },
            { CMyApplication2::ECommand::command2, "command2", 0, 0, },
          }
          , 2
      );
      
      m_fosh.addCommand( subSignal );

      const char* ar1[] = {"commandSub" ,"command1", nullptr};
      const char* ar2[] = {"commandSub" ,"command2", nullptr};
      const char* ar3[] = {"commandSub" ,"command3", nullptr};
      const char* ar4[] = {"commandBus" ,"command4", nullptr};
      int sta;
      
      // General check for matching
      
      sta=m_fosh.commander().execCommand(2, ar1);

      REQUIRE ( sta == 0 );
      REQUIRE ( myApplication.executionCounter(0) == 1 );
      REQUIRE ( myApplication.executionCounter(1) == 0 );
      
      sta=m_fosh.commander().execCommand(2, ar2);
      
      REQUIRE ( sta == 0 );
      REQUIRE ( myApplication.executionCounter(0) == 1 );
      REQUIRE ( myApplication.executionCounter(1) == 1 );
      
      sta=m_fosh.commander().execCommand(2, ar3);

      REQUIRE ( sta == 21 );
      REQUIRE ( myApplication.executionCounter(0) == 1 );
      REQUIRE ( myApplication.executionCounter(1) == 1 );
      
      sta=m_fosh.commander().execCommand(2, ar4);
      
      REQUIRE ( sta == 22 );
      REQUIRE ( myApplication.executionCounter(0) == 1 );
      REQUIRE ( myApplication.executionCounter(1) == 1 );
      
      // Check for argument mismatch
      
      sta=m_fosh.commander().execCommand(4, ar1);
      REQUIRE ( sta == 23 );
      REQUIRE ( myApplication.executionCounter(0) == 1 );
      REQUIRE ( myApplication.executionCounter(1) == 1 );
      
   }
}; // TEST_CASE

#endif

//---fin----------------------------------------------------------------------
