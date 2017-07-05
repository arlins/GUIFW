#include "guiglobal.h"
#include "guiapplication.h"
#include "guiwindoweventdispatcher.h"
#include "private/guiapplication_p.h"
#include "guidefs.h"

GuiApplication* g_app = NULL;
GuiApplication* guiApplication()
{
	return g_app;	
}

GuiApplication::GuiApplication()
: d_ptr( new GuiApplicationPrivate() )
{
	g_app = this;
	_init();
}

GuiApplication::~GuiApplication()
{
	GdiplusShutdown( d_ptr->gdiplusToken );
	Gui_SAFE_DELETE( d_ptr );
	g_app = NULL;
}

int GuiApplication::exec()
{
	MSG msg = { 0 };
	while( ::GetMessage(&msg, NULL, 0, 0) ) 
	{
		bool bMsgFlitered = false;
		if ( d_ptr->eventFilterFunc )
		{
			bMsgFlitered = (*(d_ptr->eventFilterFunc))( & msg ) ;
		}
		if( !bMsgFlitered ) 
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

void GuiApplication::installEventFilter( EventFilterFuncType func )
{
	d_ptr->eventFilterFunc = func;
}

void GuiApplication::removeEventFilter()
{
	d_ptr->eventFilterFunc = NULL;
}

std::wstring GuiApplication::cmdLine()
{
	return ::GetCommandLineW();
}

void GuiApplication::_init()
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup( &d_ptr->gdiplusToken, &gdiplusStartupInput, NULL );
}

std::wstring GuiApplication::exePath()
{
	return d_ptr->exePath;
}

void GuiApplication::setQuitOnLastWindowClosed( bool bQuit )
{
	d_ptr->bQuitOnLastWindowClosed = bQuit;
}

bool GuiApplication::quitOnLastWindowClosed()
{
	return d_ptr->bQuitOnLastWindowClosed;
}

void GuiApplication::addFrameWindow( GuiFrameWindow* frameWindow )
{
	std::vector<GuiFrameWindow*>::iterator it = d_ptr->frameWindowList.begin();
	for ( ; it != d_ptr->frameWindowList.end(); it++ )
	{
		if ( frameWindow == *it )
		{
			break;
		}
	}

	if ( it == d_ptr->frameWindowList.end() )
	{
		d_ptr->frameWindowList.push_back( frameWindow );
	}
}

void GuiApplication::removeFrameWindow( GuiFrameWindow* frameWindow )
{
	std::vector<GuiFrameWindow*>::iterator it = d_ptr->frameWindowList.begin();
	for ( ; it != d_ptr->frameWindowList.end(); it++ )
	{
		if ( frameWindow == *it )
		{
			break;;
		}
	}

	if ( it != d_ptr->frameWindowList.end() )
	{
		d_ptr->frameWindowList.erase( it );
	}

	if ( d_ptr->frameWindowList.empty() && d_ptr->bQuitOnLastWindowClosed )
	{
		quit( 0 );
	}
}

void GuiApplication::quit( int exitCode )
{
	::PostQuitMessage( exitCode );
}
