#include "guiglobal.h"
#include "guifw/guiobject.h"
#include "guiobject_p.h"

int GuiObjectPrivate::s_objectNameIndex = 0;

GuiObjectPrivate::GuiObjectPrivate()
: parentObject( NULL )
, objectName( L"" )
{
	s_objectNameIndex ++;
	std::wstringstream preObjectName;
	preObjectName << "pre_objectname_index_" << s_objectNameIndex;
	objectName = preObjectName.str();
}

GuiObjectPrivate::~GuiObjectPrivate()
{

}