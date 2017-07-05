#include "guiglobal.h"
#include "guiwidgetvboxlayout.h"

GuiWidgetVBoxLayout::GuiWidgetVBoxLayout(  )
{

}

GuiWidgetVBoxLayout::~GuiWidgetVBoxLayout( )
{
	
}

void GuiWidgetVBoxLayout::updateLayout( GuiWidget* rootWidget )
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
	int fixHeightCount = 0;

	//获取可变大小的widget个数
	std::list<GuiObject*> children = rootWidget->getChildren();
	for ( std::list<GuiObject*>::iterator it = children.begin(); it != children.end(); it++ )
	{
		GuiWidget* child = static_cast<GuiWidget*>( *it );
		if ( child )
		{
			if ( child->minimizeHeight() != child->maximizeHeight() )
			{
				adjustedWidgetCount ++;
			}
			else
			{
				fixHeightCount += child->fixHeight();
			}
		}
	}

	int leftPos = widgetRect.GetLeft();
	int topPos = widgetRect.GetTop();
	int adjustWidgetHeight = 0;
	if ( adjustedWidgetCount > 0 )
	{
		adjustWidgetHeight = widgetRect.Height > fixHeightCount? ( ( widgetRect.Height - fixHeightCount )/adjustedWidgetCount ):0; 
	}

	//设置各个widget的大小
	for ( std::list<GuiObject*>::iterator it = children.begin(); it != children.end(); it++ )
	{
		GuiWidget* child = static_cast<GuiWidget*>( *it );
		if ( child )
		{
			if ( child->minimizeHeight() != child->maximizeHeight() )
			{
				child->setGeometry( Rect( leftPos, topPos, widgetRect.Width ,adjustWidgetHeight ) );
				topPos += adjustWidgetHeight;
			}
			else
			{
				child->setGeometry( Rect( leftPos, topPos, widgetRect.Width, child->fixHeight() ) );
				topPos += child->fixHeight();
			}
		}
	}
}
