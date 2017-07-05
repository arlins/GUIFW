#pragma once 
#include "guiglobal.h"
#include "guifw/guiwidget.h"
#include "../guiwidgeteventdispatcher.h"
#include "../guiframewindow.h"
#include "../guipainter.h"

class GuiFrameWindowPrivate
{
public:
	GuiFrameWindowPrivate( GuiFrameWindow* frameWindow );
	~GuiFrameWindowPrivate();

	HWND realWnd;
	GuiWidget* rootWidget;
	Rect dirtyRect;
	BLENDFUNCTION blend;
	std::wstring backgroundImage;
	std::wstring windowTitle;
	std::wstring windowIconPath;
	bool bMouseTracking;
	bool bMouseEntered;
	bool bTransparentBackground;
	bool bUpdateLayer;
	GuiWidgetEventDispatcher* wigetEventDispatcher;
	GuiPainter* painter;
	bool bIgnoreSkinChange;
	Size maximizeSize;
	Size minimizeSize;
};
