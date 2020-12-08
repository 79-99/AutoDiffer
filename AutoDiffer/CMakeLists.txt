CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
PROJECT(AutoDiffer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# force GNU linker to include all shared libraries
if(NOT APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
else()
  set(CMAKE_MACOSX_RPATH ON)
endif()

# Enable coverage profiling
OPTION(COVERAGE "Enable Code Coverage Settings" OFF)
if(COVERAGE)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-g -O0 --coverage -std=c++11 -fprofile-arcs -ftest-coverage --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
    # set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
  endif()
endif()

# Enable coverage profiling
OPTION(THREAD "Enable multithreading" OFF)
if(THREAD)
   find_package(OpenMP REQUIRED)
   if(OPENMP_FOUND)
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -Xpreprocessor")
   endif()
endif()

# ======================== #
# location of header files
# ======================== #
include_directories(include)

# ========================================================= #
# location of directory to search for next "CmakeLists.txt"
# ========================================================= #
add_subdirectory(core)
