#pragma once 
#include "guiglobal.h"
#include "guifw/guiframewindow.h"
#include "guifw/guiwidget.h"

class GuiWidgetPrivate
{
public:
	GuiWidgetPrivate();
	virtual ~GuiWidgetPrivate();

	GuiWidget::DragWidgetFlag dragWidgetFlag;
	GuiFrameWindow* frameWindow;
	bool bVisible;
	bool bEnableDrag;
	Color backgroundColor;
	Size minimizeSize;
	Size maximizeSize;
	Rect geometry;
	GuiWidget::LayoutType layoutType;
	GuiWidget::ClipFlag clipFlag;
	std::wstring xmlPath;
};