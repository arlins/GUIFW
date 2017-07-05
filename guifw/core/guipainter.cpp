#include "guiglobal.h"
#include "guipainter.h"
#include "private/guipainter_p.h"

GuiPainter::GuiPainter( GuiFrameWindow* frameWindow )
: d_ptr( new GuiPainterPrivate( frameWindow ) )
{
	
}

GuiPainter::~GuiPainter()
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiPainter::drawText( const std::wstring& text, const Font* font, const PointF& origin,const Brush* brush )
{
	if ( d_ptr->graphics == NULL )
	{
		return;
	}

	d_ptr->graphics->DrawString( text.c_str(), text.length(), font, origin, brush ); 
}

void GuiPainter::drawImage( const std::wstring& imagePath, const Rect& rc )
{
	if ( d_ptr->graphics == NULL )
	{
		return;
	}

	Image image( imagePath.c_str() );
	d_ptr->graphics->DrawImage( &image , rc ); 
}

void GuiPainter::drawRect( const Pen* pen, const Rect& rc )
{
	if ( d_ptr->graphics == NULL )
	{
		return;
	}

	d_ptr->graphics->DrawRectangle( pen, rc );
}

void GuiPainter::drawLine( const Pen* pen, const Point& pt1, const Point& pt2 )
{
	if ( d_ptr->graphics == NULL )
	{
		return;
	}

	d_ptr->graphics->DrawLine( pen, pt1, pt2 );
}

void GuiPainter::fillRect( const Brush* pen, const Rect& rc )
{
	if ( d_ptr->graphics == NULL )
	{
		return;
	}

	d_ptr->graphics->FillRectangle( pen, rc );
}

