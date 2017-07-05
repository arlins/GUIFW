#pragma once 
#include "guiglobal.h"

class GuiObjectPrivate;

class GUIFW_DECL_EXPORT GuiObject : public xsignals::trackable 
{
public:
	explicit GuiObject( GuiObject* parent = NULL );
	virtual ~GuiObject();

	void deleteLater();

	std::wstring objectName();
	void setObjectName( const std::wstring& name );

	void setParent( GuiObject* parent );
	GuiObject* parent();

	GuiObject* findChild( const std::wstring& objectName );
	std::list<GuiObject*>& getChildren();

	void addChild( GuiObject* child );
	void removeChild( GuiObject* child );
		
	virtual void setAttribute( std::wstring& name, std::wstring& value );

protected:
	GuiObjectPrivate* d_ptr;
};