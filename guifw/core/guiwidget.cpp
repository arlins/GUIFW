#include "guiglobal.h"
#include "guiwidget.h"
#include "guiframewindow.h"
#include "private/guiwidget_p.h"
#include "../utility/text/ustring.h"
#include "layout/guiwidgethboxlayout.h"
#include "layout/guiwidgetvboxlayout.h"

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiWidget );
GuiWidget::GuiWidget( GuiWidget* parent )
: GuiObject( parent )
, d_ptr( new GuiWidgetPrivate() )
{
	setLayout( HBox );
}

GuiWidget::~GuiWidget()
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiWidget::doConstruct()
{
	if ( !d_ptr->xmlPath.empty() )
	{
		GuiXmlUI::createFromFile( d_ptr->xmlPath, L"", this );
	}

	construct();
}

void GuiWidget::construct()
{

}

GuiFrameWindow* GuiWidget::frameWindow()
{
	return d_ptr->frameWindow;
}

void GuiWidget::setGuiFrameWindow( GuiFrameWindow* frameWindow )
{
	d_ptr->frameWindow = frameWindow;
}

void GuiWidget::setVisible( bool bVisible )
{
	d_ptr->bVisible = bVisible;
	std::list<GuiObject*> children = getChildren();
	for ( std::list<GuiObject*>::iterator it = children.begin(); it != children.end(); it++ )
	{
		GuiWidget* child = static_cast<GuiWidget*>( *it );
		if ( child )
		{
			child->setVisible( bVisible );
		}
	}
}

bool GuiWidget::isVisible()
{
	return d_ptr->bVisible;
}

void GuiWidget::paintEvent( GuiPainter* painter )
{
	LinearGradientBrush brush( Point(0,0), Point( 1, 1 ), d_ptr->backgroundColor, d_ptr->backgroundColor);
	painter->fillRect( &brush, geometry() );
}

void GuiWidget::show()
{
	setVisible( true );
}

void GuiWidget::hide()
{	
	setVisible( false );
}

void GuiWidget::setGeometry( const Rect& rc )
{
	d_ptr->geometry = rc;
	GuiEvent ev;
	resizeEvent( &ev );
	updateLayout();
}

Rect GuiWidget::geometry()
{
	return d_ptr->geometry;
}

void GuiWidget::update()
{
	if ( d_ptr->frameWindow == NULL )
	{
		return;
	}

	d_ptr->frameWindow->update( geometry() ); 
}

void GuiWidget::setDragWidgetFlag( DragWidgetFlag flag )
{
	d_ptr->dragWidgetFlag = flag;
}

GuiWidget::DragWidgetFlag GuiWidget::dragWidgetFlag()
{
	if ( d_ptr->dragWidgetFlag == DragWithParentFlag )
	{
		if ( parent() )
		{
			GuiWidget* parentWidget = static_cast<GuiWidget*>( parent() );
			if ( parentWidget )
			{
				return parentWidget->dragWidgetFlag();
			}
			else
			{
				return GuiWidget::NotDragWindow;
			}
		}
		else
		{
			return GuiWidget::NotDragWindow;
		}
	}

	return d_ptr->dragWidgetFlag; 
}

void GuiWidget::setBackgroundColor( const std::wstring& value )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( value, L",", containter );
	if ( containter.size() == 3 )
	{
		int r = Utility::text::stringToInt( containter.at(0) );
		int g = Utility::text::stringToInt( containter.at(1) );
		int b = Utility::text::stringToInt( containter.at(2) );

		setBackgroundColor( Color( r, g, b ) );
	}
	else if ( containter.size() == 4 )
	{
		int a = Utility::text::stringToInt( containter.at(0) );
		int r = Utility::text::stringToInt( containter.at(1) );
		int g = Utility::text::stringToInt( containter.at(2) );
		int b = Utility::text::stringToInt( containter.at(3) );

		setBackgroundColor( Color( a, r, g, b ) );
	}
}

void GuiWidget::setBackgroundColor( const Color& color )
{
	d_ptr->backgroundColor = color;
}

Color GuiWidget::backgroundColor()
{
	return d_ptr->backgroundColor;
}

void GuiWidget::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"backgroundColor" )
	{
		setBackgroundColor( value );
	}
	else if ( name == L"layout" )
	{
		setLayout( value );
	}
	else if ( name == L"fixWidth" )
	{
		setFixedWidth( value );
	}
	else if ( name == L"fixHeight" )
	{
		setFixedHeight( value );
	}
	else if ( name == L"xmlPath" )
	{
		setXmlPath( value );
	}
	else if ( name == L"visible" )
	{
		setVisible( value );
	}
	else
	{
		GuiObject::setAttribute( name, value );
	}
}

void GuiWidget::updateLayout()
{
	if ( d_ptr->layoutType == HBox )
	{
		GuiWidgetHBoxLayout::updateLayout( this );
	}
	else if ( d_ptr->layoutType == VBox )
	{
		GuiWidgetVBoxLayout::updateLayout( this );
	}
}

void GuiWidget::setLayout( const std::wstring& value )
{	
	if ( value == L"HBox" )
	{
		setLayout( HBox );
	}
	else if ( value == L"VBox")
	{
		setLayout( VBox );
	}
}


void GuiWidget::setLayout( LayoutType layoutType )
{	
	d_ptr->layoutType = layoutType;
}

