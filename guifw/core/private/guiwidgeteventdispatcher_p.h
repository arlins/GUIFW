#pragma once
#include "guiglobal.h"
#include "guifw/guiframewindow.h"

class GuiWidgetEventDispatcherPrivate
{
public:
	GuiWidgetEventDispatcherPrivate()
		: frameWindow( NULL )
		, oldClickWidget( NULL )
		, oldHoverWidget( NULL )
	{

	}
	~GuiWidgetEventDispatcherPrivate()
	{

	}

	GuiFrameWindow* frameWindow;
	GuiWidget* oldClickWidget;
	GuiWidget* oldHoverWidget;
};
