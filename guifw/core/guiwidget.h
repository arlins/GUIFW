#pragma once 
#include "guiobject.h"
#include "guifw/guixmlui.h"
#include "guievent.h"
#include "guipainter.h"

class GuiFrameWindow;
class GuiWidgetPrivate;

class GUIFW_DECL_EXPORT GuiWidget : public GuiObject
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( GuiWidget );

public:
	explicit GuiWidget( GuiWidget* parent = NULL );
	virtual ~GuiWidget();

	enum DragWidgetFlag
	{
		DragWindow = 1,
		NotDragWindow = 2,
		DragWithParentFlag = 3
	};

	enum LayoutType
	{
		NoLayout,
		HBox,
		VBox
	};

	enum ClipFlag
	{
		ClipNone = 0x00,
		ClipToShape = 0x01,
		ChildrenClipToShape = 0x02,
	};

	GuiFrameWindow* frameWindow();

	void show();
	void hide();

	void setVisible( bool bVisible );
	bool isVisible();

	void setGeometry( const Rect& rc );
	Rect geometry();

	void setPosition( const Point& pt );
	Point position();
	void setFixedWidth( int w );
	void setFixedHeight( int h );
	void setMinimizeWidth( int w );
	void setMinimizeHeight( int h );
	void setMaximizeWidth( int w );
	void setMaximizeHeight( int h );
	void setFixedSize( const Size& size );
	void setMinimizeSize( const Size& size );
	void setMaximizeSize( const Size& size );
	int fixWidth();
	int fixHeight();
	int minimizeWidth();
	int minimizeHeight();
	int maximizeWidth();
	int maximizeHeight();
	Size fixedSize();
	Size minimizeSize();
	Size maximizeSize();

	void update();
	void updateLayout();

	void setDragWidgetFlag( DragWidgetFlag flag );
	DragWidgetFlag dragWidgetFlag();

	void setBackgroundColor( const Color& color );
	Color backgroundColor();

	void setLayout( LayoutType layoutType );
	LayoutType layoutType();

	virtual void setAttribute( std::wstring& name, std::wstring& value );
	void setGuiFrameWindow( GuiFrameWindow* frameWindow );

	void setClipFlag( ClipFlag flag );
	ClipFlag clipFlag();

protected:
	friend class GuiWidgetEventDispatcher;

	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );
	virtual void closeEvent( GuiEvent* msg );
	virtual void resizeEvent( GuiEvent* msg );

	virtual void mouseWheelEvent( GuiEvent* msg );
	virtual void hoverMoveEvent( GuiEvent* msg );
	virtual void hoverEnterEvent( GuiEvent* msg );
	virtual void hoverLeaveEvent( GuiEvent* msg );
	virtual void mouseLButtonPressEvent( GuiEvent* msg );
	virtual void mouseLButtonReleaseEvent( GuiEvent* msg );
	virtual void mouseMButtonPressEvent( GuiEvent* msg );
	virtual void mouseMButtonReleaseEvent( GuiEvent* msg );
	virtual void mouseRButtonPressEvent( GuiEvent* msg );
	virtual void mouseRButtonReleaseEvent( GuiEvent* msg );
	virtual void mouseMButtonDoubleClickEvent( GuiEvent* msg );
	virtual void mouseLButtonDoubleClickEvent( GuiEvent* msg );
	virtual void mouseRButtonDoubleClickEvent( GuiEvent* msg );

private:
	friend class GuiXmlUI;
	friend class GuiFrameWindow;
	void doConstruct();
	Rect realShape();

protected: //attributes from string to specified type
	void setBackgroundColor( const std::wstring& value );
	void setLayout( const std::wstring& value );
	void setFixedWidth( const std::wstring& value );
	void setFixedHeight( const std::wstring& value );
	void setXmlPath( const std::wstring& xmlPath );
	void setVisible( const std::wstring& bVisible );

private:
	GuiWidgetPrivate* d_ptr;
};