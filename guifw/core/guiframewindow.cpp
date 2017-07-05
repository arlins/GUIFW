#include "guiglobal.h"
#include "guievent.h"
#include "guiframewindow.h"
#include "guiwidget.h"
#include "guiapplication.h"
#include "guidefs.h"
#include "guiwidgeteventdispatcher.h"
#include "guiskinmanager.h"
#include "guipainter.h"
#include "private/guiframewindow_p.h"
#include "../utility/graphics/graphics.h"
#include "../utility/text/ustring.h"

const int KWindowCornerSize = 3;

GUI_IMPLEMENT_FRAME_DYNAMIC_CREATE_SELF( GuiFrameWindow );
GuiFrameWindow::GuiFrameWindow( GuiFrameWindow* parent )
: GuiObject( parent )
, d_ptr( new GuiFrameWindowPrivate( this ) )
{
	guiApp->addFrameWindow( this );
	_init();
}

GuiFrameWindow::~GuiFrameWindow()
{
	guiApp->removeFrameWindow( this );
	Gui_SAFE_DELETE( d_ptr );
}

void GuiFrameWindow::_init()
{
	//create window
	DWORD dwExStyle = 0;
	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	HWND parentHwnd = NULL;
	GuiFrameWindow* parentWindow = static_cast<GuiFrameWindow*>( parent() );
	if( parentWindow && parentWindow->isVaildWindow() )
	{
		dwStyle = dwStyle|WS_CHILD;
		parentHwnd = parentWindow->hwnd();
	}

	d_ptr->realWnd = ::CreateWindowEx(dwExStyle, KWinClassName, L"", dwStyle, 0, 0, 0, 0, parentHwnd, NULL, ::GetModuleHandle( NULL ), NULL );
	if ( !isVaildWindow() )
	{
		return;
	}
	
	xsignals_helper::sig_connect( skinManager()->skinAlphaValueChanged, this , &GuiFrameWindow::on_skinAlphaValueChanged );
	xsignals_helper::sig_connect( skinManager()->skinImageChanged, this , &GuiFrameWindow::on_skinImageChanged );

	::SetWindowLong( hwnd(), GWL_USERDATA, (LONG)this );
	if ( d_ptr->rootWidget == NULL )
	{
		d_ptr->rootWidget = new GuiWidget( (GuiWidget*)NULL );
		d_ptr->rootWidget->setParent( this );
		d_ptr->rootWidget->setObjectName( L"realRootWidget" );
		d_ptr->rootWidget->setGuiFrameWindow( this );
		d_ptr->rootWidget->setDragWidgetFlag( GuiWidget::DragWindow );
		d_ptr->rootWidget->setLayout( GuiWidget::HBox );
		//d_ptr->rootWidget->setDragWidgetFlag( GuiWidget::NotDragWindow );
		//d_ptr->rootWidget->setBackgroundColor( Color(50,255,0,0) );
	}
}

void GuiFrameWindow::doConstruct()
{
	rootWidget()->setGeometry( rect() );
	construct();
}

void GuiFrameWindow::construct()
{
	
}

GuiWidget* GuiFrameWindow::rootWidget()
{
	return d_ptr->rootWidget;
}

HWND GuiFrameWindow::hwnd()
{
	return d_ptr->realWnd;
}

void GuiFrameWindow::setVisible( bool bVisible )
{
	if ( !isVaildWindow() )
	{
		return;
	}

	if ( bVisible )
	{
		::ShowWindow( hwnd(), SW_SHOW );
	}
	else
	{
		::ShowWindow( hwnd(), SW_HIDE );
	}
}

bool GuiFrameWindow::isVisible()
{
	if ( !isVaildWindow() )
	{
		return false;
	}

	return ::IsWindowVisible( d_ptr->realWnd ) == TRUE;
}

void GuiFrameWindow::show()
{
	setVisible( true );
}

void GuiFrameWindow::hide()
{
	setVisible( false );
}

Rect GuiFrameWindow::geometry()
{
	if ( !isVaildWindow() )
	{
		return Rect();
	}

	Rect gRect;
	RECT rect;
	::GetWindowRect( hwnd(), &rect );
	gRect = Rect( rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top );
	return gRect;
}

void GuiFrameWindow::setGeometry( int x, int y, int cx, int cy )
{
	if ( !isVaildWindow() )
	{
		return;
	}

	::SetWindowPos( hwnd(), 0, x, y, cx, cy, SWP_NOZORDER );
}

