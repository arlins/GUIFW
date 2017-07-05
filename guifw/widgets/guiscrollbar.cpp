#include "guiscrollbar.h"
#include "private/guiscrollbar_p.h"
#include "guifw/guiapplication.h"
#include "guifw/guiframewindow.h"
#include "../utility/text/ustring.h"

const int KMinSliderHeight = 30;

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiScrollBar )
GuiScrollBar::GuiScrollBar( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
, d_ptr( new GuiScrollBarPrivate )
{
	d_ptr->backgroundImage = L"theme/scrollbar_background.png";
	d_ptr->thumbImage = L"theme/scrollbar_normal.png";
	setDragWidgetFlag( GuiWidget::NotDragWindow );
}

GuiScrollBar::~GuiScrollBar( void )
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiScrollBar::hoverEnterEvent( GuiEvent* msg )
{
	
}

void GuiScrollBar::hoverLeaveEvent( GuiEvent* msg )
{
	
}

void GuiScrollBar::hoverMoveEvent( GuiEvent* msg )
{
	if ( d_ptr->bMousePressed )
	{
		Point pt = frameWindow()->clientPointFromEvent( msg );
		_updateSlider( pt );
	}
}

void GuiScrollBar::mouseLButtonPressEvent( GuiEvent* msg )
{
	d_ptr->bMousePressed = true;
	Point pt = frameWindow()->clientPointFromEvent( msg );
	_updateSlider( pt );
}

void GuiScrollBar::_updateSlider( const Point& pt )
{
	int h = pt.Y - geometry().GetTop();
	h = max( 0, h );
	int value  = h*d_ptr->maxValue/( fixHeight() -_sliderHeight() );
	setCurrentValue( value );
}

void GuiScrollBar::mouseLButtonReleaseEvent( GuiEvent* msg )
{
	d_ptr->bMousePressed = false;
}

void GuiScrollBar::paintEvent( GuiPainter* painter )
{
	std::wstring bkImagePath =  guiApp->exePath() + L"/" + d_ptr->backgroundImage; 
	std::wstring thumbImagePath =  guiApp->exePath() + L"/" + d_ptr->thumbImage; 
	Image bkImage( bkImagePath.c_str() );
	Image thumbImage( thumbImagePath.c_str() );
	int leftPos = 0;
	int topPos = 0;

	Rect thumbRect;
	int thumbHeight = _sliderHeight();
	topPos = geometry().GetTop() + d_ptr->currentValue*( fixHeight() -_sliderHeight() )/d_ptr->maxValue;
	topPos = min( geometry().GetBottom() - thumbHeight, topPos );
	leftPos = geometry().GetLeft();
	thumbRect = Rect( leftPos, topPos, thumbImage.GetWidth(), thumbHeight );

	painter->drawImage( bkImagePath, geometry() );
	painter->drawNinePiecesImage( thumbRect, thumbImagePath, Rect(0,0,4,4), Rect(6,14,4,4) );
}

void GuiScrollBar::construct()
{
	
}

void GuiScrollBar::setAttribute( std::wstring& name, std::wstring& value )
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

void GuiScrollBar::setBackgroundImagePath( const std::wstring& imagePath )
{
	d_ptr->backgroundImage = imagePath;
}

void GuiScrollBar::setThumbImagePath( const std::wstring& imagePath )
{
	d_ptr->thumbImage = imagePath;
}

int GuiScrollBar::currentValue()
{
	return d_ptr->currentValue;
}

void GuiScrollBar::setCurrentValue( int value )
{
	value = min(value,d_ptr->maxValue);
	d_ptr->currentValue = value;
	update();

	valueChanged();
}

void GuiScrollBar::setMaxValue( int value )
{
	d_ptr->maxValue = value;
}

int GuiScrollBar::maxValue()
{
	return d_ptr->maxValue;
}

int GuiScrollBar::_sliderHeight()
{
	int h = KMinSliderHeight;
	if( d_ptr->maxValue < fixHeight() )
	{
		h = fixHeight() - d_ptr->maxValue;
		h = max( h, KMinSliderHeight );
	}

	return h;
}
