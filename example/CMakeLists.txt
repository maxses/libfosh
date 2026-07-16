#------------------------------------------------------------------------------
#
# \brief        CMakeLists.txt file for "CANIO"
#
#------------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.11)


project( fosh_example C CXX )


find_package(ArenaFlash REQUIRED)
find_package(GitVersion REQUIRED)


add_executable(
   ${PROJECT_NAME}
      src/main.cpp
      ${GIT_VERSION_HEADER}
)

target_link_libraries(
   ${PROJECT_NAME}
      fosh
)


#------------------------------------------------------------------------------
