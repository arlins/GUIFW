#include "guiglobal.h"
#include "guiimagewidget.h"
#include "private/guiimagewidget_p.h"
#include "guifw/guiapplication.h"
#include "guifw/guiframewindow.h"

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiImageWidget )
GuiImageWidget::GuiImageWidget( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
, d_ptr( new GuiImageWidgetPrivate )
{

}

GuiImageWidget::~GuiImageWidget( void )
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiImageWidget::construct()
{

}

void GuiImageWidget::paintEvent( GuiPainter* painter )
{
	std::wstring imagePath =  guiApp->exePath() + L"/" + d_ptr->imagePath; 
	painter->drawImage( imagePath, geometry() );
}

void GuiImageWidget::setImagePath( const std::wstring& imagePath )
{
	d_ptr->imagePath = imagePath;
}

std::wstring GuiImageWidget::imagePath()
{
	return d_ptr->imagePath;
}

void GuiImageWidget::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"imagePath" )
	{
		setImagePath( value );
	}
	else
	{
		GuiWidget::setAttribute( name, value );
	}
}
