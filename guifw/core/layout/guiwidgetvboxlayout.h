#pragma once
#include "../guiwidget.h"

class GuiWidgetVBoxLayout 
{
public:
	GuiWidgetVBoxLayout( );
	~GuiWidgetVBoxLayout(void);

	static void updateLayout( GuiWidget* rootWidget );
};
