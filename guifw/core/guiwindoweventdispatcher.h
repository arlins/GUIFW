#pragma once 

class GuiWindowEventDispatcher
{
public:
	GuiWindowEventDispatcher();
	~GuiWindowEventDispatcher();

	static LRESULT CALLBACK WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

