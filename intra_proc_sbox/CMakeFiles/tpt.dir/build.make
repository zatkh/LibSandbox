# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zt/LibSandbox/intra_proc_sbox

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zt/LibSandbox/intra_proc_sbox

# Include any dependencies generated for this target.
include CMakeFiles/tpt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tpt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tpt.dir/flags.make

CMakeFiles/tpt.dir/tpt.c.o: CMakeFiles/tpt.dir/flags.make
CMakeFiles/tpt.dir/tpt.c.o: tpt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/LibSandbox/intra_proc_sbox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tpt.dir/tpt.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tpt.dir/tpt.c.o   -c /home/zt/LibSandbox/intra_proc_sbox/tpt.c

CMakeFiles/tpt.dir/tpt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tpt.dir/tpt.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zt/LibSandbox/intra_proc_sbox/tpt.c > CMakeFiles/tpt.dir/tpt.c.i

CMakeFiles/tpt.dir/tpt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tpt.dir/tpt.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zt/LibSandbox/intra_proc_sbox/tpt.c -o CMakeFiles/tpt.dir/tpt.c.s

CMakeFiles/tpt.dir/tpt.c.o.requires:

.PHONY : CMakeFiles/tpt.dir/tpt.c.o.requires

CMakeFiles/tpt.dir/tpt.c.o.provides: CMakeFiles/tpt.dir/tpt.c.o.requires
	$(MAKE) -f CMakeFiles/tpt.dir/build.make CMakeFiles/tpt.dir/tpt.c.o.provides.build
.PHONY : CMakeFiles/tpt.dir/tpt.c.o.provides

CMakeFiles/tpt.dir/tpt.c.o.provides.build: CMakeFiles/tpt.dir/tpt.c.o


# Object files for target tpt
tpt_OBJECTS = \
"CMakeFiles/tpt.dir/tpt.c.o"

# External object files for target tpt
tpt_EXTERNAL_OBJECTS =

libtpt.so: CMakeFiles/tpt.dir/tpt.c.o
libtpt.so: CMakeFiles/tpt.dir/build.make
libtpt.so: CMakeFiles/tpt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zt/LibSandbox/intra_proc_sbox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libtpt.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tpt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tpt.dir/build: libtpt.so

.PHONY : CMakeFiles/tpt.dir/build

CMakeFiles/tpt.dir/requires: CMakeFiles/tpt.dir/tpt.c.o.requires

.PHONY : CMakeFiles/tpt.dir/requires

CMakeFiles/tpt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tpt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tpt.dir/clean

CMakeFiles/tpt.dir/depend:
	cd /home/zt/LibSandbox/intra_proc_sbox && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox/CMakeFiles/tpt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tpt.dir/depend
