#pragma once
#include "guifw/guiwidget.h"

class GuiImageWidgetPrivate;

class GUIFW_DECL_EXPORT GuiImageWidget : public GuiWidget
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( GuiImageWidget )

public:
	GuiImageWidget( GuiWidget* parent = NULL );
	~GuiImageWidget(void);

	void setImagePath( const std::wstring& text );
	std::wstring imagePath();

	virtual void setAttribute( std::wstring& name, std::wstring& value );

protected:
	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );

private:
	GuiImageWidgetPrivate* d_ptr;
};
