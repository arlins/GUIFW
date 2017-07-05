#include "guiglobal.h"
#include "guifw/guiframewindow.h"
#include "private/guiwidgeteventdispatcher_p.h"
#include "guiwidgeteventdispatcher.h"
#include "guiwidget.h"

//深度遍历整棵树
#define  DispatchEventToWidgets( funname, arg ) \
{ \
	if ( d_ptr->frameWindow != NULL ) \
	{ \
		std::deque<GuiObject*> stackNode; \
		stackNode.push_back( static_cast<GuiObject*>( d_ptr->frameWindow->rootWidget() ) ); \
		while( !stackNode.empty() ) \
		{ \
			GuiObject *pItem=stackNode.back(); \
			stackNode.pop_back(); \
			GuiWidget* itemWidget = static_cast<GuiWidget*> ( pItem ); \
			if ( itemWidget ) \
			{ \
				itemWidget->funname( arg ); \
			} \
			for ( std::list<GuiObject*>::reverse_iterator  it = pItem->getChildren().rbegin(); it != pItem->getChildren().rend(); it++ ) \
			{ \
				stackNode.push_back( *it ); \
			} \
		} \
	} \
}

GuiWidgetEventDispatcher::GuiWidgetEventDispatcher( GuiFrameWindow* frameWindow )
: d_ptr( new GuiWidgetEventDispatcherPrivate )
{
	d_ptr->frameWindow = frameWindow;
}

GuiWidgetEventDispatcher::~GuiWidgetEventDispatcher(void)
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiWidgetEventDispatcher::paintEvent( GuiPainter* painter )
{
	if ( d_ptr->frameWindow == NULL ) 
	{
		return;
	}

	std::deque<GuiObject*> stackNode; 
	stackNode.push_back( static_cast<GuiObject*>( d_ptr->frameWindow->rootWidget() ) ); 
	while( !stackNode.empty() ) 
	{ 
		GuiObject *pItem=stackNode.back(); 
		stackNode.pop_back(); 
		GuiWidget* itemWidget = static_cast<GuiWidget*> ( pItem ); 
		if ( itemWidget && itemWidget->isVisible() ) 
		{ 
			Rect realRect = itemWidget->realShape();
			bool widgetInDirtyRect = ( realRect.Intersect( d_ptr->frameWindow->dirtyRect() ) == TRUE );
			if ( widgetInDirtyRect )
			{
				painter->save();
				painter->setClipRect( realRect, CombineModeReplace );
				itemWidget->paintEvent( painter ); 
				painter->restore();

				std::wstringstream ot;
				ot << __FUNCTIONW__ << L" objName = " << itemWidget->objectName().c_str() << L"\n";
				//::OutputDebugStringW( ot.str().c_str() );
			}
		} 
		for ( std::list<GuiObject*>::reverse_iterator  it = pItem->getChildren().rbegin(); it != pItem->getChildren().rend(); it++ )
		{ 
			stackNode.push_back( *it ); 
		} 
	} 
}

void GuiWidgetEventDispatcher::resizeEvent( GuiEvent* msg )
{
	DispatchEventToWidgets( resizeEvent, msg );
}

void GuiWidgetEventDispatcher::closeEvent( GuiEvent* msg )
{
	DispatchEventToWidgets( closeEvent, msg );
}

void GuiWidgetEventDispatcher::mouseWheelEvent( GuiEvent* msg )
{
	if ( d_ptr->frameWindow == NULL )
	{
		return;
	}

	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* widget = d_ptr->frameWindow->findWidgetByPoint( pt );
	if ( widget )
	{
		widget->mouseWheelEvent( msg );
	}
}

void GuiWidgetEventDispatcher::mouseHoverEvent( GuiEvent* msg )
{
	//do noting
}

void GuiWidgetEventDispatcher::mouseEnterEvent( GuiEvent* msg )
{
	//do noting
}

void GuiWidgetEventDispatcher::mouseLeaveEvent( GuiEvent* msg )
{
	if ( d_ptr->oldHoverWidget )
	{
		d_ptr->oldHoverWidget->hoverLeaveEvent( msg );
		d_ptr->oldHoverWidget = NULL;
	}

	if ( d_ptr->oldClickWidget )
	{
		d_ptr->oldClickWidget = NULL;
	}
}

void GuiWidgetEventDispatcher::mouseMoveEvent( GuiEvent* msg )
{
	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* newHoverWidget = d_ptr->frameWindow->findWidgetByPoint( pt );
	
	if ( newHoverWidget == d_ptr->oldHoverWidget )
	{
		if ( d_ptr->oldHoverWidget )
		{
			d_ptr->oldHoverWidget->hoverMoveEvent( msg );
		}
		if ( d_ptr->oldClickWidget )
		{
			d_ptr->oldClickWidget->hoverMoveEvent( msg );
		}
	}
	
	if ( newHoverWidget != d_ptr->oldHoverWidget )
	{
		if ( d_ptr->oldHoverWidget )
		{
			d_ptr->oldHoverWidget->hoverLeaveEvent( msg );
		}
		if ( newHoverWidget )
		{
			newHoverWidget->hoverEnterEvent( msg );
		}
		d_ptr->oldHoverWidget = newHoverWidget;
	}
}

void GuiWidgetEventDispatcher::mouseLButtonPressEvent( GuiEvent* msg )
{
	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* newClickWidget = d_ptr->frameWindow->findWidgetByPoint( pt );
	if ( newClickWidget != NULL )
	{
		newClickWidget->mouseLButtonPressEvent( msg );
	}
	d_ptr->oldClickWidget = newClickWidget;
}

void GuiWidgetEventDispatcher::mouseLButtonReleaseEvent( GuiEvent* msg )
{
	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* releaseWidget = d_ptr->frameWindow->findWidgetByPoint( pt );
	if ( d_ptr->oldClickWidget == releaseWidget && releaseWidget )
	{
		releaseWidget->mouseLButtonReleaseEvent( msg );
	}

	d_ptr->oldClickWidget = NULL;
}

void GuiWidgetEventDispatcher::mouseMButtonPressEvent( GuiEvent* msg )
{
	//do noting
}

void GuiWidgetEventDispatcher::mouseMButtonReleaseEvent( GuiEvent* msg )
{
	//do noting
}

void GuiWidgetEventDispatcher::mouseRButtonPressEvent( GuiEvent* msg )
{
	//do noting
}

void GuiWidgetEventDispatcher::mouseRButtonReleaseEvent( GuiEvent* msg )
{
	//do noting
}

void GuiWidgetEventDispatcher::mouseMButtonDoubleClickEvent( GuiEvent* msg )
{
	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* widget = d_ptr->frameWindow->findWidgetByPoint( pt );
	if ( widget != NULL )
	{
		widget->mouseMButtonDoubleClickEvent( msg );
	}
}

void GuiWidgetEventDispatcher::mouseLButtonDoubleClickEvent( GuiEvent* msg )
{
	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* widget = d_ptr->frameWindow->findWidgetByPoint( pt );
	if ( widget != NULL )
	{
		widget->mouseLButtonDoubleClickEvent( msg );
	}
}

void GuiWidgetEventDispatcher::mouseRButtonDoubleClickEvent( GuiEvent* msg )
{
	Point pt = d_ptr->frameWindow->clientPointFromEvent( msg );
	GuiWidget* widget = d_ptr->frameWindow->findWidgetByPoint( pt );
	if ( widget != NULL )
	{
		widget->mouseRButtonDoubleClickEvent( msg );
	}
}
