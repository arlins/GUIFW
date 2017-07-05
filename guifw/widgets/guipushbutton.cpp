#include "guipushbutton.h"
#include "private/guipushbutton_p.h"
#include "guifw/guiapplication.h"
#include "guifw/guiframewindow.h"
#include "../utility/text/ustring.h"

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiPushButton )
GuiPushButton::GuiPushButton( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
, d_ptr( new GuiPushButtonPrivate )
{
	setDragWidgetFlag( GuiWidget::NotDragWindow );
}

GuiPushButton::~GuiPushButton( void )
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiPushButton::hoverEnterEvent( GuiEvent* msg )
{
	d_ptr->status = StateHover;
	update();
}

void GuiPushButton::hoverLeaveEvent( GuiEvent* msg )
{
	d_ptr->status = StateNormal;
	update();
}

void GuiPushButton::mouseLButtonPressEvent( GuiEvent* msg )
{
	d_ptr->status = StatePressed;
	update();
}

void GuiPushButton::mouseLButtonReleaseEvent( GuiEvent* msg )
{
	d_ptr->status = StateHover;
	update();

	clicked();
}

void GuiPushButton::paintEvent( GuiPainter* painter )
{
	std::wstring imagePath =  guiApp->exePath() + L"/"; 
	std::wstring iconAllPath = guiApp->exePath() + L"/" + d_ptr->iconPath;
	Image icon( iconAllPath.c_str() );

	if ( d_ptr->status == StateNormal )
	{
		imagePath += d_ptr->normalImage;
	}
	else if ( d_ptr->status == StateHover )
	{
		imagePath += d_ptr->hoverImage;
	}
	else if ( d_ptr->status == StatePressed )
	{
		imagePath += d_ptr->pressImage;
	}

	int leftPos = geometry().GetLeft() + (fixWidth() - icon.GetWidth())/2;
	int topPos = geometry().GetTop() + (fixHeight() - icon.GetHeight())/2;
	Rect iconRect = Rect( leftPos, topPos, icon.GetWidth(), icon.GetHeight() );

	painter->drawImage( imagePath, geometry() );
	painter->drawImage( iconAllPath, iconRect );
}

void GuiPushButton::hoverMoveEvent( GuiEvent* msg )
{
	
}

void GuiPushButton::construct()
{
	
}

void GuiPushButton::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"imagePath" )
	{
		setImagePath( value );
	}
	else if ( name == L"iconPath" )
	{
		setIconPath( value );
	}
	else
	{
		GuiWidget::setAttribute( name, value );
	}
}

void GuiPushButton::setImagePath( const std::wstring& imagePath )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( imagePath, L"|", containter );
	if ( containter.size() != 3 )
	{
		assert( false );
		return;
	}

	d_ptr->normalImage = containter.at( 0 );
	d_ptr->hoverImage = containter.at( 1 );
	d_ptr->pressImage = containter.at( 2 );
}

void GuiPushButton::setIconPath( const std::wstring& iconPath )
{
	d_ptr->iconPath = iconPath;
}
