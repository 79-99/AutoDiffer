# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build

# Include any dependencies generated for this target.
include core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/depend.make

# Include the progress variables for this target.
include core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/progress.make

# Include the compile flags for this target's objects.
include core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/flags.make

core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.o: core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/flags.make
core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.o: ../core/tests/test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.o"
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.o -c /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/test_main.cpp

core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.i"
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/test_main.cpp > CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.i

core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.s"
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests/test_main.cpp -o CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.s

# Object files for target ADValueTest.Unit.Test
ADValueTest_Unit_Test_OBJECTS = \
"CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.o"

# External object files for target ADValueTest.Unit.Test
ADValueTest_Unit_Test_EXTERNAL_OBJECTS =

bin/ADValueTest.Unit.Test: core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/test_main.cpp.o
bin/ADValueTest.Unit.Test: core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/build.make
bin/ADValueTest.Unit.Test: lib/libADValueTest.dylib
bin/ADValueTest.Unit.Test: lib/libADNodeTest.dylib
bin/ADValueTest.Unit.Test: lib/libAutoDiffer.dylib
bin/ADValueTest.Unit.Test: /Users/michaelneuder/Dropbox/github/cs107-FinalProject/install/3PL/googletest/lib/libgtest.a
bin/ADValueTest.Unit.Test: /Users/michaelneuder/Dropbox/github/cs107-FinalProject/install/3PL/googletest/lib/libgtest_main.a
bin/ADValueTest.Unit.Test: core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/ADValueTest.Unit.Test"
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ADValueTest.Unit.Test.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Run ADValue Unit Tests"
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests && ../../bin/ADValueTest.Unit.Test

# Rule to build all files generated by this target.
core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/build: bin/ADValueTest.Unit.Test

.PHONY : core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/build

core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/clean:
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests && $(CMAKE_COMMAND) -P CMakeFiles/ADValueTest.Unit.Test.dir/cmake_clean.cmake
.PHONY : core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/clean

core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/depend:
	cd /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/core/tests /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests /Users/michaelneuder/Dropbox/github/cs107-FinalProject/AutoDiffer/build/core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/tests/CMakeFiles/ADValueTest.Unit.Test.dir/depend

