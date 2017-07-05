#pragma once 
#include "guipainter_p.h"

GuiPainterPrivate::GuiPainterPrivate( GuiFrameWindow* win )
: frameWindow( win )
, memoryBitmap( NULL )
, graphics( NULL )
{
	
}

GuiPainterPrivate::~GuiPainterPrivate()
{
	
}

void GuiPainterPrivate::updatePainter()
{
	if ( frameWindow == NULL )
	{
		return;
	}

	clearPainter();
	
	memoryBitmap = new Bitmap( frameWindow->width(), frameWindow->height() );
	graphics = Graphics::FromImage( memoryBitmap );
	//graphics->SetInterpolationMode(InterpolationModeNearestNeighbor);
	//graphics->SetPixelOffsetMode(PixelOffsetModeHalf);
	//graphics->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed);
	//graphics->SetInterpolationMode(Gdiplus::InterpolationModeLowQuality);
}

void GuiPainterPrivate::clearPainter()
{
	Gui_SAFE_DELETE( memoryBitmap );
	Gui_SAFE_DELETE( graphics );
}
