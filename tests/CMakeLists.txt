#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for miniminutnik (host)
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)

project( fosh_tests )

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
   ${CATCH2_TARGET}
)

add_test(
   NAME fosh_tests
   COMMAND fosh_tests
   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)


#------------------------------------------------------------------------------
