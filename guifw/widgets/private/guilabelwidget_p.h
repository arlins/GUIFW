#pragma once
#include "guiglobal.h"

class GuiLabelWidgetPrivate
{
public:
	GuiLabelWidgetPrivate()
		: textSize( 9 )
		, textColor( 254, 0, 0, 0 )
	{

	}
	~GuiLabelWidgetPrivate()
	{

	}

	std::wstring text;
	Color textColor;
	int textSize;
};
