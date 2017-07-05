#pragma once

class GUIFW_DECL_EXPORT GuiEvent
{
public:

	GuiEvent();
	~GuiEvent();

	enum EventType
	{
		GuiEventType = WM_USER + 1,
	};

	int type;
	WPARAM wParam;
	LPARAM lParam;
	bool bAccepted;
};