void GuiPainter::drawNinePiecesImage( const Rect& rcDraw, const std::wstring& imagePath, const Rect& rcRes1, const Rect& rcRes2 )
{
	if ( d_ptr->graphics == NULL )
	{
		return;
	}

	Image pImage( imagePath.c_str() );
	Rect rcf1(rcDraw.GetLeft(), rcDraw.GetTop(), rcRes1.Width, rcRes2.Height);   //左上
	Rect rcf2(rcDraw.GetLeft()+rcRes1.Width, rcDraw.GetTop(), rcDraw.Width-rcRes1.Width-rcRes2.Width, rcRes1.Height);   //上中
	Rect rcf3(rcDraw.Width-rcRes2.Width+rcDraw.GetLeft(), rcDraw.GetTop(), rcRes2.Width, rcRes1.Height);   // 右上
	Rect rcf4(rcDraw.GetLeft(), rcDraw.GetTop()+rcRes1.Height, rcRes1.Width, rcDraw.Height-rcRes1.Height-rcRes2.Height);   //左中
	Rect rcf5(rcDraw.GetLeft()+rcRes1.Width, rcDraw.GetTop()+rcRes1.Height, rcDraw.Width-rcRes1.Width-rcRes2.Width, rcDraw.Height-rcRes1.Height-rcRes2.Height);  //正中
	Rect rcf6(rcDraw.Width-rcRes2.Width+rcDraw.GetLeft(), rcDraw.GetTop()+rcRes1.Height, rcRes2.Width, rcDraw.Height-rcRes1.Height-rcRes2.Height);   //右中
	Rect rcf7(rcDraw.GetLeft(), rcDraw.Height-rcRes2.Height+rcDraw.GetTop(), rcRes1.Width, rcRes2.Height);      //左下
	Rect rcf8(rcDraw.GetLeft()+rcRes1.Width, rcDraw.Height-rcRes2.Height+rcDraw.GetTop(), rcDraw.Width-rcRes1.Width-rcRes2.Width, rcRes2.Height);  //下中
	Rect rcf9(rcDraw.Width-rcRes2.Width+rcDraw.GetLeft(), rcDraw.Height-rcRes2.Height+rcDraw.GetTop(), rcRes2.Width, rcRes2.Height);  //右下 

	Rect resRc1( rcRes1.GetLeft(), rcRes1.GetTop(), rcRes1.Width, rcRes1.Height );
	Rect resRc2( rcRes1.Width , rcRes1.GetTop(), pImage.GetWidth() - rcRes1.Width - rcRes2.Width, rcRes1.Height );
	Rect resRc3( pImage.GetWidth() - rcRes2.Width , rcRes1.GetTop(), rcRes2.Width, rcRes1.Height );
	Rect resRc4( rcRes1.GetLeft(), rcRes1.Height, rcRes1.Width, pImage.GetHeight() - rcRes1.Height - rcRes2.Height );
	Rect resRc5( rcRes1.Width, rcRes1.Height, pImage.GetWidth() - rcRes1.Width - rcRes2.Width, pImage.GetHeight() - rcRes1.Height - rcRes2.Height );
	Rect resRc6( pImage.GetWidth() - rcRes2.Width, rcRes1.Height, rcRes2.Width, pImage.GetHeight() - rcRes1.Height - rcRes2.Height );
	Rect resRc7( rcRes1.GetLeft(), pImage.GetHeight() - rcRes2.Height, rcRes1.Width, rcRes2.Height );
	Rect resRc8( rcRes1.Width, pImage.GetHeight() - rcRes2.Height, pImage.GetWidth() - rcRes1.Width - rcRes2.Width, rcRes2.Height );
	Rect resRc9( pImage.GetWidth() - rcRes2.Width, pImage.GetHeight() - rcRes2.Height, rcRes2.Width, rcRes2.Height );

	d_ptr->graphics->DrawImage(&pImage, rcf1, resRc1.GetLeft(), resRc1.GetTop(), resRc1.Width, resRc1.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf2, resRc2.GetLeft(), resRc2.GetTop(), resRc2.Width, resRc2.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf3, resRc3.GetLeft(), resRc3.GetTop(), resRc3.Width, resRc3.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf4, resRc4.GetLeft(), resRc4.GetTop(), resRc4.Width, resRc4.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf5, resRc5.GetLeft(), resRc5.GetTop(), resRc5.Width, resRc5.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf6, resRc6.GetLeft(), resRc6.GetTop(), resRc6.Width, resRc6.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf7, resRc7.GetLeft(), resRc7.GetTop(), resRc7.Width, resRc7.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf8, resRc8.GetLeft(), resRc8.GetTop(), resRc8.Width, resRc8.Height, UnitPixel);    
	d_ptr->graphics->DrawImage(&pImage, rcf9, resRc9.GetLeft(), resRc9.GetTop(), resRc9.Width, resRc9.Height, UnitPixel);    
}

void GuiPainter::updatePainter()
{
	d_ptr->updatePainter();
}

Graphics* GuiPainter::graphics()
{
	return d_ptr->graphics;
}

Bitmap* GuiPainter::memoryBitmap()
{
	return d_ptr->memoryBitmap;
}

void GuiPainter::setClipRect( const Rect& rc, CombineMode op )
{
	if ( graphics() == NULL )
	{
		return;
	}

	Gdiplus::Status result = graphics()->SetClip( rc, op );
	for ( int i = rc.GetLeft(); i < rc.GetRight() ; i++ )
	{
		for ( int j = rc.GetTop(); j < rc.GetBottom() ; j++ )
		{
			//d_ptr->memoryBitmap->SetPixel( i, j, Color(0,0,0,0) );
		}
	}
}

void GuiPainter::save()
{
	if ( graphics() == NULL )
	{
		return;
	}

	graphics()->GetClipBounds( &d_ptr->oldClipRect );
}

void GuiPainter::restore()
{
	if ( graphics() == NULL )
	{
		return;
	}
	
	Gdiplus::Status result = graphics()->SetClip( d_ptr->oldClipRect, CombineModeReplace );
}	
