#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for miniminutnik (host)
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)

project( fosh_tests )

if( 0 )
find_package( Catch2 )
if( NOT Catch2_FOUND )
   find_package( Catch )
   if( NOT Catch_FOUND )
      # find_package does not work for Catch, at least on ubuntu 20.04
      if( EXISTS /usr/include/catch )
         add_definitions( "-DCATCH_V1" )
      elseif( EXISTS /usr/include/catch2 )
         if( EXISTS /usr/include/catch2/catch_test_macros.hpp )
            add_definitions( "-DCATCH_V3" )
         else()
            add_definitions( "-DCATCH_V2" )
         endif()
      else( EXISTS /usr/include/catch2 )
         message( FATAL_ERROR "Install eeither Catch or Catch2")
      endif( EXISTS /usr/include/catch )
   endif( NOT Catch_FOUND )
   add_definitions( "-DCATCH_V1" )
else( NOT Catch2_FOUND)
   add_definitions( "-DCATCH_V3" )
   set( CATCH_LIBRARY "Catch2::Catch2WithMain" )
endif( NOT Catch2_FOUND )
endif( 0 )

# Catch2 v3?
find_package(Catch2 3 QUIET)

if (Catch2_FOUND)
    message(STATUS "Using Catch2 v3")
    add_definitions( "-DCATCH_V3" )
    set(CATCH2_TARGET Catch2::Catch2WithMain)
else()
    # Catch2 v2?
    find_package(Catch2 2 REQUIRED)
    message(STATUS "Using Catch2 v2")
    add_definitions( "-DCATCH_V2" )
    set(CATCH2_TARGET Catch2::Catch2)
endif()

add_executable(
   ${PROJECT_NAME}
   test_main.cpp
   test_command.cpp
)


target_link_libraries(
   ${PROJECT_NAME}
   fosh
   lepto
   ${CATCH_LIBRARY}
)


add_test(
   NAME fosh_tests
   COMMAND fosh_tests
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------------------------
