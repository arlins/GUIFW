#pragma once
#include "guifw/guiwidget.h"

class GuiLabelWidgetPrivate;

class GUIFW_DECL_EXPORT GuiLabelWidget : public GuiWidget
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( GuiLabelWidget )

public:
	GuiLabelWidget( GuiWidget* parent = NULL );
	~GuiLabelWidget(void);

	void setText( const std::wstring& text );
	std::wstring text();
	
	void setTextColor( const Color& color );
	Color textColor();
	
	void setTextSize( int ts );
	int textSize();

	virtual void setAttribute( std::wstring& name, std::wstring& value );

protected:
	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );

protected: //attributes from string to specified type
	void setTextColor( const std::wstring& value );
	void setTextSize( const std::wstring& value );

private:
	GuiLabelWidgetPrivate* d_ptr;
};