void GuiFrameWindow::centerWindow()
{
	if ( !isVaildWindow() )
	{
		return;
	}

	RECT rcDlg = { 0 };
	::GetWindowRect( hwnd() , &rcDlg);
	RECT rcArea = { 0 };
	RECT rcCenter = { 0 };
	HWND hWndParent = ::GetParent( hwnd() );
	HWND hWndCenter = ::GetWindow(hwnd(), GW_OWNER);
	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
	if( hWndCenter == NULL ) rcCenter = rcArea; else ::GetWindowRect(hWndCenter, &rcCenter);

	int DlgWidth = rcDlg.right - rcDlg.left;
	int DlgHeight = rcDlg.bottom - rcDlg.top;

	// Find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right) / 2 - DlgWidth / 2;
	int yTop = (rcCenter.top + rcCenter.bottom) / 2 - DlgHeight / 2;

	// The dialog is outside the screen, move it inside
	if( xLeft < rcArea.left ) xLeft = rcArea.left;
	else if( xLeft + DlgWidth > rcArea.right ) xLeft = rcArea.right - DlgWidth;
	if( yTop < rcArea.top ) yTop = rcArea.top;
	else if( yTop + DlgHeight > rcArea.bottom ) yTop = rcArea.bottom - DlgHeight;
	::SetWindowPos( hwnd(), NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

int GuiFrameWindow::width()
{
	Size size;
	geometry().GetSize( &size );
	return size.Width;
}

int GuiFrameWindow::height()
{
	Size size;
	geometry().GetSize( &size );
	return size.Height;
}

bool GuiFrameWindow::isVaildWindow()
{    
	return ::IsWindow( hwnd() ) == TRUE;
}

void GuiFrameWindow::setOpacity( int op )
{
	op = max( 1, op );
	op = min( 255, op );
	d_ptr->blend.SourceConstantAlpha= op;//1~255

	update();
}

int GuiFrameWindow::opacity()
{
	return d_ptr->blend.SourceConstantAlpha;
}

void GuiFrameWindow::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"backgroundImage" )
	{
		setBackgroundImage( value );
	}
	else if ( name == L"minimizeSize" )
	{
		setMinimizeSize( value );
	}
	else if ( name == L"maximizeSize" )
	{
		setMaximizeSize( value );
	}
	else if ( name == L"fixSize" )
	{
		setFixedSize( value );
	}
	else if ( name == L"defaultSize" )
	{
		setDefaultSize( value );
	}
	else if ( name == L"windowTitle" )
	{
		setWindowTitle( value );
	}
	else if ( name == L"windowIcon" )
	{
		setWindowIcon( value );
	}
	else
	{
		GuiObject::setAttribute( name, value );
	}
}

void GuiFrameWindow::setBackgroundImage( const std::wstring& filePath )
{
	d_ptr->backgroundImage = filePath;
	update();
}

void GuiFrameWindow::update( Rect dirtyRect )
{
	if ( dirtyRect.IsEmptyArea() )
	{
		d_ptr->painter->updatePainter();
		d_ptr->dirtyRect = rect();
	}
	else
	{
		if ( d_ptr->dirtyRect.IsEmptyArea() )
		{
			d_ptr->dirtyRect = dirtyRect;
		}
		else
		{
			Rect::Union( d_ptr->dirtyRect, dirtyRect, d_ptr->dirtyRect );
		}
	}

	_postMessage( GuiPaint, 0, 0 );
}

