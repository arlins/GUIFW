#pragma once
#include "guiglobal.h"
#include "guifw/guiobject.h"

class GuiSkinManagerPrivate;

class GUIFW_DECL_EXPORT GuiSkinManager : private GuiObject
{
public:
	GuiSkinManager();
	~GuiSkinManager();

	void setSkinImage( const Color& color );
	void setSkinImagePath( const std::wstring& skinImagePath );
	std::wstring skinImagePath();

	void setSkinAlphaValue( int value );
	int skinAlphaValue();

gui_signals:
	typedef xsignals::signal<void ()> _def_void_signal;  
	_def_void_signal skinImageChanged;
	_def_void_signal skinAlphaValueChanged;

private:
	GuiSkinManagerPrivate* d_ptr;
};

GUIFW_DECL_EXPORT GuiSkinManager* skinManager();


