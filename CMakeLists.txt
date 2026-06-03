#------------------------------------------------------------------------------
#
# \brief	CMakeLists.txt file for "libfosh"
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)
project( fosh )

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
)

if( USE_BIWAK )

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
   )

   set(
      libfosh_HEADERS
         ${libfosh_HEADERS}
         include/fosh/commands/biwak/date.hpp
         include/fosh/commands/biwak/time.hpp
         include/fosh/commands/biwak/alarm.hpp
         include/fosh/commands/biwak/eeprom.hpp
   )

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
   
   # I'm not interested in porting those coommands for the host at the moment
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

endif( USE_BIWAK )

add_library( 
   ${PROJECT_NAME} 
   STATIC
      ${libfosh_SOURCES}
      ${libfosh_HEADERS}
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

if ( HOST )

add_subdirectory ( tests )

endif ( NOT HOST )


#------------------------------------------------------------------------------
