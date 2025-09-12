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
      src/commands/signal.cpp
      src/commands/exit.cpp
)

set(
   libfosh_HEADERS
      include/fosh/fosh.hpp
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
   )

   # I'm not interested in porting those coommands for the host at the moment
   if( NOT HOST )

      set(
         libfosh_SOURCES
            ${libfosh_SOURCES}
      )

   endif( NOT HOST )

endif( USE_BIWAK )

if( USE_CAMPO AND USE_BIWAK )
   set(
      libfosh_SOURCES
         ${libfosh_SOURCES}
         src/commands/hwdata.cpp
   )
   set( 
      libfosh_HEADERS
         ${libfosh_HEADERS}
         include/fosh/commands/hwdata.h
   )
endif( USE_CAMPO AND USE_BIWAK )


if( USE_BIWAK )
   
   set(
      libfosh_HEADERS
         ${libfosh_HEADERS}
         include/fosh/commands/biwak/date.hpp
         include/fosh/commands/biwak/time.hpp
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
)

if( USE_BIWAK )
   target_link_libraries(
      ${PROJECT_NAME}
      biwak
   )
endif( USE_BIWAK )

target_include_directories(
   ${PROJECT_NAME} 
   INTERFACE
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
   PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/include"
)


#------------------------------------------------------------------------------
