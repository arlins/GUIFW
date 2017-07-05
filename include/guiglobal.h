#pragma once

//system
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <deque>
#include <string>
#include<fstream>
#include <sstream>
#include <xstring>
#include <map>
#include <vector>
#include <iostream>
#include <assert.h>
#include <utility>
#include <wtypes.h>
#include <windef.h>
#include <windows.h>
#include <windowsx.h>

// gdi+
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#pragma warning(disable:4275)
#pragma warning(disable:4251)

//custom
#include "guifw/xsignals_helper.h"
#include "guifw/xsignals.h"
#include "guifw/sigslot.h"

#ifdef BUILD_GUIFW_DECL_EXPORT
	#define GUIFW_DECL_EXPORT __declspec(dllexport)
#else
	#define GUIFW_DECL_EXPORT __declspec(dllimport)
#endif

#define Gui_SAFE_DELETE( x ) if ( x != NULL ) { delete x; x = NULL;}

#define gui_slots protected
#define  gui_signals public