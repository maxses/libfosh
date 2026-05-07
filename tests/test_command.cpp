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

#include <fosh/command.hpp>


//---Implementation-----------------------------------------------------------


class CCommandTest: public CCommand
{
   public:
      CCommandTest(const char* name)
           :CCommand(name, "Help string")
      {
         
      }
      virtual int exec(int argc, const char * argv[]) const override
      {
         return(0);
      }
};


TEST_CASE( "Mainswitch", "[default]" )
{
   SECTION( "TimeToSeconds" )
   {
      CCommandTest commandTest("name");

      REQUIRE ( strcmp( "foobar", "name") != 0 );
      REQUIRE ( commandTest.matches( "foobar", "name", false ) == false );
      REQUIRE ( commandTest.matchingIndex( "foobar", false) == -1 );
      REQUIRE ( commandTest.matchingIndex( "nameofone", true) == -1 );
      REQUIRE ( commandTest.matchingIndex( "nam", true) == 0 );
   }
}; // TEST_CASE


//---fin----------------------------------------------------------------------
