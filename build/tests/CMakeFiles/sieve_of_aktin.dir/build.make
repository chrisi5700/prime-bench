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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chris/Documents/cpp/PrimesBench

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chris/Documents/cpp/PrimesBench/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/sieve_of_aktin.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/sieve_of_aktin.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/sieve_of_aktin.dir/flags.make

tests/CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.o: tests/CMakeFiles/sieve_of_aktin.dir/flags.make
tests/CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.o: ../tests/test_soa.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chris/Documents/cpp/PrimesBench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.o"
	cd /home/chris/Documents/cpp/PrimesBench/build/tests && /bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.o -c /home/chris/Documents/cpp/PrimesBench/tests/test_soa.cpp

tests/CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.i"
	cd /home/chris/Documents/cpp/PrimesBench/build/tests && /bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chris/Documents/cpp/PrimesBench/tests/test_soa.cpp > CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.i

tests/CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.s"
	cd /home/chris/Documents/cpp/PrimesBench/build/tests && /bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chris/Documents/cpp/PrimesBench/tests/test_soa.cpp -o CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.s

# Object files for target sieve_of_aktin
sieve_of_aktin_OBJECTS = \
"CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.o"

# External object files for target sieve_of_aktin
sieve_of_aktin_EXTERNAL_OBJECTS =

tests/sieve_of_aktin: tests/CMakeFiles/sieve_of_aktin.dir/test_soa.cpp.o
tests/sieve_of_aktin: tests/CMakeFiles/sieve_of_aktin.dir/build.make
tests/sieve_of_aktin: lib/libgtest_main.a
tests/sieve_of_aktin: lib/libgtest.a
tests/sieve_of_aktin: tests/CMakeFiles/sieve_of_aktin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chris/Documents/cpp/PrimesBench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sieve_of_aktin"
	cd /home/chris/Documents/cpp/PrimesBench/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sieve_of_aktin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/sieve_of_aktin.dir/build: tests/sieve_of_aktin

.PHONY : tests/CMakeFiles/sieve_of_aktin.dir/build

tests/CMakeFiles/sieve_of_aktin.dir/clean:
	cd /home/chris/Documents/cpp/PrimesBench/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/sieve_of_aktin.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/sieve_of_aktin.dir/clean

tests/CMakeFiles/sieve_of_aktin.dir/depend:
	cd /home/chris/Documents/cpp/PrimesBench/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chris/Documents/cpp/PrimesBench /home/chris/Documents/cpp/PrimesBench/tests /home/chris/Documents/cpp/PrimesBench/build /home/chris/Documents/cpp/PrimesBench/build/tests /home/chris/Documents/cpp/PrimesBench/build/tests/CMakeFiles/sieve_of_aktin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/sieve_of_aktin.dir/depend

