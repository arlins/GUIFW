#include "guiframewindow_p.h"
#include "..\guipainter.h"

GuiFrameWindowPrivate::GuiFrameWindowPrivate( GuiFrameWindow* frameWindow )
: realWnd( NULL )
, rootWidget( NULL )
, backgroundImage( L"" )
, bMouseTracking( true )
, bMouseEntered( false )
, bTransparentBackground( false )
, bIgnoreSkinChange( false )
, wigetEventDispatcher( new GuiWidgetEventDispatcher( frameWindow ) )
, maximizeSize( INT_MAX, INT_MAX )
, minimizeSize( 0, 0 ) 
, painter( new GuiPainter( frameWindow ) )
, bUpdateLayer( true )
{
	// init GDI
	blend.BlendOp=AC_SRC_OVER; 
	blend.BlendFlags=0; 
	blend.AlphaFormat=AC_SRC_ALPHA;
	blend.SourceConstantAlpha=255;
}

GuiFrameWindowPrivate::~GuiFrameWindowPrivate()
{
	Gui_SAFE_DELETE( wigetEventDispatcher );
	Gui_SAFE_DELETE( painter );

	if ( IsWindow( realWnd ) )
	{
		::DestroyWindow( realWnd );
		realWnd = NULL;
	}
}

