/** Copyright 2011 Thorsten Wißmann. All rights reserved.
 *
 * This software is licensed under the "Simplified BSD License".
 * See LICENSE for details */

#ifndef __HERBSTLUFT_GLOBALS_H_
#define __HERBSTLUFT_GLOBALS_H_

#include <stdbool.h>
#include <X11/Xlib.h>

#define HERBSTLUFT_VERSION "0.1-GIT, build on "__DATE__
#define HERBSTLUFT_AUTOSTART "herbstluftrc"

#define HERBST_FRAME_CLASS "_HERBST_FRAME"
#define WINDOW_MIN_HEIGHT 32
#define WINDOW_MIN_WIDTH 32

#define HERBST_MAX_TREE_HEIGHT 3

// connection to x-server
Display*    g_display;
int         g_screen;
Window      g_root;
// some settings/info
bool        g_aboutToQuit;


#endif



