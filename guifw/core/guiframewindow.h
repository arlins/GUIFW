#pragma once 
#include "guiobject.h"
#include <gdiplus.h>
#include "guifw/guixmlui.h"
#include "guifw/guievent.h"

class GuiWidget;
class GuiFrameWindowPrivate;
class GuiWidgetEventDispatcher;
class GuiPainter;

class GUIFW_DECL_EXPORT GuiFrameWindow : public GuiObject 
{
	GUI_DECLARE_FRAME_DYNAMIC_CREATE_SELF( GuiFrameWindow );

public:
	explicit GuiFrameWindow( GuiFrameWindow* parent = NULL );
	virtual ~GuiFrameWindow();

	GuiWidget* rootWidget();
	HWND hwnd();

	void show();
	void hide();
	void close();
	void showMinimize();
	void showMaximize();
	void showNormal();
	void showRestore();

	void setVisible( bool bVisible );
	bool isVisible();

	void setFixedSize( const Size& size );
	Size fixedSize();
	void setMaximizeSize( const Size& size );
	Size maximizeSize();
	void setMinimizeSize( const Size& size );
	Size minimizeSize();
	void setGeometry( int x, int y, int cx, int cy );
	Rect geometry();
	Rect rect();

	int width();
	int height();

	void centerWindow();
	void update( Rect dirtyRect = Rect(0,0,0,0) );
	void layout();
	bool isVaildWindow();

	void setOpacity( int op );
	int opacity();

	void setIgnoreSkinChange( bool bIgnore );
	bool ignoreSkinChange();

	void setWindowTitle( const std::wstring& tx );
	std::wstring windowTitle();

	void setWindowIcon( const std::wstring& iconPath );
	std::wstring windowIcon();

	void setBackgroundImage( const std::wstring& filePath );
	void setTransparentBackground( bool bTransparent );
	void setMouseTracking( bool bMouseTracking ); // enable to receive mouse hover event
	bool mouseTracking();
	
	Point mapFromScreen( const Point& pt );
	Point mapToScreen( const Point& pt );
	Point clientPointFromEvent( GuiEvent* ev );
	GuiWidget* findWidgetByPoint( const Point& pt );

	virtual void setAttribute( std::wstring& name, std::wstring& value );

gui_signals:
	typedef xsignals::signal<void ()> _def_void_signal;  
	_def_void_signal aboutToClose;

gui_slots:
	void on_skinAlphaValueChanged();
	void on_skinImageChanged();

protected:
	friend class GuiXmlUI;
	void doConstruct();
	virtual void construct();

protected:
	friend class GuiWidgetEventDispatcher;
	Rect dirtyRect();

protected: // used by GuiWindowEventDispatcher
	friend class GuiWindowEventDispatcher;
	LRESULT windowNcHitTest( GuiEvent* msg );
	void windowGetMinMaxInfoEvent( GuiEvent* msg );
	void windowCloseEvent( GuiEvent* msg );
	void windowResizeEvent( GuiEvent* msg );
	void windowPaintEvent();
	void windowMouseWheelEvent( GuiEvent* msg );
	void windowMouseHoverEvent( GuiEvent* msg );
	void windowMouseMoveEvent( GuiEvent* msg );
	void windowMouseEnterEvent( GuiEvent* msg );
	void windowMouseLeaveEvent( GuiEvent* msg );
	void windowMouseLButtonPressEvent( GuiEvent* msg );
	void windowMouseLButtonReleaseEvent( GuiEvent* msg );
	void windowMouseMButtonPressEvent( GuiEvent* msg );
	void windowMouseMButtonReleaseEvent( GuiEvent* msg );
	void windowMouseRButtonPressEvent( GuiEvent* msg );
	void windowMouseRButtonReleaseEvent( GuiEvent* msg );
	void windowMouseLButtonDoubleClickEvent( GuiEvent* msg );
	void windowMouseMButtonDoubleClickEvent( GuiEvent* msg );
	void windowMouseRButtonDoubleClickEvent( GuiEvent* msg );

protected: // events
	virtual bool winEvent( GuiEvent* msg );
	virtual void closeEvent( GuiEvent* msg );
	virtual void resizeEvent( GuiEvent* msg );
	virtual void paintEvent( GuiPainter* painter );

	virtual void mouseWheelEvent( GuiEvent* msg );
	virtual void mouseHoverEvent( GuiEvent* msg );
	virtual void mouseMoveEvent( GuiEvent* msg );
	virtual void mouseEnterEvent( GuiEvent* msg );
	virtual void mouseLeaveEvent( GuiEvent* msg );
	virtual void mouseLButtonPressEvent( GuiEvent* msg );
	virtual void mouseLButtonReleaseEvent( GuiEvent* msg );
	virtual void mouseMButtonPressEvent( GuiEvent* msg );
	virtual void mouseMButtonReleaseEvent( GuiEvent* msg );
	virtual void mouseRButtonPressEvent( GuiEvent* msg );
	virtual void mouseRButtonReleaseEvent( GuiEvent* msg );
	virtual void mouseLButtonDoubleClickEvent( GuiEvent* msg );
	virtual void mouseMButtonDoubleClickEvent( GuiEvent* msg );
	virtual void mouseRButtonDoubleClickEvent( GuiEvent* msg );
	
protected:
	virtual void drawBackground( GuiPainter* painter );

protected: //attributes from string to specified type
	void setMaximizeSize( const std::wstring& value );
	void setMinimizeSize( const std::wstring& value );
	void setFixedSize( const std::wstring& value );
	void setDefaultSize( const std::wstring& value );

private:
	void _init();
	void _setWindowCorner();
	void _postMessage( UINT Msg,WPARAM wParam,LPARAM lParam );

private:
	GuiFrameWindowPrivate* d_ptr;
};
