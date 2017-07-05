#include "guiglobal.h"
#include "guixmlui.h"
#include "../utility/xml/xmlelement.h"
#include "../utility/xml/xmldocument.h"
#include "../utility/text/ustring.h"
#include "guifw/guiframewindow.h"
#include "guifw/guiwidget.h"
#include "guifw/guiapplication.h"

GuiFrameWindow* GuiXmlUI::createFromFile( const std::wstring& fileName, const std::wstring& rootPath, GuiFrameWindow *parent )
{
	std::wstring fixRootPath = rootPath;
	if ( fixRootPath.empty() )
	{
		fixRootPath = guiApp->exePath();
	}

	XmlDocument xml;
	std::wstring filePath = fixRootPath + L"/"+ fileName;
	if( !xml.loadFromFile( filePath ) )
	{
		return NULL;
	}

	const XmlElement *child = xml.elementByPath(_T("xmlui"));
	if ( NULL == child )
	{
		return NULL;
	}

	child = child->child(0);
	if ( NULL == child )
	{
		return NULL;
	}

	std::wstring className = child->tag();
	if (className.empty())
	{
		return NULL;
	}

	//1、创建Frame
	GuiFrameWindow* frame = GuiDynamicFrameList::createObject(className, parent);
	if (frame == NULL)
	{
		return NULL;
	}

	//2、设置Frame属性
	for ( int i = 0; i < child->attributeCount(); i++ )
	{
		std::wstring wideName = child->attributeName( i );
		std::wstring wideValue = child->attribute( i );
		frame->setAttribute( wideName, wideValue );
	}

	//3、创建widget
	int count = child->childCount();
	for (int index = 0; index < count; ++index)
	{
		createChild(child->child(index), frame->rootWidget(), frame );
	}

	//二次构造
	frame->doConstruct();

	return frame;
}

bool GuiXmlUI::createFromFile( const std::wstring& fileName, const std::wstring& rootPath, GuiWidget* parent )
{
	std::wstring fixRootPath = rootPath;
	if ( fixRootPath.empty() )
	{
		fixRootPath = guiApp->exePath();
	}

	XmlDocument xml;
	std::wstring filePath = fixRootPath + L"/"+ fileName;

	if( !xml.loadFromFile( filePath ) )
	{
		return false;
	}

	const XmlElement *child = xml.elementByPath(_T("xmlui"));

	if ( NULL == child )
	{
		return false;
	}

	int count = child->childCount();
	for (int index = 0; index < count; ++index)
	{
		createChild( child->child(index), parent, parent->frameWindow() );
	}

	 return true;
}

bool GuiXmlUI::createChild( const XmlElement *child, GuiWidget *parent, GuiFrameWindow* frameWindow )
{
	std::wstring className = child->tag();
	GuiWidget *layoutObj = GuiDynamicWidgetList::createObject( className, parent );

	layoutObj->setGuiFrameWindow( frameWindow );
	layoutObj->setParent( parent );
	
	for ( int i = 0; i < child->attributeCount(); i++ )
	{
		std::wstring wideName = child->attributeName( i );
		std::wstring wideValue = child->attribute( i );
		layoutObj->setAttribute( wideName, wideValue );
	}

	int count = child->childCount();
	for (int index = 0; index < count; ++index)
	{
		createChild( child->child(index), layoutObj, frameWindow );
	}

	layoutObj->doConstruct();
	return true;
}

