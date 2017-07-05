#include "guiglobal.h"
#include "guifw/guievent.h"
#include "guiwindoweventdispatcher.h"
#include "guiframewindow.h"
#include "guidefs.h"

GuiWindowEventDispatcher::GuiWindowEventDispatcher( )
{

}

GuiWindowEventDispatcher::~GuiWindowEventDispatcher()
{

}

LRESULT CALLBACK GuiWindowEventDispatcher::WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	GuiFrameWindow* pData = (GuiFrameWindow*)::GetWindowLong( hWnd, GWL_USERDATA );
	if ( pData == NULL || pData->hwnd() != hWnd )
	{
		return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	
	if ( uMsg == WM_ERASEBKGND 
		|| uMsg == WM_NCPAINT 
		|| uMsg == WM_NCCALCSIZE 
		|| uMsg == WM_PAINT ) // do not handle some events
	{
		return FALSE;
	}

	GuiEvent ev;
	ev.type = uMsg;
	ev.wParam = wParam;
	ev.lParam = lParam;

	pData->winEvent( &ev );

	switch( uMsg ) 
	{
		case WM_GETMINMAXINFO:
			{
				pData->windowGetMinMaxInfoEvent( &ev );
				return ::DefWindowProc( hWnd, uMsg, ev.wParam, ev.lParam );
			}
		break;
		case  WM_CLOSE:
			{
				pData->windowCloseEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_NCHITTEST:
			{
				LRESULT lrs = pData->windowNcHitTest( &ev );
				return lrs;
			}
			break;
		case WM_SIZE: 
			{
				pData->windowResizeEvent( &ev ); 
				return FALSE ;
			}
			break;
		case WM_MOUSEHWHEEL: 
		case WM_MOUSEWHEEL:
			{
				pData->windowMouseWheelEvent( &ev ); 
				return FALSE ;
			}
			break;
		case WM_MOUSEMOVE:
			{
				if ( pData->mouseTracking() )
				{
					// be able to receive WM_MOUSEHOVER 
					TRACKMOUSEEVENT csTME;
					csTME.cbSize = sizeof (csTME);
					csTME.dwFlags = TME_HOVER;
					csTME.hwndTrack = hWnd ;
					csTME.dwHoverTime = 500;  // duration
					::TrackMouseEvent ( &csTME ); 
				}
				
				// be able to receive WM_MOUSELEAVE
				TRACKMOUSEEVENT csTME;
				csTME.cbSize = sizeof (csTME);
				csTME.dwFlags = TME_LEAVE;
				csTME.hwndTrack = hWnd ;
				csTME.dwHoverTime = 500; 
				::TrackMouseEvent ( &csTME ); 

				pData->windowMouseMoveEvent( &ev ); 

				return FALSE ;
			}
			break;
		case WM_MOUSEHOVER: 
			{
				pData->windowMouseHoverEvent( &ev ); 
				return FALSE ;
			}
			break;
		case WM_MOUSELEAVE: 
			{
				pData->windowMouseLeaveEvent( &ev ); 
				return FALSE ;
			}
			break;
		case WM_LBUTTONDOWN: 
			{
				pData->windowMouseLButtonPressEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_LBUTTONUP: 
			{
				pData->windowMouseLButtonReleaseEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_MBUTTONDOWN: 
			{
				pData->windowMouseMButtonPressEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_MBUTTONUP: 
			{
				pData->windowMouseMButtonReleaseEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_RBUTTONDOWN: 
			{
				pData->windowMouseRButtonPressEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_RBUTTONUP: 
			{
				pData->windowMouseRButtonReleaseEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_LBUTTONDBLCLK: 
			{
				pData->windowMouseLButtonDoubleClickEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_MBUTTONDBLCLK: 
			{
				pData->windowMouseMButtonDoubleClickEvent( &ev ); 
				return FALSE;
			}
			break;
		case WM_RBUTTONDBLCLK: 
			{
				pData->windowMouseRButtonDoubleClickEvent( &ev ); 
				return FALSE;
			}
			break;
		case GuiPaint:
			{
				pData->windowPaintEvent();
				return FALSE;
			}
			break;
		default:
			break;
	}

	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}