void GuiFrameWindow::windowPaintEvent()
{
	if ( !isVaildWindow() )
	{
		return;
	}   

	//画所有的widget
	d_ptr->painter->setClipRect( d_ptr->dirtyRect, CombineModeReplace );
	if ( !d_ptr->bTransparentBackground )
	{
		drawBackground( d_ptr->painter ); 
	}

	paintEvent( d_ptr->painter );
	d_ptr->wigetEventDispatcher->paintEvent( d_ptr->painter );

	//将整张图一次性贴到DC上
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint( hwnd(), &ps);  
	HDC hMemDc = CreateCompatibleDC( hdc );  // 创建与当前DC兼容的内存DC    

	BYTE * pBits ;
	BITMAPINFOHEADER bmih;
	ZeroMemory( &bmih, sizeof( BITMAPINFOHEADER ) );
	bmih.biSize = sizeof (BITMAPINFOHEADER) ;
	bmih.biWidth = width() ;
	bmih.biHeight = height() ;
	bmih.biPlanes = 1 ;
	bmih.biBitCount = 32; 
	bmih.biCompression = BI_RGB ;
	bmih.biSizeImage = 0 ;
	bmih.biXPelsPerMeter = 0 ;
	bmih.biYPelsPerMeter = 0 ;
	bmih.biClrUsed = 0 ;
	bmih.biClrImportant = 0 ;
	HBITMAP hBmpBuffer = CreateDIBSection(NULL, (BITMAPINFO *) &bmih, 0, (VOID**)&pBits, NULL, 0) ;// 创建一块指定大小的位图 
	HGDIOBJ hPreBmp = SelectObject( hMemDc, hBmpBuffer );  // 将该位图选入到内存DC中，默认是全黑色的    

	Image* bitmap = d_ptr->painter->memoryBitmap();
	Graphics graph( hMemDc );
	graph.DrawImage( bitmap, 0, 0, 0, 0, (INT)bitmap->GetWidth(), (INT)bitmap->GetHeight(), UnitPixel );
	graph.ReleaseHDC( hMemDc );

	POINT ptWinPos={ geometry().GetLeft(), geometry().GetTop() };
	SIZE sizeWindow={ width(),height() };
	POINT ptSrc={0,0};
	DWORD dwExStyle = ::GetWindowLong( hwnd(), GWL_EXSTYLE );
	if ( (dwExStyle&0x80000) != 0x80000 )
	{
		::SetWindowLong( hwnd(),GWL_EXSTYLE,dwExStyle^0x80000 );
	}

	::UpdateLayeredWindow( hwnd(), hdc, &ptWinPos, &sizeWindow, hMemDc ,&ptSrc, 0, &d_ptr->blend, ULW_ALPHA );

	SelectObject( hMemDc, hPreBmp );  
	DeleteObject( hBmpBuffer );  
	DeleteDC( hMemDc ); 
	EndPaint( hwnd(), &ps );
	
	_setWindowCorner();
	d_ptr->dirtyRect = Rect(0,0,0,0);
}

void GuiFrameWindow::drawBackground( GuiPainter* painter )
{
	std::wstring imagePath =  guiApp->exePath() + L"/" + d_ptr->backgroundImage; 
	if ( d_ptr->backgroundImage.empty() )
	{
		SolidBrush brush( Color( 1,0,0,0 ) );
		painter->fillRect( &brush, rect() );
	}
	else
	{
		painter->drawImage( imagePath, rect() );
	}

	Pen pen( Color( 51,91,88) );	
	painter->drawLine( &pen, Point( KWindowCornerSize, 0 ), Point( width() - KWindowCornerSize, 0 ) );
	painter->drawLine( &pen, Point( 0, KWindowCornerSize ), Point( 0, height() - KWindowCornerSize ) );
	painter->drawLine( &pen, Point( width() - 1, 0), Point( width() - 1, height() - KWindowCornerSize ) );
	painter->drawLine( &pen, Point( KWindowCornerSize, height() - 1 ), Point( width() - KWindowCornerSize, height() - 1 ) );
	
	painter->drawLine( &pen, Point(0,KWindowCornerSize), Point( KWindowCornerSize, 0 ) );
	painter->drawLine( &pen, Point(width() - KWindowCornerSize - 1,0), Point( width() - 1, KWindowCornerSize ) );
	painter->drawLine( &pen, Point(width() - 1, height() - KWindowCornerSize), Point( width() - 1 - KWindowCornerSize, height() ) );
	painter->drawLine( &pen, Point(0,height() - KWindowCornerSize), Point( KWindowCornerSize, height() ) );
	

	pen.SetColor( Color(80,255,255,255) );
	painter->drawLine( &pen, Point( KWindowCornerSize, 1 ), Point( width() - KWindowCornerSize, 1 ) );
	painter->drawLine( &pen, Point( 1, KWindowCornerSize ), Point( 1, height() - KWindowCornerSize ) );
	painter->drawLine( &pen, Point( width() - 2, 0), Point( width() - 2, height() - KWindowCornerSize ) );
	painter->drawLine( &pen, Point( KWindowCornerSize, height() - 2 ), Point( width() - KWindowCornerSize, height() - 2 ) );
}

