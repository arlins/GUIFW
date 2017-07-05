#include "guiglobal.h"
#include "guiwidgethboxlayout.h"
#include "../guiobject.h"
#include "../guiwidget.h"

GuiWidgetHBoxLayout::GuiWidgetHBoxLayout()
{

}

GuiWidgetHBoxLayout::~GuiWidgetHBoxLayout( )
{

}

void GuiWidgetHBoxLayout::updateLayout( GuiWidget* rootWidget )
{
	if ( rootWidget == NULL )
	{
		return;
	}

	if ( rootWidget->getChildren().size() == 0 )
	{
		return;
	}

	Rect widgetRect = rootWidget->geometry();
	int adjustedWidgetCount = 0;
	int fixWidthCount = 0;
	//获取可变大小的widget个数
	std::list<GuiObject*> children = rootWidget->getChildren();
	for ( std::list<GuiObject*>::iterator it = children.begin(); it != children.end(); it++ )
	{
		GuiWidget* child = static_cast<GuiWidget*>( *it );
		if ( child )
		{
			if ( child->minimizeWidth() != child->maximizeWidth() )
			{
				adjustedWidgetCount ++;
			}
			else
			{
				fixWidthCount += child->fixWidth();
			}
		}
	}

	//设置各个widget的大小
	int leftPos = widgetRect.GetLeft();
	int topPos = widgetRect.GetTop();
	int adjustWidgetWidth = 0;
	if ( adjustedWidgetCount > 0 )
	{
		adjustWidgetWidth = widgetRect.Width > fixWidthCount? ( ( widgetRect.Width - fixWidthCount )/adjustedWidgetCount ):0;
	}

	for ( std::list<GuiObject*>::iterator it = children.begin(); it != children.end(); it++ )
	{
		GuiWidget* child = static_cast<GuiWidget*>( *it );
		if ( child )
		{
			if ( child->minimizeWidth() != child->maximizeWidth() )
			{
				child->setGeometry( Rect( leftPos, topPos, adjustWidgetWidth, widgetRect.Height ) );
				leftPos += adjustWidgetWidth;
			}
			else
			{
				child->setGeometry( Rect( leftPos, topPos, child->fixWidth(), widgetRect.Height ) );
				leftPos += child->fixWidth();
			}
		}
	}
}
