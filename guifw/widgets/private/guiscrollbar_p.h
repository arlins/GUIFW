#pragma once

class GuiScrollBarPrivate
{
public:
	GuiScrollBarPrivate()
		: maxValue( 100 )
		, currentValue( 0 ) 
		, bMousePressed( false )
	{

	}
	~GuiScrollBarPrivate()
	{

	}

	bool bMousePressed;
	std::wstring backgroundImage;
	std::wstring thumbImage;
	int maxValue;
	int currentValue;
};
