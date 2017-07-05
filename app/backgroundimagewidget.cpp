#include "guiglobal.h"
#include "backgroundimagewidget.h"
#include "guifw/guiapplication.h"

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( BackgroundImageWidget )
BackgroundImageWidget::BackgroundImageWidget( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
{

}

BackgroundImageWidget::~BackgroundImageWidget( void )
{
	
}

void BackgroundImageWidget::construct()
{

}

void BackgroundImageWidget::paintEvent( GuiPainter* painter )
{
	std::wstring imagePath =  guiApp->exePath() + L"/" + m_imagePath; 
	painter->drawImage( imagePath, geometry() );
}

void BackgroundImageWidget::setImagePath( const std::wstring& imagePath )
{
	m_imagePath = imagePath;
}

std::wstring BackgroundImageWidget::imagePath()
{
	return m_imagePath;
}

void BackgroundImageWidget::setAttribute( std::wstring& name, std::wstring& value )
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
