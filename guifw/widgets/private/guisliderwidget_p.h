#pragma once

class GuiSliderWidgetPrivate
{
public:
	GuiSliderWidgetPrivate()
		: maxValue( 100 )
		, currentValue( 0 ) 
		, bMousePressed( false )
	{

	}
	~GuiSliderWidgetPrivate()
	{

	}

	bool bMousePressed;
	std::wstring backgroundImage;
	std::wstring thumbImage;
	int maxValue;
	int currentValue;
};
