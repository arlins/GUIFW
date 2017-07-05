#include "guiapplication_p.h"
#include "../guiwindoweventdispatcher.h"
#include "../guidefs.h"

GuiApplicationPrivate::GuiApplicationPrivate()
: eventFilterFunc( NULL )
, exePath( L"" )
, bQuitOnLastWindowClosed( false )
{
	_initExePath();
	_registerWindow();
}

GuiApplicationPrivate::~GuiApplicationPrivate()
{

}

void GuiApplicationPrivate::_initExePath()
{
	TCHAR szProcessPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL, szProcessPath, MAX_PATH - 1);

	exePath = szProcessPath;
	int nPos1 = exePath.rfind(L"\\");
	exePath = exePath.substr(0, nPos1);
	std::wstring src = L"\\";
	std::wstring des = L"/";

	int pos = -1;
	int curPos = 0;
	while (-1 != (pos = exePath.find(src, curPos)))
	{
		exePath.replace(pos, src.size(), des);
		curPos = pos + des.size();
	}
}

bool GuiApplicationPrivate::_registerWindow()
{
	WNDCLASS wndclass;//窗口类结构

	wndclass.style =CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//CS_开头表示类的风格, CS_DBLCLKS表示窗口接受双击事件
	wndclass.lpfnWndProc = &GuiWindowEventDispatcher::WinProc;//指向窗口过程的指针
	wndclass.cbClsExtra = 0;//系统保留的扩展名称，通常为0
	wndclass.cbWndExtra = 0;//系统保留的扩展名称，通常为0

	wndclass.hInstance = ::GetModuleHandle( NULL );
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);//IDI_表示图标的
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);//IDC_表示光标的,鼠标指针
	wndclass.hbrBackground = (HBRUSH)GetSysColorBrush(WHITE_BRUSH);//画刷句柄，获取一个图形对象

	wndclass.lpszMenuName = NULL;//若窗口有菜单，则放置菜单名称

	wndclass.lpszClassName = KWinClassName;
	DWORD ret = (DWORD)RegisterClass(&wndclass);

	return ret == 1;
}
