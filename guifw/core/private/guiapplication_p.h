#pragma once 
#include "guiglobal.h"
#include "guifw/guiapplication.h"

class GuiApplicationPrivate
{

public:
	GuiApplicationPrivate( );
	~GuiApplicationPrivate();

public:
	EventFilterFuncType eventFilterFunc;
	std::wstring exePath;
	ULONG_PTR gdiplusToken;
	bool bQuitOnLastWindowClosed;
	std::vector<GuiFrameWindow*> frameWindowList;

private:
	void _initExePath();
	bool _registerWindow();
};