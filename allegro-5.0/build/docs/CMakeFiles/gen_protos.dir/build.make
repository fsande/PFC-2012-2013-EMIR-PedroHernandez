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

# Utility rule file for gen_protos.

# Include the progress variables for this target.
include docs/CMakeFiles/gen_protos.dir/progress.make

docs/CMakeFiles/gen_protos: docs/protos

docs/protos: docs/make_protos
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating protos"
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 && /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/make_protos src/dtor.c src/system.c src/opengl/ogl_bitmap.c src/opengl/extensions.c src/opengl/ogl_draw.c src/opengl/ogl_display.c src/file_stdio.c src/misc/list.c src/misc/bstrlib.c src/misc/aatree.c src/misc/vector.c src/bitmap_io.c src/allegro.c src/inline.c src/file_slice.c src/gp2xwiz/wiz_joystick.c src/gp2xwiz/wiz_display_fb.c src/gp2xwiz/wiz_system.c src/gp2xwiz/wiz_display_opengl.c src/keybdnu.c src/config.c src/threads.c src/transformations.c src/utf8.c src/file.c src/convert.c src/joynu.c src/display.c src/path.c src/evtsrc.c src/tls.c src/timernu.c src/fshook_stdio.c src/memblit.c src/iphone/iphone_main.m src/iphone/iphone_joystick.m src/iphone/iphone_mouse.m src/iphone/allegroAppDelegate.m src/iphone/iphone_display.c src/iphone/iphone_keyboard.c src/iphone/EAGLView.h src/iphone/iphone_system.c src/iphone/EAGLView.m src/iphone/allegroAppDelegate.h src/iphone/iphone_path.m src/tri_soft.c src/memdraw.c src/scanline_drawers.c src/fshook.c src/macosx/hidjoy.m src/macosx/osxgl.m src/macosx/hidman.m src/macosx/keybd.m src/macosx/system.m src/macosx/hidjoy-10.4.m src/macosx/osx_app_delegate.m src/macosx/osxgl.h src/macosx/qzmouse.m src/x/xcursor.c src/x/xkeyboard.c src/x/xglx_config.c src/x/xmousenu.c src/x/xsystem.c src/x/xrandr.c src/x/xfullscreen.c src/x/xdisplay.c src/pixels.c src/linux/lstddrv.c src/linux/lmsems.c src/linux/vtswitch.c src/linux/lmsedrv.c src/linux/lmseps2.c src/linux/ljoynu.c src/linux/lkeybdnu.c src/linux/lmemory.c src/linux/lmouse.c src/linux/lconsole.c src/linux/lmseev.c src/linux/lsystem.c src/linux/lgfxdrv.c src/linux/lmsegpmd.c src/linux/lasyncio.c src/unix/udrvlist.c src/unix/ujoydrv.c src/unix/upath.c src/unix/umodules.c src/unix/uxthread.c src/unix/ugfxdrv.c src/unix/umouse.c src/unix/ufdwatch.c src/unix/utime.c src/unix/ukeybd.c src/win/wkeyboard.c src/win/wmcursor.c src/win/wmouse.c src/win/wgl.h src/win/d3d.h src/win/wsystem.c src/win/wgl_disp.c src/win/wthread.c src/win/wjoydxnu.c src/win/wjoydrv.c src/win/wtime.c src/win/wxthread.c src/win/wwindow.c src/display_settings.c src/bitmap.c src/blenders.c src/optimized.c src/mousenu.c src/libc.c src/events.c src/math.c src/memory.c src/win/d3d_bmp.cpp src/win/d3d_disp.cpp > /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/protos
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 && /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/make_protos include/allegro5/opengl/gl_ext.h include/allegro5/opengl/GLext/wgl_ext_alias.h include/allegro5/opengl/GLext/wgl_ext_list.h include/allegro5/opengl/GLext/gl_ext_api.h include/allegro5/opengl/GLext/glx_ext_list.h include/allegro5/opengl/GLext/gl_ext_alias.h include/allegro5/opengl/GLext/wgl_ext_defs.h include/allegro5/opengl/GLext/wgl_ext_api.h include/allegro5/opengl/GLext/gl_ext_list.h include/allegro5/opengl/GLext/glx_ext_alias.h include/allegro5/opengl/GLext/glx_ext_api.h include/allegro5/opengl/GLext/glx_ext_defs.h include/allegro5/opengl/GLext/gl_ext_defs.h include/allegro5/file.h include/allegro5/allegro_iphone.h include/allegro5/bitmap.h include/allegro5/allegro5.h include/allegro5/system.h include/allegro5/allegro_opengl.h include/allegro5/fmaths.h include/allegro5/allegro_windows.h include/allegro5/threads.h include/allegro5/base.h include/allegro5/utf8.h include/allegro5/fixed.h include/allegro5/joystick.h include/allegro5/timer.h include/allegro5/color.h include/allegro5/platform/albcc32.h include/allegro5/platform/aintlnx.h include/allegro5/platform/almsvc.h include/allegro5/platform/almngw32.h include/allegro5/platform/aintxglx.h include/allegro5/platform/aldmc.h include/allegro5/platform/aintwin.h include/allegro5/platform/astdint.h include/allegro5/platform/alwin.h include/allegro5/platform/alucfg.h include/allegro5/platform/aintunix.h include/allegro5/platform/al386vc.h include/allegro5/platform/alosx.h include/allegro5/platform/alosxcfg.h include/allegro5/platform/aliphonecfg.h include/allegro5/platform/alwiz.h include/allegro5/platform/astdbool.h include/allegro5/platform/aintuthr.h include/allegro5/platform/al386gcc.h include/allegro5/platform/aintwthr.h include/allegro5/platform/aintosx.h include/allegro5/platform/aliphone.h include/allegro5/platform/alwizcfg.h include/allegro5/platform/alwatcom.h include/allegro5/platform/aintwiz.h include/allegro5/platform/al386wat.h include/allegro5/platform/alunix.h include/allegro5/platform/aintiphone.h include/allegro5/keycodes.h include/allegro5/mouse.h include/allegro5/events.h include/allegro5/error.h include/allegro5/alinline.h include/allegro5/allegro.h include/allegro5/alcompat.h include/allegro5/transformations.h include/allegro5/debug.h include/allegro5/path.h include/allegro5/tls.h include/allegro5/bitmap_io.h include/allegro5/display.h include/allegro5/fshook.h include/allegro5/allegro_direct3d.h include/allegro5/config.h include/allegro5/internal/aintern_joystick.h include/allegro5/internal/aintern_pixels.h include/allegro5/internal/aintern_config.h include/allegro5/internal/aintern_convert.h include/allegro5/internal/aintern_tls.h include/allegro5/internal/aintern_fshook.h include/allegro5/internal/aintern_vector.h include/allegro5/internal/aintern_atomicops.h include/allegro5/internal/aintern_dtor.h include/allegro5/internal/aintern_float.h include/allegro5/internal/aintern_system.h include/allegro5/internal/aintern.h include/allegro5/internal/aintern_gp2xwiz.h include/allegro5/internal/aintern_path.h include/allegro5/internal/aintern_timer.h include/allegro5/internal/aintern_direct3d.h include/allegro5/internal/aintern_opengl.h include/allegro5/internal/aintern_display.h include/allegro5/internal/aintern_blend.h include/allegro5/internal/aintern_tri_soft.h include/allegro5/internal/aintern_bitmap.h include/allegro5/internal/aintern_keyboard.h include/allegro5/internal/bstrlib.h include/allegro5/internal/aintern_file.h include/allegro5/internal/aintern_list.h include/allegro5/internal/aintern_mouse.h include/allegro5/internal/aintern_events.h include/allegro5/internal/aintern_aatree.h include/allegro5/internal/alconfig.h include/allegro5/internal/aintern_iphone.h include/allegro5/internal/aintern_xglx.h include/allegro5/internal/aintern_thread.h include/allegro5/memory.h include/allegro5/altime.h include/allegro5/keyboard.h include/allegro5/inline/fmaths.inl >> /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/protos
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 && /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/make_protos addons/acodec/ogg.c addons/acodec/acodec.c addons/acodec/modaudio.c addons/acodec/allegro5/allegro_acodec.h addons/acodec/flac.c addons/acodec/acodec.h addons/acodec/wav.c addons/physfs/a5_physfs.c addons/physfs/allegro_physfs_intern.h addons/physfs/a5_physfs_dir.c addons/physfs/allegro5/allegro_physfs.h addons/color/color.c addons/color/allegro5/allegro_color.h addons/memfile/memfile.c addons/memfile/allegro5/allegro_memfile.h addons/primitives/prim_soft.c addons/primitives/prim_directx.c addons/primitives/prim_opengl.c addons/primitives/point_soft.c addons/primitives/line_soft.c addons/primitives/high_primitives.c addons/primitives/directx_shaders.c addons/primitives/primitives.c addons/primitives/allegro5/allegro_primitives.h addons/primitives/allegro5/internal/aintern_prim_directx.h addons/primitives/allegro5/internal/aintern_prim_opengl.h addons/primitives/allegro5/internal/aintern_prim_soft.h addons/primitives/allegro5/internal/aintern_prim.h addons/main/osx_main.m addons/main/generic_main.c addons/image/iio.h addons/image/bmp.c addons/image/iio.c addons/image/macosx.m addons/image/jpg.c addons/image/png.c addons/image/allegro5/allegro_image.h addons/image/allegro5/internal/aintern_image.h addons/image/pcx.c addons/image/iphone.m addons/image/tga.c addons/ttf/ttf.c addons/ttf/allegro5/allegro_ttf.h addons/font/text.c addons/font/font.c addons/font/fontbmp.c addons/font/allegro5/allegro_font.h addons/font/font.h addons/native_dialog/dialog.c addons/native_dialog/win_dialog.c addons/native_dialog/textlog.c addons/native_dialog/osx_dialog.m addons/native_dialog/allegro5/allegro_native_dialog.h addons/native_dialog/allegro5/internal/aintern_native_dialog.h addons/native_dialog/iphone_dialog.m addons/native_dialog/gtk_dialog.c addons/audio/kcm_voice.c addons/audio/kcm_dtor.c addons/audio/alsa.c addons/audio/kcm_instance.c addons/audio/oss.c addons/audio/kcm_sample.c addons/audio/pulseaudio.c addons/audio/kcm_mixer.c addons/audio/audio.c addons/audio/allegro5/allegro_audio.h addons/audio/allegro5/internal/aintern_audio.h addons/audio/kcm_stream.c addons/audio/aqueue.m addons/audio/openal.c addons/audio/audio_io.c addons/primitives/nshader.cpp addons/image/gdiplus.cpp addons/audio/dsound.cpp >> /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/protos

gen_protos: docs/CMakeFiles/gen_protos
gen_protos: docs/protos
gen_protos: docs/CMakeFiles/gen_protos.dir/build.make
.PHONY : gen_protos

# Rule to build all files generated by this target.
docs/CMakeFiles/gen_protos.dir/build: gen_protos
.PHONY : docs/CMakeFiles/gen_protos.dir/build

docs/CMakeFiles/gen_protos.dir/clean:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs && $(CMAKE_COMMAND) -P CMakeFiles/gen_protos.dir/cmake_clean.cmake
.PHONY : docs/CMakeFiles/gen_protos.dir/clean

docs/CMakeFiles/gen_protos.dir/depend:
	cd /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0 /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/docs /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs /home/sande/work/PROYECTOS_PFCs/Proyecto_Pedro-EMIR/allegro-5.0/build/docs/CMakeFiles/gen_protos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docs/CMakeFiles/gen_protos.dir/depend

