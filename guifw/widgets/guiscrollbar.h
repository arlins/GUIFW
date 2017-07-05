#pragma once
#include "guifw/guiwidget.h"

class GuiScrollBarPrivate;

class GUIFW_DECL_EXPORT GuiScrollBar : public GuiWidget
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( GuiScrollBar )

public:
	GuiScrollBar( GuiWidget* parent = NULL );
	~GuiScrollBar(void);

	void setMaxValue( int value );
	int maxValue();

	void setCurrentValue( int value );
	int currentValue();

	void setBackgroundImagePath( const std::wstring& imagePath );
	void setThumbImagePath( const std::wstring& imagePath );
	
	virtual void setAttribute( std::wstring& name, std::wstring& value );

gui_signals:
	typedef xsignals::signal<void ()> _def_void_signal;  
	_def_void_signal valueChanged;

protected:
	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );
	virtual void hoverMoveEvent( GuiEvent* msg );
	virtual void hoverEnterEvent( GuiEvent* msg );
	virtual void hoverLeaveEvent( GuiEvent* msg );
	virtual void mouseLButtonPressEvent( GuiEvent* msg );
	virtual void mouseLButtonReleaseEvent( GuiEvent* msg );

private:
	void _updateSlider( const Point& pt );
	int _sliderHeight();

private:
	GuiScrollBarPrivate* d_ptr;
};
