# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build

# Utility rule file for run_tests.

# Include the progress variables for this target.
include tests/CMakeFiles/run_tests.dir/progress.make

tests/CMakeFiles/run_tests: tests/test_driver
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/tests && ./test_driver /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_bitmaps.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_bitmaps2.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_blend.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_locking.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_locking2.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_backbuffer.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_image.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_fonts.ini /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests/test_prim.ini

run_tests: tests/CMakeFiles/run_tests
run_tests: tests/CMakeFiles/run_tests.dir/build.make
.PHONY : run_tests

# Rule to build all files generated by this target.
tests/CMakeFiles/run_tests.dir/build: run_tests
.PHONY : tests/CMakeFiles/run_tests.dir/build

tests/CMakeFiles/run_tests.dir/clean:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/run_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/run_tests.dir/clean

tests/CMakeFiles/run_tests.dir/depend:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/tests /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/tests /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/tests/CMakeFiles/run_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/run_tests.dir/depend

