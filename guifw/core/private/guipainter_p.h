#pragma once 
#include "guiglobal.h"
#include "../guiframewindow.h"

class GuiPainterPrivate
{

public:
	GuiPainterPrivate( GuiFrameWindow* win );
	virtual ~GuiPainterPrivate();

	void updatePainter( );

	GuiFrameWindow* frameWindow;
	Graphics* graphics;
	Bitmap* memoryBitmap;
	Rect oldClipRect;
private:
	void clearPainter();
};

