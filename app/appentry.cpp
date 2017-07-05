#include "stable.h"
#include "guifw/guixmlui.h"
#include "guifw/guiapplication.h"
#include "mainwindow.h"
#include "guifw/utility/graphics.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{
	GuiApplication app;
	app.setQuitOnLastWindowClosed( true );

	MainWindow* win = static_cast<MainWindow*>(GuiXmlUI::createFromFile( L"layout/mainwindow.xml", L"",(GuiFrameWindow*)NULL ));
	if ( win )
	{
		win->centerWindow();
		win->show();
	}

	return app.exec();
}