void GuiFrameWindow::windowCloseEvent( GuiEvent* msg )
{
	closeEvent( msg );
	d_ptr->wigetEventDispatcher->closeEvent( msg );
	if ( msg->bAccepted )
	{
		aboutToClose();
		delete this;
	}
}

void GuiFrameWindow::windowResizeEvent( GuiEvent* msg )
{
	_setWindowCorner();
	rootWidget()->setGeometry( rect() );
	update();

	resizeEvent( msg );
	d_ptr->wigetEventDispatcher->resizeEvent( msg );
}

void GuiFrameWindow::windowMouseMoveEvent( GuiEvent* msg )
{
	if ( !d_ptr->bMouseEntered )
	{
		mouseEnterEvent( msg );
		d_ptr->bMouseEntered = true;
	}

	mouseMoveEvent( msg );
	d_ptr->wigetEventDispatcher->mouseMoveEvent( msg );
}

void GuiFrameWindow::windowMouseLeaveEvent( GuiEvent* msg )
{
	d_ptr->bMouseEntered = false;
	mouseLeaveEvent( msg );
	d_ptr->wigetEventDispatcher->mouseLeaveEvent( msg );
}


bool GuiFrameWindow::winEvent( GuiEvent* msg )
{
	return true;
}

void GuiFrameWindow::paintEvent( GuiPainter* painter )
{

}

void GuiFrameWindow::resizeEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::closeEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::mouseWheelEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseHoverEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::mouseEnterEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::mouseLeaveEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::mouseMoveEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::mouseLButtonPressEvent( GuiEvent* msg )
{
	
}

void GuiFrameWindow::mouseLButtonReleaseEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseMButtonPressEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseMButtonReleaseEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseRButtonPressEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseRButtonReleaseEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseMButtonDoubleClickEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseLButtonDoubleClickEvent( GuiEvent* msg )
{

}

void GuiFrameWindow::mouseRButtonDoubleClickEvent( GuiEvent* msg )
{

}

GuiWidget* GuiFrameWindow::findWidgetByPoint( const Point& pt )
{
	if ( d_ptr->rootWidget == NULL )
	{
		return NULL;
	}

	GuiWidget* widget = NULL;
	GuiWidget* pWidget = d_ptr->rootWidget;

	std::deque<GuiObject*> stackNode; 
	stackNode.push_back( static_cast<GuiObject*>( d_ptr->rootWidget ) ); 
	while( !stackNode.empty() ) 
	{ 
		GuiObject *pItem=stackNode.back(); 
		GuiWidget* itemWidget = static_cast<GuiWidget*> ( pItem ); 
		stackNode.pop_back(); 
		if ( itemWidget && itemWidget->isVisible() && itemWidget->realShape().Contains( pt ) )
		{
			widget = itemWidget;
		}

		for ( std::list<GuiObject*>::reverse_iterator  it = pItem->getChildren().rbegin(); it != pItem->getChildren().rend(); it++ ) \
		{ 
			stackNode.push_back( *it );
		} 
	}

	return widget;
}

void GuiFrameWindow::close()
{
	_postMessage( WM_CLOSE, 0, 0 );
}

void GuiFrameWindow::setMouseTracking( bool bMouseTracking )
{
	d_ptr->bMouseTracking;
}

bool GuiFrameWindow::mouseTracking()
{
	return d_ptr->bMouseTracking;
}

Rect GuiFrameWindow::rect()
{
	return Rect( 0, 0, width(), height() );
}

void GuiFrameWindow::_postMessage( UINT Msg,WPARAM wParam,LPARAM lParam )
{
	if ( !isVaildWindow() )
	{
		return;
	}

	::PostMessage( hwnd(), Msg, wParam, lParam );
}

