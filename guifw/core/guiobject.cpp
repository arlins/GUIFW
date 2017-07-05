#include "guiglobal.h"
#include "guiobject.h"
#include "private/guiobject_p.h"

GuiObject::GuiObject( GuiObject* parent )
: d_ptr( new GuiObjectPrivate() )
{
	setParent( parent );
}

GuiObject::~GuiObject()
{
	xsignals_helper::free_all_slots_of( this );
	std::list<GuiObject*>::iterator it = d_ptr->children.begin();
	while( it != d_ptr->children.end() )
	{
		GuiObject* item = *it;
		delete item; 
		it = d_ptr->children.erase( it );
	}

	Gui_SAFE_DELETE( d_ptr );
}

void GuiObject::setObjectName( const std::wstring& name )
{
	d_ptr->objectName = name;
}

std::wstring GuiObject::objectName()
{
	return d_ptr->objectName;
}

GuiObject* GuiObject::parent()
{
	return d_ptr->parentObject;
}

void GuiObject::setParent( GuiObject* parent )
{
	if ( d_ptr->parentObject != NULL )
	{
		d_ptr->parentObject->removeChild( this );
	}

	d_ptr->parentObject = parent;
	if ( d_ptr->parentObject )
	{
		d_ptr->parentObject->addChild( this );
	}
}

std::list<GuiObject*>& GuiObject::getChildren()
{
	return d_ptr->children;
}

void GuiObject::addChild( GuiObject* child )
{
	bool bChildExist = false;
	std::list<GuiObject*>::iterator it = d_ptr->children.begin();
	for ( ; it != d_ptr->children.end(); it++ )
	{
		if ( (*it)->objectName() == child->objectName() )
		{
			bChildExist = true;
			break;
		}
	}

	if ( !bChildExist )
	{
		d_ptr->children.push_back( child );
	}
}

void GuiObject::removeChild( GuiObject* child )
{
	std::list<GuiObject*>::iterator it = d_ptr->children.begin();
	for ( ; it != d_ptr->children.end(); it++ )
	{
		if ( (*it)->objectName() == child->objectName() )
		{
			d_ptr->children.erase( it );
			return;
		}
	}
}

void GuiObject::setAttribute( std::wstring& name, std::wstring& value )
{
	if ( name == L"objectName" )
	{
		setObjectName( value );
	}
	else
	{
		assert( false );
	}
}

GuiObject* GuiObject::findChild( const std::wstring& objectName )
{
	std::deque<GuiObject*> dequeNode;
	dequeNode.push_back( this );
	while(!dequeNode.empty())
	{
		GuiObject *pItem=dequeNode.front();
		dequeNode.pop_front();
		if ( pItem && pItem->objectName() == objectName )
		{
			return pItem;
		}

		for ( std::list<GuiObject*>::iterator it = pItem->getChildren().begin(); it != pItem->getChildren().end(); it++ )
		{
			dequeNode.push_back( *it );
		}
	}

	return NULL;
}

void GuiObject::deleteLater()
{
	
}