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
	WNDCLASS wndclass;//������ṹ

	wndclass.style =CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//CS_��ͷ��ʾ��ķ��, CS_DBLCLKS��ʾ���ڽ���˫���¼�
	wndclass.lpfnWndProc = &GuiWindowEventDispatcher::WinProc;//ָ�򴰿ڹ��̵�ָ��
	wndclass.cbClsExtra = 0;//ϵͳ��������չ���ƣ�ͨ��Ϊ0
	wndclass.cbWndExtra = 0;//ϵͳ��������չ���ƣ�ͨ��Ϊ0

	wndclass.hInstance = ::GetModuleHandle( NULL );
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);//IDI_��ʾͼ���
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);//IDC_��ʾ����,���ָ��
	wndclass.hbrBackground = (HBRUSH)GetSysColorBrush(WHITE_BRUSH);//��ˢ�������ȡһ��ͼ�ζ���

	wndclass.lpszMenuName = NULL;//�������в˵�������ò˵�����

	wndclass.lpszClassName = KWinClassName;
	DWORD ret = (DWORD)RegisterClass(&wndclass);

	return ret == 1;
}
