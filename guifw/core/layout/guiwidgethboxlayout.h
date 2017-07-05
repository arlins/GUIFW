#pragma once

class GuiWidget;

class GuiWidgetHBoxLayout
{
public:
	GuiWidgetHBoxLayout( );
	~GuiWidgetHBoxLayout(void);

	static void updateLayout( GuiWidget* rootWidget );
};
