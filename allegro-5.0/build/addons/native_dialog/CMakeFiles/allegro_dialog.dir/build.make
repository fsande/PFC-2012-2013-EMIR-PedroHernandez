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
include addons/native_dialog/CMakeFiles/allegro_dialog.dir/depend.make

# Include the progress variables for this target.
include addons/native_dialog/CMakeFiles/allegro_dialog.dir/progress.make

# Include the compile flags for this target's objects.
include addons/native_dialog/CMakeFiles/allegro_dialog.dir/flags.make

addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o: addons/native_dialog/CMakeFiles/allegro_dialog.dir/flags.make
addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o: ../addons/native_dialog/dialog.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD -o CMakeFiles/allegro_dialog.dir/dialog.c.o   -c /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/dialog.c

addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/allegro_dialog.dir/dialog.c.i"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD -E /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/dialog.c > CMakeFiles/allegro_dialog.dir/dialog.c.i

addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/allegro_dialog.dir/dialog.c.s"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD -S /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/dialog.c -o CMakeFiles/allegro_dialog.dir/dialog.c.s

addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.requires:
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.requires

addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.provides: addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.requires
	$(MAKE) -f addons/native_dialog/CMakeFiles/allegro_dialog.dir/build.make addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.provides.build
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.provides

addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.provides.build: addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o

addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o: addons/native_dialog/CMakeFiles/allegro_dialog.dir/flags.make
addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o: ../addons/native_dialog/textlog.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD -o CMakeFiles/allegro_dialog.dir/textlog.c.o   -c /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/textlog.c

addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/allegro_dialog.dir/textlog.c.i"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD -E /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/textlog.c > CMakeFiles/allegro_dialog.dir/textlog.c.i

addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/allegro_dialog.dir/textlog.c.s"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD -S /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/textlog.c -o CMakeFiles/allegro_dialog.dir/textlog.c.s

addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.requires:
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.requires

addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.provides: addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.requires
	$(MAKE) -f addons/native_dialog/CMakeFiles/allegro_dialog.dir/build.make addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.provides.build
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.provides

addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.provides.build: addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o

addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o: addons/native_dialog/CMakeFiles/allegro_dialog.dir/flags.make
addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o: ../addons/native_dialog/gtk_dialog.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD  -pthread -I/usr/include/gtk-2.0 -I/usr/lib/i386-linux-gnu/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -Wno-strict-prototypes -o CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o   -c /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/gtk_dialog.c

addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/allegro_dialog.dir/gtk_dialog.c.i"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD  -pthread -I/usr/include/gtk-2.0 -I/usr/lib/i386-linux-gnu/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -Wno-strict-prototypes -E /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/gtk_dialog.c > CMakeFiles/allegro_dialog.dir/gtk_dialog.c.i

addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/allegro_dialog.dir/gtk_dialog.c.s"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -DALLEGRO_NATIVE_DIALOG_SRC  -DALLEGRO_LIB_BUILD  -pthread -I/usr/include/gtk-2.0 -I/usr/lib/i386-linux-gnu/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -Wno-strict-prototypes -S /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog/gtk_dialog.c -o CMakeFiles/allegro_dialog.dir/gtk_dialog.c.s

addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.requires:
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.requires

addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.provides: addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.requires
	$(MAKE) -f addons/native_dialog/CMakeFiles/allegro_dialog.dir/build.make addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.provides.build
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.provides

addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.provides.build: addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o

# Object files for target allegro_dialog
allegro_dialog_OBJECTS = \
"CMakeFiles/allegro_dialog.dir/dialog.c.o" \
"CMakeFiles/allegro_dialog.dir/textlog.c.o" \
"CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o"

# External object files for target allegro_dialog
allegro_dialog_EXTERNAL_OBJECTS =

lib/liballegro_dialog.so.5.0.7: addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o
lib/liballegro_dialog.so.5.0.7: addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o
lib/liballegro_dialog.so.5.0.7: addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o
lib/liballegro_dialog.so.5.0.7: lib/liballegro.so.5.0.7
lib/liballegro_dialog.so.5.0.7: /usr/lib/i386-linux-gnu/libSM.so
lib/liballegro_dialog.so.5.0.7: /usr/lib/i386-linux-gnu/libICE.so
lib/liballegro_dialog.so.5.0.7: /usr/lib/i386-linux-gnu/libX11.so
lib/liballegro_dialog.so.5.0.7: /usr/lib/i386-linux-gnu/libXext.so
lib/liballegro_dialog.so.5.0.7: /usr/lib/i386-linux-gnu/libGL.so
lib/liballegro_dialog.so.5.0.7: /usr/lib/i386-linux-gnu/libGLU.so
lib/liballegro_dialog.so.5.0.7: addons/native_dialog/CMakeFiles/allegro_dialog.dir/build.make
lib/liballegro_dialog.so.5.0.7: addons/native_dialog/CMakeFiles/allegro_dialog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library ../../lib/liballegro_dialog.so"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/allegro_dialog.dir/link.txt --verbose=$(VERBOSE)
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/liballegro_dialog.so.5.0.7 ../../lib/liballegro_dialog.so.5.0 ../../lib/liballegro_dialog.so

lib/liballegro_dialog.so.5.0: lib/liballegro_dialog.so.5.0.7

lib/liballegro_dialog.so: lib/liballegro_dialog.so.5.0.7

# Rule to build all files generated by this target.
addons/native_dialog/CMakeFiles/allegro_dialog.dir/build: lib/liballegro_dialog.so
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/build

addons/native_dialog/CMakeFiles/allegro_dialog.dir/requires: addons/native_dialog/CMakeFiles/allegro_dialog.dir/dialog.c.o.requires
addons/native_dialog/CMakeFiles/allegro_dialog.dir/requires: addons/native_dialog/CMakeFiles/allegro_dialog.dir/textlog.c.o.requires
addons/native_dialog/CMakeFiles/allegro_dialog.dir/requires: addons/native_dialog/CMakeFiles/allegro_dialog.dir/gtk_dialog.c.o.requires
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/requires

addons/native_dialog/CMakeFiles/allegro_dialog.dir/clean:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog && $(CMAKE_COMMAND) -P CMakeFiles/allegro_dialog.dir/cmake_clean.cmake
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/clean

addons/native_dialog/CMakeFiles/allegro_dialog.dir/depend:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/addons/native_dialog /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/addons/native_dialog/CMakeFiles/allegro_dialog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : addons/native_dialog/CMakeFiles/allegro_dialog.dir/depend

