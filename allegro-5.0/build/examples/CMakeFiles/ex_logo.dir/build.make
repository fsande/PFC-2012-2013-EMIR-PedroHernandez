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

# Include any dependencies generated for this target.
include examples/CMakeFiles/ex_logo.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/ex_logo.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/ex_logo.dir/flags.make

examples/CMakeFiles/ex_logo.dir/ex_logo.c.o: examples/CMakeFiles/ex_logo.dir/flags.make
examples/CMakeFiles/ex_logo.dir/ex_logo.c.o: ../examples/ex_logo.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/ex_logo.dir/ex_logo.c.o"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/ex_logo.dir/ex_logo.c.o   -c /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/examples/ex_logo.c

examples/CMakeFiles/ex_logo.dir/ex_logo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ex_logo.dir/ex_logo.c.i"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/examples/ex_logo.c > CMakeFiles/ex_logo.dir/ex_logo.c.i

examples/CMakeFiles/ex_logo.dir/ex_logo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ex_logo.dir/ex_logo.c.s"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/examples/ex_logo.c -o CMakeFiles/ex_logo.dir/ex_logo.c.s

examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.requires:
.PHONY : examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.requires

examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.provides: examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.requires
	$(MAKE) -f examples/CMakeFiles/ex_logo.dir/build.make examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.provides.build
.PHONY : examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.provides

examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.provides.build: examples/CMakeFiles/ex_logo.dir/ex_logo.c.o

# Object files for target ex_logo
ex_logo_OBJECTS = \
"CMakeFiles/ex_logo.dir/ex_logo.c.o"

# External object files for target ex_logo
ex_logo_EXTERNAL_OBJECTS =

examples/ex_logo: examples/CMakeFiles/ex_logo.dir/ex_logo.c.o
examples/ex_logo: lib/liballegro_font.so.5.0.7
examples/ex_logo: lib/liballegro_ttf.so.5.0.7
examples/ex_logo: lib/liballegro_image.so.5.0.7
examples/ex_logo: lib/liballegro_primitives.so.5.0.7
examples/ex_logo: lib/liballegro.so.5.0.7
examples/ex_logo: lib/liballegro_main.so.5.0.7
examples/ex_logo: lib/liballegro_dialog.so.5.0.7
examples/ex_logo: lib/liballegro_font.so.5.0.7
examples/ex_logo: /usr/lib/i386-linux-gnu/libfreetype.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libpng.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libz.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libjpeg.so
examples/ex_logo: lib/liballegro.so.5.0.7
examples/ex_logo: /usr/lib/i386-linux-gnu/libSM.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libICE.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libX11.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libXext.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libGL.so
examples/ex_logo: /usr/lib/i386-linux-gnu/libGLU.so
examples/ex_logo: examples/CMakeFiles/ex_logo.dir/build.make
examples/ex_logo: examples/CMakeFiles/ex_logo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ex_logo"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex_logo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/ex_logo.dir/build: examples/ex_logo
.PHONY : examples/CMakeFiles/ex_logo.dir/build

examples/CMakeFiles/ex_logo.dir/requires: examples/CMakeFiles/ex_logo.dir/ex_logo.c.o.requires
.PHONY : examples/CMakeFiles/ex_logo.dir/requires

examples/CMakeFiles/ex_logo.dir/clean:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/ex_logo.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/ex_logo.dir/clean

examples/CMakeFiles/ex_logo.dir/depend:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/examples /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/examples/CMakeFiles/ex_logo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/ex_logo.dir/depend

