#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for "libfosh"
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( fosh )

enable_testing()

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR) # PROJECT_IS_TOP_LEVEL

    set ( CMAKE_CXX_STANDARD 20 )

endif()

if( TARGET lepto )
   find_package( leptoGitVersion REQUIRED )
   find_package( leptoConfigHeader REQUIRED )
endif( TARGET lepto )

if ( CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR ) # PROJECT_IS_TOP_LEVEL
   add_compile_options( 
      -Wall
      -Werror
      -flto
      -Wodr
      -Wl,-lto
      -Wl,-Werror
      -Wl,-Wall
   )
endif()

set(
   libfosh_SOURCES
      src/fosh.cpp
      src/commander.cpp
      src/command.cpp
      src/subCommands.cpp
      src/allCommands.cpp
      src/commands/signal.cpp
      src/commands/function.cpp
      src/commands/exit.cpp
      src/commands/memory.cpp
      src/commands/clear.cpp
      src/commands/log.cpp
)

set(
   libfosh_HEADERS
      include/fosh/fosh.hpp
      include/fosh/allCommands.hpp
      include/fosh/commands/log.hpp
      include/fosh/commands/clear.hpp
      include/fosh/commands/exit.hpp
      include/fosh/commands/memory.hpp
      include/fosh/commands/signal.hpp
      include/fosh/commands/function.hpp
      
      ${GIT_VERSION_HEADER}
)

if( TARGET lepto )
   set(
      libfosh_SOURCES
      ${libfosh_SOURCES}
      src/commands/version.cpp
   )
   set(
      libfosh_HEADERS
      ${libfosh_HEADERS}
      fosh/config_generated_local.h
      include/fosh/commands/version.hpp
   )
endif( TARGET lepto )

if( TARGET biwak )

   set(
      libfosh_SOURCES
         ${libfosh_SOURCES}
         src/commands/biwak/date.cpp
         src/commands/biwak/time.cpp
         src/commands/biwak/info.cpp
         src/commands/biwak/spi_flash.cpp
         src/commands/biwak/i2c.cpp
         src/commands/biwak/alarm.cpp
         src/commands/biwak/eeprom.cpp
         src/commands/biwak/reset.cpp
   )

   set(
      libfosh_HEADERS
         ${libfosh_HEADERS}
         include/fosh/commands/biwak/date.hpp
         include/fosh/commands/biwak/time.hpp
         include/fosh/commands/biwak/alarm.hpp
         include/fosh/commands/biwak/eeprom.hpp
   )

   if( NOT HOST )
      set(
         libfosh_SOURCES
            ${libfosh_SOURCES}
            src/commands/biwak/stop.cpp
            src/commands/biwak/standby.cpp
      )
   
      set(
         libfosh_HEADERS
            ${libfosh_HEADERS}
            include/fosh/commands/biwak/stop.hpp
            include/fosh/commands/biwak/standby.hpp
      )
      
   endif( NOT HOST )

   if( NOT ( ( "${MCU_REV}" MATCHES "l0" ) OR ( "${MCU_REV}" MATCHES "l1" ) ) )
      set(libfosh_SOURCES
            ${libfosh_SOURCES}
            src/commands/biwak/candump.cpp
         )
      set(libfosh_HEADERS
            ${libfosh_HEADERS}
            include/fosh/commands/biwak/candump.hpp
         )
   endif( NOT ( ( "${MCU_REV}" MATCHES "l0" ) OR ( "${MCU_REV}" MATCHES "l1" ) ) )

   if( ( "${MCU_REV}" MATCHES "l4" ) OR ( "${MCU_PLATFORM}" MATCHES "linux" ) )
      set(libfosh_SOURCES
            ${libfosh_SOURCES}
            src/commands/biwak/sd.cpp
         )
      set(libfosh_HEADERS
            ${libfosh_HEADERS}
            include/fosh/commands/biwak/sd.hpp
         )
   endif( ( "${MCU_REV}" MATCHES "l4" ) OR ( "${MCU_PLATFORM}" MATCHES "linux" ) )

   set(
      LIBRARIES
         ${LIBRARIES}
         biwak
   )
   
   # I'm not interested in porting those commands for the host at the moment
   if( NOT HOST )

      set(
         libfosh_SOURCES
            ${libfosh_SOURCES}
      )

   endif( NOT HOST )

   if( USE_HWINFO )
      
      set(
         libfosh_SOURCES
            ${libfosh_SOURCES}
            src/commands/biwak/hwinfo.cpp
         )
      
      set( 
         libfosh_HEADERS
            ${libfosh_HEADERS}
            include/fosh/commands/biwak/hwinfo.hpp
      )
   
      set(
         LIBRARIES
            ${LIBRARIES}
            hwinfo
      )

   endif( USE_HWINFO )

endif( TARGET biwak )

add_library( 
   ${PROJECT_NAME} 
   STATIC
      ${libfosh_SOURCES}
      ${libfosh_HEADERS}
)

if ( COMMON_CONFIG_HEADER )
   set ( FOSH_CONFIG_HEADER "${COMMON_CONFIG_HEADER}" )
elseif( NOT FOSH_CONFIG_HEADER )
   set ( FOSH_CONFIG_HEADER "include/fosh/presets/config_full.h" )
endif()


if( TARGET lepto )

   add_generated_config( ${PROJECT_NAME} )

else( TARGET lepto )

   find_library( lepto lepto )

   if( NOT lepto )
      message( FATAL_ERROR "Please install liblepto to your sysroot or add it as subdirectory to your project" )
   else()
      message( "Found liblepto: ${lepto}")
   endif( NOT lepto )

   add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/fosh/config_generated_local.h
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/fosh
      COMMAND cp include/fosh/presets/config_full.h ${CMAKE_CURRENT_BINARY_DIR}/fosh/config_generated_local.h
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/fosh/presets/config_full.h
   )

   add_custom_target(
      generate_fosh_config
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/fosh/config_generated_local.h
   )

   add_dependencies( fosh generate_fosh_config )

   target_include_directories (
      fosh
      PUBLIC
         ${CMAKE_CURRENT_BINARY_DIR}
   )

   install (
      FILES
         ${CMAKE_CURRENT_BINARY_DIR}/fosh/config_generated_local.h
      DESTINATION
         include/fosh
      RENAME
         config_generated.h
      COMPONENT Devel
   )

endif( TARGET lepto )

# Don't you dare to use a sysroots config header!
target_compile_definitions(
   ${PROJECT_NAME}
   PUBLIC
      -DFOSH_LOCAL_CONFIG
)

target_link_libraries(
   ${PROJECT_NAME}
      lepto
      ${LIBRARIES}
)

target_include_directories(
   ${PROJECT_NAME} 
   INTERFACE
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
   PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

install(
   TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
   RUNTIME DESTINATION bin
   INCLUDES DESTINATION include
)

# Includes have to be installed manually for some reason
install(
   DIRECTORY
      include/fosh
   DESTINATION
      include
   COMPONENT Devel
   PATTERN
      include/fosh/presets EXCLUDE
)

install (
   FILES
      LICENSE
   DESTINATION
      share/doc/libfosh
)

if ( HOST )

   add_subdirectory ( tests )
   add_subdirectory ( example )

endif ( HOST )


#------------------------------------------------------------------------------
