#include "guiglobal.h"
#include "guilabelwidget.h"
#include "private/guilabelwidget_p.h"
#include "guifw/guiapplication.h"
#include "guifw/guiframewindow.h"
#include "../utility/text/ustring.h"

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiLabelWidget )
GuiLabelWidget::GuiLabelWidget( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
, d_ptr( new GuiLabelWidgetPrivate )
{
	
}

GuiLabelWidget::~GuiLabelWidget( void )
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiLabelWidget::construct()
{

}

void GuiLabelWidget::paintEvent( GuiPainter* painter )
{
	SolidBrush brush( d_ptr->textColor );
	Font ft( L"MicrosoftYaHei", REAL( d_ptr->textSize ) );
	painter->drawText( d_ptr->text.c_str(), &ft, PointF( REAL(geometry().GetLeft()), REAL(geometry().GetTop()) ), &brush );
}

void GuiLabelWidget::setText( const std::wstring& text )
{
	d_ptr->text = text;
}

std::wstring GuiLabelWidget::text()
{
	return d_ptr->text;
}

void GuiLabelWidget::setTextColor( const Color& color )
{
	d_ptr->textColor = Color( 254, color.GetRed(), color.GetGreen(), color.GetBlue() ); //不支持透明字体
}

Color GuiLabelWidget::textColor()
{
	return d_ptr->textColor;
}

void GuiLabelWidget::setTextSize( int ts )
{
	d_ptr->textSize = ts;
}

int GuiLabelWidget::textSize()
{
	return d_ptr->textSize;
}

void GuiLabelWidget::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"textColor" )
	{
		setTextColor( value );
	}
	else if ( name == L"textSize" )
	{
		setTextSize( value );
	}
	else if ( name == L"text" )
	{
		setText( value );
	}
	else
	{
		GuiWidget::setAttribute( name, value );
	}
}

void GuiLabelWidget::setTextColor( const std::wstring& value )
{
	std::vector<std::wstring> containter;
	Utility::text::spliteString( value, L",", containter );
	if ( containter.size() == 3 )
	{
		int r = Utility::text::stringToInt( containter.at(0) );
		int g = Utility::text::stringToInt( containter.at(1) );
		int b = Utility::text::stringToInt( containter.at(2) );

		setTextColor( Color( r, g, b ) );
	}
	else if ( containter.size() == 4 )
	{
		int a = Utility::text::stringToInt( containter.at(0) );
		int r = Utility::text::stringToInt( containter.at(1) );
		int g = Utility::text::stringToInt( containter.at(2) );
		int b = Utility::text::stringToInt( containter.at(3) );

		setTextColor( Color( a, r, g, b ) ); 
	}
}

void GuiLabelWidget::setTextSize( const std::wstring& value )
{
	int ts = Utility::text::stringToInt( value );
	setTextSize( ts );
}