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
CMAKE_COMMAND = /home/zt/.local/lib/python2.7/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/zt/.local/lib/python2.7/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zt/Documents/git/LibSandbox/API

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zt/Documents/git/LibSandbox/API

# Include any dependencies generated for this target.
include CMakeFiles/kernel_api.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kernel_api.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kernel_api.dir/flags.make

CMakeFiles/kernel_api.dir/kernel_api.c.o: CMakeFiles/kernel_api.dir/flags.make
CMakeFiles/kernel_api.dir/kernel_api.c.o: kernel_api.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/Documents/git/LibSandbox/API/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/kernel_api.dir/kernel_api.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/kernel_api.dir/kernel_api.c.o -c /home/zt/Documents/git/LibSandbox/API/kernel_api.c

CMakeFiles/kernel_api.dir/kernel_api.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kernel_api.dir/kernel_api.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zt/Documents/git/LibSandbox/API/kernel_api.c > CMakeFiles/kernel_api.dir/kernel_api.c.i

CMakeFiles/kernel_api.dir/kernel_api.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kernel_api.dir/kernel_api.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zt/Documents/git/LibSandbox/API/kernel_api.c -o CMakeFiles/kernel_api.dir/kernel_api.c.s

# Object files for target kernel_api
kernel_api_OBJECTS = \
"CMakeFiles/kernel_api.dir/kernel_api.c.o"

# External object files for target kernel_api
kernel_api_EXTERNAL_OBJECTS =

libkernel_api.so: CMakeFiles/kernel_api.dir/kernel_api.c.o
libkernel_api.so: CMakeFiles/kernel_api.dir/build.make
libkernel_api.so: CMakeFiles/kernel_api.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zt/Documents/git/LibSandbox/API/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libkernel_api.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kernel_api.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kernel_api.dir/build: libkernel_api.so

.PHONY : CMakeFiles/kernel_api.dir/build

CMakeFiles/kernel_api.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kernel_api.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kernel_api.dir/clean

CMakeFiles/kernel_api.dir/depend:
	cd /home/zt/Documents/git/LibSandbox/API && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zt/Documents/git/LibSandbox/API /home/zt/Documents/git/LibSandbox/API /home/zt/Documents/git/LibSandbox/API /home/zt/Documents/git/LibSandbox/API /home/zt/Documents/git/LibSandbox/API/CMakeFiles/kernel_api.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kernel_api.dir/depend
