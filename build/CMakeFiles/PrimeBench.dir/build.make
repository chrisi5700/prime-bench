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
include CMakeFiles/PrimeBench.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PrimeBench.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PrimeBench.dir/flags.make

CMakeFiles/PrimeBench.dir/main.cpp.o: CMakeFiles/PrimeBench.dir/flags.make
CMakeFiles/PrimeBench.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chris/Documents/cpp/PrimesBench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PrimeBench.dir/main.cpp.o"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PrimeBench.dir/main.cpp.o -c /home/chris/Documents/cpp/PrimesBench/main.cpp

CMakeFiles/PrimeBench.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PrimeBench.dir/main.cpp.i"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chris/Documents/cpp/PrimesBench/main.cpp > CMakeFiles/PrimeBench.dir/main.cpp.i

CMakeFiles/PrimeBench.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PrimeBench.dir/main.cpp.s"
	/bin/x86_64-linux-gnu-g++-11 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chris/Documents/cpp/PrimesBench/main.cpp -o CMakeFiles/PrimeBench.dir/main.cpp.s

# Object files for target PrimeBench
PrimeBench_OBJECTS = \
"CMakeFiles/PrimeBench.dir/main.cpp.o"

# External object files for target PrimeBench
PrimeBench_EXTERNAL_OBJECTS =

PrimeBench: CMakeFiles/PrimeBench.dir/main.cpp.o
PrimeBench: CMakeFiles/PrimeBench.dir/build.make
PrimeBench: /usr/local/lib/libbenchmark.a
PrimeBench: CMakeFiles/PrimeBench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chris/Documents/cpp/PrimesBench/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PrimeBench"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PrimeBench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PrimeBench.dir/build: PrimeBench

.PHONY : CMakeFiles/PrimeBench.dir/build

CMakeFiles/PrimeBench.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PrimeBench.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PrimeBench.dir/clean

CMakeFiles/PrimeBench.dir/depend:
	cd /home/chris/Documents/cpp/PrimesBench/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chris/Documents/cpp/PrimesBench /home/chris/Documents/cpp/PrimesBench /home/chris/Documents/cpp/PrimesBench/build /home/chris/Documents/cpp/PrimesBench/build /home/chris/Documents/cpp/PrimesBench/build/CMakeFiles/PrimeBench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PrimeBench.dir/depend
