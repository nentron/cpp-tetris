# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Public\CMake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Public\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\build

# Include any dependencies generated for this target.
include CMakeFiles/KeyboardTranslater.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/KeyboardTranslater.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/KeyboardTranslater.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KeyboardTranslater.dir/flags.make

CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj: CMakeFiles/KeyboardTranslater.dir/flags.make
CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj: C:/Users/Sengo/Dev/cpp-super-tetris/KeyboardTranslater/keyboard_translater.cpp
CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj: CMakeFiles/KeyboardTranslater.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj"
	C:\Users\Sengo\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj -MF CMakeFiles\KeyboardTranslater.dir\keyboard_translater.cpp.obj.d -o CMakeFiles\KeyboardTranslater.dir\keyboard_translater.cpp.obj -c C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\keyboard_translater.cpp

CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.i"
	C:\Users\Sengo\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\keyboard_translater.cpp > CMakeFiles\KeyboardTranslater.dir\keyboard_translater.cpp.i

CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.s"
	C:\Users\Sengo\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\keyboard_translater.cpp -o CMakeFiles\KeyboardTranslater.dir\keyboard_translater.cpp.s

# Object files for target KeyboardTranslater
KeyboardTranslater_OBJECTS = \
"CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj"

# External object files for target KeyboardTranslater
KeyboardTranslater_EXTERNAL_OBJECTS =

libKeyboardTranslater.a: CMakeFiles/KeyboardTranslater.dir/keyboard_translater.cpp.obj
libKeyboardTranslater.a: CMakeFiles/KeyboardTranslater.dir/build.make
libKeyboardTranslater.a: CMakeFiles/KeyboardTranslater.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libKeyboardTranslater.a"
	$(CMAKE_COMMAND) -P CMakeFiles\KeyboardTranslater.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\KeyboardTranslater.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KeyboardTranslater.dir/build: libKeyboardTranslater.a
.PHONY : CMakeFiles/KeyboardTranslater.dir/build

CMakeFiles/KeyboardTranslater.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\KeyboardTranslater.dir\cmake_clean.cmake
.PHONY : CMakeFiles/KeyboardTranslater.dir/clean

CMakeFiles/KeyboardTranslater.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\build C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\build C:\Users\Sengo\Dev\cpp-super-tetris\KeyboardTranslater\build\CMakeFiles\KeyboardTranslater.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/KeyboardTranslater.dir/depend
