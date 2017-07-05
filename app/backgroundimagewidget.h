#pragma once
#include "guifw/guiwidget.h"

class BackgroundImageWidget : public GuiWidget
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( BackgroundImageWidget )

public:
	BackgroundImageWidget( GuiWidget* parent = NULL );
	~BackgroundImageWidget(void);

	void setImagePath( const std::wstring& text );
	std::wstring imagePath();

	virtual void setAttribute( std::wstring& name, std::wstring& value );

protected:
	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );

private:
	std::wstring m_imagePath;
};
