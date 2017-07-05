#pragma once 
#include "guiglobal.h"

class GuiObject;

class GuiObjectPrivate
{
public:
	GuiObjectPrivate();
	virtual ~GuiObjectPrivate();

public:
	GuiObject* parentObject;
	std::wstring objectName;
	std::list<GuiObject*> children;
	static int s_objectNameIndex;
};