LRESULT GuiFrameWindow::windowNcHitTest( GuiEvent* msg )
{
	if ( !isVaildWindow() )
	{
		return HTCLIENT;
	}

	Point clientPt = clientPointFromEvent( msg );
	clientPt = mapFromScreen( clientPt );

	int spacing = 4;
	Rect hitRect;

	if ( !d_ptr->maximizeSize.Equals( d_ptr->minimizeSize ) )
	{
		hitRect = Rect( 0, 0, spacing, spacing );
		if ( hitRect.Contains( clientPt ) ) //左上角
		{  
			return HTTOPLEFT;  
		}

		hitRect = Rect( width() - spacing, 0, spacing, spacing );
		if ( hitRect.Contains( clientPt ) ) //右上角
		{  
			return HTTOPRIGHT;  
		}

		hitRect = Rect( 0, height() - spacing, spacing, spacing );
		if ( hitRect.Contains( clientPt ) ) //左下角
		{  
			return HTBOTTOMLEFT;  
		}

		hitRect = Rect( width() - spacing, height() - spacing, spacing, spacing );
		if ( hitRect.Contains( clientPt ) ) //右下角
		{  
			return HTBOTTOMRIGHT;  
		}

		hitRect = Rect( 0, spacing, spacing, height() - spacing );
		if ( hitRect.Contains( clientPt ) ) //左边框
		{  
			return HTLEFT;  
		}

		hitRect = Rect( width() - spacing, spacing, spacing, height() - spacing );
		if ( hitRect.Contains( clientPt ) ) //右边框
		{  
			return HTRIGHT;  
		}

		hitRect = Rect( spacing, 0, width() - spacing, spacing );
		if ( hitRect.Contains( clientPt ) ) //上边框
		{  
			return HTTOP;  
		}

		hitRect = Rect( spacing, height() - spacing, width() - spacing, spacing );
		if ( hitRect.Contains( clientPt ) ) //下边框
		{  
			return HTBOTTOM;  
		}
	}

	GuiWidget* widget = findWidgetByPoint( clientPt );
	if ( widget && widget->dragWidgetFlag() == GuiWidget::DragWindow )
	{
		return HTCAPTION;
	}

	return HTCLIENT;
}

Point GuiFrameWindow::mapFromScreen( const Point& pt )
{
	if ( !isVaildWindow() )
	{
		return Point();
	}

	POINT newPt = { pt.X, pt.Y };
	::ScreenToClient( hwnd(), &newPt );

	return Point( newPt.x, newPt.y );
}

Point GuiFrameWindow::mapToScreen( const Point& pt )
{
	if ( !isVaildWindow() )
	{
		return Point();
	}

	POINT newPt = { pt.X, pt.Y };
	::ClientToScreen( hwnd(), &newPt );

	return Point( newPt.x, newPt.y );
}

void GuiFrameWindow::windowGetMinMaxInfoEvent( GuiEvent* msg )
{
	LPMINMAXINFO lpMMI = (LPMINMAXINFO) (msg->lParam );
	RECT rectWorkArea = {0};
	if(!SystemParametersInfo(SPI_GETWORKAREA,sizeof(RECT),&rectWorkArea,0))
	{
		rectWorkArea.right = ::GetSystemMetrics(SM_CXSCREEN);
		rectWorkArea.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	}
	lpMMI->ptMaxSize.x = rectWorkArea.right - rectWorkArea.left ;  // 设置窗口最大化时的宽度
	lpMMI->ptMaxSize.y = rectWorkArea.bottom - rectWorkArea.top;  // 设置窗口最大化时的高度
	lpMMI->ptMaxPosition.x = 0; // 设置窗口最大化时x坐标
	lpMMI->ptMaxPosition.y = 0; // 设置窗口最大化时y坐标
	lpMMI->ptMinTrackSize.x = d_ptr->minimizeSize.Width; // 设置窗口最小宽度
	lpMMI->ptMinTrackSize.y = d_ptr->minimizeSize.Height; // 设置窗口最小高度
	lpMMI->ptMaxTrackSize.x = d_ptr->maximizeSize.Width; // 设置窗口最大宽度
	lpMMI->ptMaxTrackSize.y = d_ptr->maximizeSize.Height; // 设置窗口最大高度
}

void GuiFrameWindow::showMinimize()
{
	if ( !isVaildWindow() )
	{
		return;
	}

	::ShowWindow( hwnd(), SW_MINIMIZE );
}

void GuiFrameWindow::showMaximize()
{
	if ( !isVaildWindow() )
	{
		return;
	}

	::ShowWindow( hwnd(), SW_MAXIMIZE );
}

void GuiFrameWindow::showNormal()
{
	if ( !isVaildWindow() )
	{
		return;
	}

	::ShowWindow( hwnd(), SW_SHOWNORMAL );
}

