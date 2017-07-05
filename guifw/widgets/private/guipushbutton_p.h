#pragma once
#include "../guipushbutton.h"

class GuiPushButtonPrivate
{
public:
	GuiPushButtonPrivate()
		: status( GuiPushButton::StateNormal )
		, normalImage( L"theme/btn_normal.png" )
		, hoverImage( L"theme/btn_hover.png" )
		, pressImage( L"theme/btn_press.png" )
		, iconPath( L"" )
	{

	}
	~GuiPushButtonPrivate()
	{

	}

	GuiPushButton::FrameState status;
	std::wstring normalImage;
	std::wstring hoverImage;
	std::wstring pressImage;
	std::wstring iconPath;
};