GuiWidget::LayoutType GuiWidget::layoutType()
{
	return d_ptr->layoutType;
}

void GuiWidget::setPosition( const Point& pt )
{
	Rect rc( pt.X, pt.Y, fixWidth(), fixHeight() );
	setGeometry( rc );
}

Point GuiWidget::position()
{
	return Point( geometry().GetLeft(), geometry().GetTop() );
}

void GuiWidget::setFixedSize( const Size& size )
{
	setMinimizeSize( size );
	setMaximizeSize( size );
	Rect rc( geometry().GetLeft(), geometry().GetTop(), size.Width, size.Height );
	setGeometry( rc );
}

Size GuiWidget::fixedSize()
{
	return Size( geometry().Width, geometry().Height );
}

void GuiWidget::setMinimizeSize( const Size& size )
{
	d_ptr->minimizeSize = size;
}

Size GuiWidget::minimizeSize()
{
	return d_ptr->minimizeSize;
}

void GuiWidget::setMaximizeSize( const Size& size )
{
	d_ptr->maximizeSize = size;
}

Size GuiWidget::maximizeSize()
{
	return d_ptr->maximizeSize;
}

void GuiWidget::setFixedWidth( int w )
{
	setMinimizeWidth( w );
	setMaximizeWidth( w );
	Rect rc( geometry().GetLeft(), geometry().GetTop(), w, geometry().Height );
	setGeometry( rc );
}

void GuiWidget::setFixedHeight( int h )
{
	setMinimizeHeight( h );
	setMaximizeHeight( h );
	Rect rc( geometry().GetLeft(), geometry().GetTop(), geometry().Width, h );
	setGeometry( rc );
}

void GuiWidget::setMinimizeWidth( int w )
{
	d_ptr->minimizeSize = Size( w, d_ptr->minimizeSize.Height );
}

void GuiWidget::setMinimizeHeight( int h )
{
	d_ptr->minimizeSize = Size( d_ptr->minimizeSize.Width, h );
}

void GuiWidget::setMaximizeWidth( int w )
{
	d_ptr->maximizeSize = Size( w, d_ptr->maximizeSize.Height );
}

void GuiWidget::setMaximizeHeight( int h )
{
	d_ptr->maximizeSize = Size( d_ptr->maximizeSize.Width, h );
}

int GuiWidget::fixWidth()
{
	return d_ptr->geometry.Width;
}

int GuiWidget::fixHeight()
{
	return d_ptr->geometry.Height;
}

int GuiWidget::minimizeWidth()
{
	return d_ptr->minimizeSize.Width;
}

int GuiWidget::minimizeHeight()
{
	return d_ptr->minimizeSize.Height;
}

int GuiWidget::maximizeWidth()
{
	return d_ptr->maximizeSize.Width;
}

int GuiWidget::maximizeHeight()
{
	return d_ptr->maximizeSize.Height;
}

void GuiWidget::setFixedWidth( const std::wstring& value )
{
	int w = Utility::text::stringToInt( value );
	setFixedWidth( w );
}

void GuiWidget::setFixedHeight( const std::wstring& value )
{
	int h = Utility::text::stringToInt( value );
	setFixedHeight( h );
}

void GuiWidget::closeEvent( GuiEvent* msg )
{

}

void GuiWidget::resizeEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseWheelEvent( GuiEvent* msg )
{

}

void GuiWidget::hoverMoveEvent( GuiEvent* msg )
{
	
}

void GuiWidget::hoverEnterEvent( GuiEvent* msg )
{
	
}

void GuiWidget::hoverLeaveEvent( GuiEvent* msg )
{
	
}

void GuiWidget::mouseLButtonPressEvent( GuiEvent* msg )
{
	
}

void GuiWidget::mouseLButtonReleaseEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseMButtonPressEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseMButtonReleaseEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseRButtonPressEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseRButtonReleaseEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseMButtonDoubleClickEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseLButtonDoubleClickEvent( GuiEvent* msg )
{

}

void GuiWidget::mouseRButtonDoubleClickEvent( GuiEvent* msg )
{

}

void GuiWidget::setXmlPath( const std::wstring& xmlPath )
{
	d_ptr->xmlPath = xmlPath;
}

void GuiWidget::setVisible( const std::wstring& bVisible )
{
	setVisible( bVisible == L"true" );
}

void GuiWidget::setClipFlag( ClipFlag flag )
{
	d_ptr->clipFlag = flag;
}

GuiWidget::ClipFlag GuiWidget::clipFlag()
{
	return d_ptr->clipFlag;
}

Rect GuiWidget::realShape()
{
	Rect realRect = geometry();
	bool bClipedByParent = false;
	Rect parentClipRect;
	GuiWidget* parentWidget = static_cast<GuiWidget*>( parent() );
	GuiWidget* childWidget = this;
	while ( parentWidget != NULL && childWidget != NULL )
	{
		if ( parentWidget->clipFlag() == GuiWidget::ChildrenClipToShape )
		{
			bClipedByParent = true;
			parentClipRect = parentWidget->geometry();
			break;
		}

		GuiWidget* tmpWidget = parentWidget;
		parentWidget = static_cast<GuiWidget*>( childWidget->parent() );
		childWidget = tmpWidget;
	}

	if ( bClipedByParent )
	{
		realRect.Intersect( parentClipRect );
	}

	return realRect;
}
