#pragma once
#include "guifw/guiwidget.h"

class GuiPushButtonPrivate;

class GUIFW_DECL_EXPORT GuiPushButton : public GuiWidget
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( GuiPushButton )

public:
	GuiPushButton( GuiWidget* parent = NULL );
	~GuiPushButton(void);
	
	enum FrameState
	{
		StateNormal = 0,
		StateHover,
		StatePressed,
		StateDisable,
		StateCheck,
		StateMax,
	};

	void setImagePath( const std::wstring& imagePath );
	void setIconPath( const std::wstring& iconPath );

	virtual void setAttribute( std::wstring& name, std::wstring& value );

gui_signals:
	typedef xsignals::signal<void ()> _def_void_signal;  
	_def_void_signal clicked;

protected:
	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );
	virtual void hoverMoveEvent( GuiEvent* msg );
	virtual void hoverEnterEvent( GuiEvent* msg );
	virtual void hoverLeaveEvent( GuiEvent* msg );
	virtual void mouseLButtonPressEvent( GuiEvent* msg );
	virtual void mouseLButtonReleaseEvent( GuiEvent* msg );

private:
	GuiPushButtonPrivate* d_ptr;
};
