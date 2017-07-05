#include "guiglobal.h"
#include "guiscrollwidget.h"
#include "private/guiscrollwidget_p.h"
#include "guifw/guiapplication.h"
#include "guifw/guiframewindow.h"

int KScrollBarWidth = 11;
const wchar_t KScrollBarObjectName[] = L"ScrollWidget_ScrollBar";

GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( GuiScrollWidget )
GuiScrollWidget::GuiScrollWidget( GuiWidget* parent /*= NULL */ )
: GuiWidget( parent )
, d_ptr( new GuiScrollWidgetPrivate )
{
	setLayout( GuiWidget::NoLayout );
	setClipFlag( GuiWidget::ChildrenClipToShape );
	setDragWidgetFlag( GuiWidget::NotDragWindow );	
}

GuiScrollWidget::~GuiScrollWidget( void )
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiScrollWidget::construct()
{
	d_ptr->scrollBar = new GuiScrollBar( this );
	d_ptr->scrollBar->setObjectName( KScrollBarObjectName );
	d_ptr->scrollBar->setGuiFrameWindow( frameWindow() );
	xsignals_helper::sig_connect( d_ptr->scrollBar->valueChanged, this , &GuiScrollWidget::on_scrollBar_valueChanged);
}

void GuiScrollWidget::paintEvent( GuiPainter* painter )
{
	SolidBrush brush( backgroundColor() );
	painter->fillRect( &brush, geometry() );
}

void GuiScrollWidget::resizeEvent( GuiEvent* msg )
{
	_layout();
}

void GuiScrollWidget::_layout()
{
	if ( getChildren().size() != 2 )
	{
		assert( false );
		return;
	}

	GuiWidget* contentWidget = _contentWidget();

	if ( contentWidget )
	{
		contentWidget->setFixedWidth( fixWidth() );
		if ( contentWidget->fixHeight() <= fixHeight() )
		{
			Rect itemRc;
			itemRc.X = geometry().X;
			itemRc.Y = geometry().Y;
			itemRc.Width = geometry().Width;
			itemRc.Height = contentWidget->fixHeight();
			contentWidget->setGeometry( itemRc );
			d_ptr->scrollBar->setVisible( d_ptr->scrollBarPolicy == GuiScrollWidget::ScrollBarAlwaysOn );
		}
		else
		{
			d_ptr->scrollBar->setVisible( !(d_ptr->scrollBarPolicy == GuiScrollWidget::ScrollBarAlwaysOff) );
			Rect scrollBarRect;
			scrollBarRect.X = geometry().GetRight() - KScrollBarWidth;
			scrollBarRect.Y = geometry().GetTop();
			scrollBarRect.Width = KScrollBarWidth;
			scrollBarRect.Height = fixHeight();
			d_ptr->scrollBar->setGeometry( scrollBarRect );
			int maxValue = contentWidget->fixHeight() - fixHeight();
			int currentValue = maxValue*d_ptr->scrollBar->currentValue()/d_ptr->scrollBar->maxValue();
			d_ptr->scrollBar->setMaxValue( maxValue );
			d_ptr->scrollBar->setCurrentValue( currentValue );
		}
	}
}

void GuiScrollWidget::on_scrollBar_valueChanged()
{
	_scroll();
}

void GuiScrollWidget::_scroll()
{
	GuiWidget* contentWidget = _contentWidget();
	int currentValue = d_ptr->scrollBar->currentValue();
	Point pt;
	pt.X = geometry().GetLeft();
	pt.Y = geometry().GetTop() - currentValue;
	contentWidget->setPosition( pt );
	update();
}

void GuiScrollWidget::setScrollBarPolicy( ScrollBarPolicy policy )
{
	d_ptr->scrollBarPolicy = policy;
}

GuiScrollWidget::ScrollBarPolicy GuiScrollWidget::scrollBarPolicy() const
{
	return d_ptr->scrollBarPolicy;
}

void GuiScrollWidget::setScrollPos( int pos )
{
	GuiWidget* contentWidget = _contentWidget();
	if ( contentWidget && contentWidget->fixHeight() > fixHeight() )
	{
		d_ptr->scrollBar->setCurrentValue( pos );
		update();
	}
}

int GuiScrollWidget::scrollPos()
{
	return 0;
}

GuiWidget* GuiScrollWidget::_contentWidget()
{
	GuiWidget* item = NULL;
	for ( std::list<GuiObject*>::iterator it = getChildren().begin(); it != getChildren().end(); it++ )
	{
		if ( *it != d_ptr->scrollBar )
		{
			item = static_cast<GuiWidget*>(*it);
			break;
		}
	}

	return item;
}
