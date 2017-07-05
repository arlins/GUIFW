#include "guiwidget_p.h"
#include <limits.h>

GuiWidgetPrivate::GuiWidgetPrivate()
: frameWindow( NULL )
, bVisible( true )
, bEnableDrag( true )
, dragWidgetFlag( GuiWidget::DragWithParentFlag )
, backgroundColor( 0, 0, 0, 0 )
, minimizeSize( 0, 0 )
, maximizeSize( INT_MAX, INT_MAX ) 
, geometry( 0, 0, 0, 0 )
, layoutType( GuiWidget::HBox )
, xmlPath( L"" )
, clipFlag( GuiWidget::ClipNone )
{

}

GuiWidgetPrivate::~GuiWidgetPrivate()
{
	
}
