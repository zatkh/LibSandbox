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
include CMakeFiles/loader.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/loader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/loader.dir/flags.make

CMakeFiles/loader.dir/loader.c.o: CMakeFiles/loader.dir/flags.make
CMakeFiles/loader.dir/loader.c.o: loader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/LibSandbox/intra_proc_sbox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/loader.dir/loader.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/loader.dir/loader.c.o   -c /home/zt/LibSandbox/intra_proc_sbox/loader.c

CMakeFiles/loader.dir/loader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/loader.dir/loader.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zt/LibSandbox/intra_proc_sbox/loader.c > CMakeFiles/loader.dir/loader.c.i

CMakeFiles/loader.dir/loader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/loader.dir/loader.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zt/LibSandbox/intra_proc_sbox/loader.c -o CMakeFiles/loader.dir/loader.c.s

CMakeFiles/loader.dir/loader.c.o.requires:

.PHONY : CMakeFiles/loader.dir/loader.c.o.requires

CMakeFiles/loader.dir/loader.c.o.provides: CMakeFiles/loader.dir/loader.c.o.requires
	$(MAKE) -f CMakeFiles/loader.dir/build.make CMakeFiles/loader.dir/loader.c.o.provides.build
.PHONY : CMakeFiles/loader.dir/loader.c.o.provides

CMakeFiles/loader.dir/loader.c.o.provides.build: CMakeFiles/loader.dir/loader.c.o


CMakeFiles/loader.dir/main.c.o: CMakeFiles/loader.dir/flags.make
CMakeFiles/loader.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/LibSandbox/intra_proc_sbox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/loader.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/loader.dir/main.c.o   -c /home/zt/LibSandbox/intra_proc_sbox/main.c

CMakeFiles/loader.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/loader.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zt/LibSandbox/intra_proc_sbox/main.c > CMakeFiles/loader.dir/main.c.i

CMakeFiles/loader.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/loader.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zt/LibSandbox/intra_proc_sbox/main.c -o CMakeFiles/loader.dir/main.c.s

CMakeFiles/loader.dir/main.c.o.requires:

.PHONY : CMakeFiles/loader.dir/main.c.o.requires

CMakeFiles/loader.dir/main.c.o.provides: CMakeFiles/loader.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/loader.dir/build.make CMakeFiles/loader.dir/main.c.o.provides.build
.PHONY : CMakeFiles/loader.dir/main.c.o.provides

CMakeFiles/loader.dir/main.c.o.provides.build: CMakeFiles/loader.dir/main.c.o


CMakeFiles/loader.dir/list.c.o: CMakeFiles/loader.dir/flags.make
CMakeFiles/loader.dir/list.c.o: list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/LibSandbox/intra_proc_sbox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/loader.dir/list.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/loader.dir/list.c.o   -c /home/zt/LibSandbox/intra_proc_sbox/list.c

CMakeFiles/loader.dir/list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/loader.dir/list.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/zt/LibSandbox/intra_proc_sbox/list.c > CMakeFiles/loader.dir/list.c.i

CMakeFiles/loader.dir/list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/loader.dir/list.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/zt/LibSandbox/intra_proc_sbox/list.c -o CMakeFiles/loader.dir/list.c.s

CMakeFiles/loader.dir/list.c.o.requires:

.PHONY : CMakeFiles/loader.dir/list.c.o.requires

CMakeFiles/loader.dir/list.c.o.provides: CMakeFiles/loader.dir/list.c.o.requires
	$(MAKE) -f CMakeFiles/loader.dir/build.make CMakeFiles/loader.dir/list.c.o.provides.build
.PHONY : CMakeFiles/loader.dir/list.c.o.provides

CMakeFiles/loader.dir/list.c.o.provides.build: CMakeFiles/loader.dir/list.c.o


# Object files for target loader
loader_OBJECTS = \
"CMakeFiles/loader.dir/loader.c.o" \
"CMakeFiles/loader.dir/main.c.o" \
"CMakeFiles/loader.dir/list.c.o"

# External object files for target loader
loader_EXTERNAL_OBJECTS =

loader: CMakeFiles/loader.dir/loader.c.o
loader: CMakeFiles/loader.dir/main.c.o
loader: CMakeFiles/loader.dir/list.c.o
loader: CMakeFiles/loader.dir/build.make
loader: libsbox.so
loader: libtpt.so
loader: libmdom.so
loader: libkernel_api.so
loader: CMakeFiles/loader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zt/LibSandbox/intra_proc_sbox/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable loader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/loader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/loader.dir/build: loader

.PHONY : CMakeFiles/loader.dir/build

CMakeFiles/loader.dir/requires: CMakeFiles/loader.dir/loader.c.o.requires
CMakeFiles/loader.dir/requires: CMakeFiles/loader.dir/main.c.o.requires
CMakeFiles/loader.dir/requires: CMakeFiles/loader.dir/list.c.o.requires

.PHONY : CMakeFiles/loader.dir/requires

CMakeFiles/loader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/loader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/loader.dir/clean

CMakeFiles/loader.dir/depend:
	cd /home/zt/LibSandbox/intra_proc_sbox && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox /home/zt/LibSandbox/intra_proc_sbox/CMakeFiles/loader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/loader.dir/depend
