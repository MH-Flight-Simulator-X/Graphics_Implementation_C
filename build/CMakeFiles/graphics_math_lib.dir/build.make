# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/morten/dev/Graphics_Implementation_C

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/morten/dev/Graphics_Implementation_C/build

# Include any dependencies generated for this target.
include CMakeFiles/graphics_math_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/graphics_math_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/graphics_math_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graphics_math_lib.dir/flags.make

CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o: CMakeFiles/graphics_math_lib.dir/flags.make
CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o: /home/morten/dev/Graphics_Implementation_C/lib/graphics_math/graphics_math.c
CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o: CMakeFiles/graphics_math_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/morten/dev/Graphics_Implementation_C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o -MF CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o.d -o CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o -c /home/morten/dev/Graphics_Implementation_C/lib/graphics_math/graphics_math.c

CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/morten/dev/Graphics_Implementation_C/lib/graphics_math/graphics_math.c > CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.i

CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/morten/dev/Graphics_Implementation_C/lib/graphics_math/graphics_math.c -o CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.s

# Object files for target graphics_math_lib
graphics_math_lib_OBJECTS = \
"CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o"

# External object files for target graphics_math_lib
graphics_math_lib_EXTERNAL_OBJECTS =

libgraphics_math_lib.a: CMakeFiles/graphics_math_lib.dir/lib/graphics_math/graphics_math.c.o
libgraphics_math_lib.a: CMakeFiles/graphics_math_lib.dir/build.make
libgraphics_math_lib.a: CMakeFiles/graphics_math_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/morten/dev/Graphics_Implementation_C/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libgraphics_math_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/graphics_math_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graphics_math_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graphics_math_lib.dir/build: libgraphics_math_lib.a
.PHONY : CMakeFiles/graphics_math_lib.dir/build

CMakeFiles/graphics_math_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graphics_math_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graphics_math_lib.dir/clean

CMakeFiles/graphics_math_lib.dir/depend:
	cd /home/morten/dev/Graphics_Implementation_C/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/morten/dev/Graphics_Implementation_C /home/morten/dev/Graphics_Implementation_C /home/morten/dev/Graphics_Implementation_C/build /home/morten/dev/Graphics_Implementation_C/build /home/morten/dev/Graphics_Implementation_C/build/CMakeFiles/graphics_math_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graphics_math_lib.dir/depend

