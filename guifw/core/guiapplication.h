#pragma once 
#include "guiglobal.h"

typedef bool (*EventFilterFuncType)( MSG* msg );

class GuiApplicationPrivate;

class GUIFW_DECL_EXPORT GuiApplication
{

public:
	GuiApplication( );
	~GuiApplication();
	
	int exec();
	void quit( int exitCode );

	void installEventFilter( EventFilterFuncType func );
	void removeEventFilter( );
	
	std::wstring cmdLine();
	std::wstring exePath();

	void setQuitOnLastWindowClosed( bool bQuit );
	bool quitOnLastWindowClosed();

protected:
	friend class GuiFrameWindow;
	void addFrameWindow( GuiFrameWindow* frameWindow );
	void removeFrameWindow( GuiFrameWindow* frameWindow );

private:
	void _init();

protected:
	GuiApplicationPrivate* d_ptr;
};

GUIFW_DECL_EXPORT GuiApplication* guiApplication();
#define guiApp guiApplication()