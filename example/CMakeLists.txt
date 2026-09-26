#------------------------------------------------------------------------------
#
# \brief        CMakeLists.txt file for fosh example
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)


project( fosh_example C CXX )


find_package( leptoGitVersion REQUIRED )


add_executable(
   ${PROJECT_NAME}
      src/main.cpp
      ${GIT_VERSION_HEADER}
)

target_compile_definitions(
   ${PROJECT_NAME}
   PRIVATE
      # Do not throw error because of wrong configuration
      CONFIG_FOSH_EXAMPLES=1
)

target_link_libraries(
   ${PROJECT_NAME}
      fosh
)


#------------------------------------------------------------------------------
