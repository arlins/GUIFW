#pragma once 
#include "guiframewindow.h"

class GuiPainterPrivate;

class GUIFW_DECL_EXPORT GuiPainter
{

public:
	GuiPainter( GuiFrameWindow* frameWindow );
	virtual ~GuiPainter();
	
	Graphics* graphics();
	Bitmap* memoryBitmap();

	void save();
	void restore();
	void setClipRect( const Rect& rc, CombineMode op );
	void drawText( const std::wstring& text, const Font* font, const PointF& origin,const Brush* brush );
	void drawImage( const std::wstring& imagePath, const Rect& rc );
	void drawRect( const Pen* pen, const Rect& rc );
	void drawLine( const Pen* pen, const Point& pt1, const Point& pt2 );
	void fillRect( const Brush* pen, const Rect& rc );
	void drawNinePiecesImage( const Rect& rcDraw, const std::wstring& imagePath, const Rect& rcRes1, const Rect& rcRes2 	) ;

protected:
	friend class GuiFrameWindow;
	void updatePainter();
	
private:
	GuiPainterPrivate* d_ptr;
};