void GuiFrameWindow::showRestore()
{
	if ( !isVaildWindow() )
	{
		return;
	}

	::ShowWindow( hwnd(), SW_RESTORE );
}

Point GuiFrameWindow::clientPointFromEvent( GuiEvent* ev )
{
	Point pt( GET_X_LPARAM( ev->lParam ), GET_Y_LPARAM( ev->lParam ) );
	return  pt;
}

void GuiFrameWindow::windowMouseLButtonPressEvent( GuiEvent* msg )
{
	::SetCapture( hwnd() );
	mouseLButtonPressEvent( msg );
	d_ptr->wigetEventDispatcher->mouseLButtonPressEvent( msg );
}

void GuiFrameWindow::windowMouseLButtonReleaseEvent( GuiEvent* msg )
{
	::ReleaseCapture();
	mouseLButtonReleaseEvent( msg );
	d_ptr->wigetEventDispatcher->mouseLButtonReleaseEvent( msg );
}

void GuiFrameWindow::windowMouseEnterEvent( GuiEvent* msg )
{
	mouseEnterEvent( msg );
	d_ptr->wigetEventDispatcher->mouseEnterEvent( msg );
}

void GuiFrameWindow::windowMouseWheelEvent( GuiEvent* msg )
{
	mouseWheelEvent( msg );
	d_ptr->wigetEventDispatcher->mouseWheelEvent( msg );
}

void GuiFrameWindow::windowMouseMButtonPressEvent( GuiEvent* msg )
{
	mouseMButtonPressEvent( msg );
	d_ptr->wigetEventDispatcher->mouseMButtonPressEvent( msg );
}

void GuiFrameWindow::windowMouseMButtonReleaseEvent( GuiEvent* msg )
{
	mouseMButtonReleaseEvent( msg );
	d_ptr->wigetEventDispatcher->mouseMButtonReleaseEvent( msg );
}

void GuiFrameWindow::windowMouseRButtonPressEvent( GuiEvent* msg )
{
	mouseRButtonPressEvent( msg );
	d_ptr->wigetEventDispatcher->mouseRButtonPressEvent( msg );
}

void GuiFrameWindow::windowMouseRButtonReleaseEvent( GuiEvent* msg )
{
	mouseRButtonReleaseEvent( msg );
	d_ptr->wigetEventDispatcher->mouseRButtonReleaseEvent( msg );
}

void GuiFrameWindow::windowMouseLButtonDoubleClickEvent( GuiEvent* msg )
{
	::SetCapture( hwnd() );
	mouseLButtonDoubleClickEvent( msg );
	d_ptr->wigetEventDispatcher->mouseLButtonDoubleClickEvent( msg );
}

void GuiFrameWindow::windowMouseMButtonDoubleClickEvent( GuiEvent* msg )
{
	mouseMButtonDoubleClickEvent( msg );
	d_ptr->wigetEventDispatcher->mouseMButtonDoubleClickEvent( msg );
}

void GuiFrameWindow::windowMouseRButtonDoubleClickEvent( GuiEvent* msg )
{
	mouseRButtonDoubleClickEvent( msg );
	d_ptr->wigetEventDispatcher->mouseRButtonDoubleClickEvent( msg );
}

void GuiFrameWindow::windowMouseHoverEvent( GuiEvent* msg )
{	
	mouseHoverEvent( msg );
	d_ptr->wigetEventDispatcher->mouseHoverEvent( msg );
}

void GuiFrameWindow::setTransparentBackground( bool bTransparent )
{
	d_ptr->bTransparentBackground = bTransparent;
}

void GuiFrameWindow::_setWindowCorner()
{
	HRGN hRgn;
	int nHeight;
	int nWidth;

	nHeight = height();
	nWidth = width(); // 计算宽度
	POINT point[8] = {
		{0,KWindowCornerSize}, // left-left-top
		{KWindowCornerSize,0}, // left-top-left
		{nWidth-KWindowCornerSize,0},
		{nWidth,KWindowCornerSize}, // right-top
		{nWidth,nHeight-KWindowCornerSize},// right-bottom-right
		{nWidth-KWindowCornerSize,nHeight}, // right-bottom-bottom
		{KWindowCornerSize,nHeight}, // left-bottom
		{0,nHeight-KWindowCornerSize}
	};
	hRgn = CreatePolygonRgn(point,8,WINDING);
	SetWindowRgn(hwnd(),hRgn,TRUE);
}

