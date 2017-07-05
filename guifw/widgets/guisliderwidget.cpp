#include "guisliderwidget.h"
#include "private/guisliderwidget_p.h"
#include "guifw/guiapplication.h"
#include "guifw/guiframewindow.h"
#include "../utility/text/ustring.h"

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiSliderWidget )
GuiSliderWidget::GuiSliderWidget( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
, d_ptr( new GuiSliderWidgetPrivate )
{
	d_ptr->backgroundImage = L"theme/slider_background.png";
	d_ptr->thumbImage = L"theme/slider_thumb.png";
	setDragWidgetFlag( GuiWidget::NotDragWindow );
}

GuiSliderWidget::~GuiSliderWidget( void )
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiSliderWidget::hoverEnterEvent( GuiEvent* msg )
{
	
}

void GuiSliderWidget::hoverLeaveEvent( GuiEvent* msg )
{
	
}

void GuiSliderWidget::mouseLButtonPressEvent( GuiEvent* msg )
{
	d_ptr->bMousePressed = true;
	Point pt = frameWindow()->clientPointFromEvent( msg );
	int w = pt.X - geometry().GetLeft();
	int value  = w*d_ptr->maxValue/fixWidth();
	setCurrentValue( value );
}

void GuiSliderWidget::mouseLButtonReleaseEvent( GuiEvent* msg )
{
	d_ptr->bMousePressed = false;
}

void GuiSliderWidget::paintEvent( GuiPainter* painter )
{
	std::wstring bkImagePath =  guiApp->exePath() + L"/" + d_ptr->backgroundImage; 
	std::wstring thumbImagePath =  guiApp->exePath() + L"/" + d_ptr->thumbImage; 
	Image bkImage( bkImagePath.c_str() );
	Image thumbImage( thumbImagePath.c_str() );
	int leftPos = 0;
	int topPos = 0;

	Rect bkRect;
	leftPos = geometry().GetLeft() + ( fixWidth() - bkImage.GetWidth() )/2;
	leftPos = max( geometry().GetLeft(), leftPos );
	topPos =  geometry().GetTop() + ( fixHeight() - bkImage.GetHeight() )/2;
	bkRect = Rect( leftPos, topPos, bkImage.GetWidth(), bkImage.GetHeight() );

	Rect thumbRect;
	leftPos = geometry().GetLeft() + d_ptr->currentValue*fixWidth()/d_ptr->maxValue;
	leftPos = min( geometry().GetRight() - thumbImage.GetWidth(), leftPos );
	topPos = geometry().GetTop();
	thumbRect = Rect( leftPos, topPos, thumbImage.GetWidth(), thumbImage.GetHeight() );

	painter->drawImage( bkImagePath, bkRect );
	painter->drawImage( thumbImagePath, thumbRect );
}

void GuiSliderWidget::hoverMoveEvent( GuiEvent* msg )
{
	if ( d_ptr->bMousePressed )
	{
		Point pt = frameWindow()->clientPointFromEvent( msg );
		int w = pt.X - geometry().GetLeft();
		int value = w*d_ptr->maxValue/fixWidth();
		setCurrentValue( value );
	}
}

void GuiSliderWidget::construct()
{
	
}

void GuiSliderWidget::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"backgroundImagePath" )
	{
		setBackgroundImagePath( value );
	}
	else if ( name == L"thumbImagePath" )
	{
		setThumbImagePath( value );
	}
	else
	{
		GuiWidget::setAttribute( name, value );
	}
}

void GuiSliderWidget::setBackgroundImagePath( const std::wstring& imagePath )
{
	d_ptr->backgroundImage = imagePath;
}

void GuiSliderWidget::setThumbImagePath( const std::wstring& imagePath )
{
	d_ptr->thumbImage = imagePath;
}

int GuiSliderWidget::currentValue()
{
	return d_ptr->currentValue;
}

void GuiSliderWidget::setCurrentValue( int value )
{
	value = min(value,d_ptr->maxValue);
	d_ptr->currentValue = value;
	update();

	valueChanged();
}

void GuiSliderWidget::setMaxValue( int value )
{
	d_ptr->maxValue = value;
}

int GuiSliderWidget::maxValue()
{
	return d_ptr->maxValue;
}