void GuiFrameWindow::on_skinAlphaValueChanged()
{
	if ( d_ptr->bIgnoreSkinChange )
	{
		return;
	}

	setOpacity( skinManager()->skinAlphaValue() );
}

void GuiFrameWindow::setIgnoreSkinChange( bool bIgnore )
{
	d_ptr->bIgnoreSkinChange = bIgnore;
}

bool GuiFrameWindow::ignoreSkinChange()
{
	return d_ptr->bIgnoreSkinChange;
}

void GuiFrameWindow::on_skinImageChanged()
{
	if ( d_ptr->bIgnoreSkinChange )
	{
		return;
	}

	setBackgroundImage( skinManager()->skinImagePath() );
}

void GuiFrameWindow::setMaximizeSize( const Size& size )
{
	d_ptr->maximizeSize = size;
}

Size GuiFrameWindow::maximizeSize()
{
	return d_ptr->maximizeSize;
}

void GuiFrameWindow::setMinimizeSize( const Size& size )
{
	d_ptr->minimizeSize = size;
}

Size GuiFrameWindow::minimizeSize()
{
	return d_ptr->minimizeSize;
}

void GuiFrameWindow::setMaximizeSize( const std::wstring& value )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( value, L",", containter );
	if ( containter.size() != 2 )
	{
		assert( false );
		return;
	}

	int w = Utility::text::stringToInt( containter.at(0) );
	int h = Utility::text::stringToInt( containter.at(1) );
	setMaximizeSize( Size( w, h ) );
}

void GuiFrameWindow::setMinimizeSize( const std::wstring& value )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( value, L",", containter );
	if ( containter.size() != 2 )
	{
		assert( false );
		return;
	}

	int w = Utility::text::stringToInt( containter.at(0) );
	int h = Utility::text::stringToInt( containter.at(1) );
	setMinimizeSize( Size( w, h ) );
}

void GuiFrameWindow::setFixedSize( const std::wstring& value )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( value, L",", containter );
	if ( containter.size() != 2 )
	{
		assert( false );
		return;
	}

	int w = Utility::text::stringToInt( containter.at(0) );
	int h = Utility::text::stringToInt( containter.at(1) );
	setFixedSize( Size( w, h ) );
}

void GuiFrameWindow::setFixedSize( const Size& size )
{
	setMaximizeSize( size );
	setMinimizeSize( size );
	Rect rc = geometry();
	setGeometry( rc.GetLeft(), rc.GetTop(), size.Width, size.Height );
}

Size GuiFrameWindow::fixedSize()
{
	Size size;
	geometry().GetSize( &size );
	return size;
}

void GuiFrameWindow::setDefaultSize( const std::wstring& value )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( value, L",", containter );
	if ( containter.size() != 2 )
	{
		assert( false );
		return;
	}

	int w = Utility::text::stringToInt( containter.at(0) );
	int h = Utility::text::stringToInt( containter.at(1) );
	Rect rc = geometry();
	setGeometry( rc.GetLeft(), rc.GetTop(), w, h );
}

Rect GuiFrameWindow::dirtyRect()
{
	return d_ptr->dirtyRect;
}

void GuiFrameWindow::setWindowTitle( const std::wstring& tx )
{
	if ( !isVaildWindow() )
	{
		return;
	}
	
	d_ptr->windowTitle = tx;
	::SetWindowText( hwnd(), d_ptr->windowTitle.c_str() );
}

std::wstring GuiFrameWindow::windowTitle()
{
	return d_ptr->windowTitle;
}

void GuiFrameWindow::setWindowIcon( const std::wstring& iconPath )
{
	if ( !isVaildWindow() )
	{
		return;
	}

	d_ptr->windowIconPath = iconPath;
	std::wstring fixIconPath = guiApp->exePath() + L"/" + d_ptr->windowIconPath;
	HICON hIcon;
	Bitmap bitmap( fixIconPath.c_str() );
	bitmap.GetHICON( &hIcon );
	SendMessage( hwnd(), WM_SETICON, 0 /* ICON_SMALL */, (LPARAM)hIcon);
	SendMessage( hwnd(), WM_SETICON, 1 /* ICON_BIG */, (LPARAM)hIcon);
}

std::wstring GuiFrameWindow::windowIcon()
{
	return d_ptr->windowIconPath;
}
