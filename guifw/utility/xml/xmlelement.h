#pragma once

#include "guiglobal.h"

class XmlElementPrivate;

namespace pugi
{
	class xml_node;
	class xml_attribute;
}

class XmlAttribute
{
	friend class XmlAttributePrivate;
	friend class XmlElement;
	friend class CXmlNodeHook;
public:
	explicit XmlAttribute();
	XmlAttribute(const XmlAttribute & src);
	~XmlAttribute();

	// Check if attribute is empty
	bool isEmpty() const;

	// Get attribute name/value, or "" if attribute is empty
	const std::wstring name() const;
	const std::wstring value() const;
	void set(std::wstring value);

	XmlAttribute nextAttribute() const;
	XmlAttribute prevAttribute() const;

	XmlAttribute& operator=(const XmlAttribute & src);
private:
	XmlAttribute(pugi::xml_attribute attr);
	XmlAttributePrivate	*d_ptr;
};

class XmlElement
{
	friend class XmlElementPrivate;
	friend class XmlDocument;
	friend class CXmlNodeHook;
public:
	explicit XmlElement(const std::wstring &name);
	~XmlElement();

	std::wstring tag() const;
	std::wstring text() const;
	void setText(const std::wstring& text);

	int childCount() const;
	const XmlElement *child(int index) const;
	void addChild(XmlElement *child);
	int attributeCount() const;

	std::wstring attribute( const std::wstring &attrName ) const;
	std::wstring attribute( int index ) const;
	std::wstring attributeName( int index ) const;
	void setAttribute(const std::wstring &attrName, const std::wstring &attrValue);
	void removeAttribute(const std::wstring &attrName);

	const XmlElement *operator[](int index) const;
	std::wstring operator[](const std::wstring &attrName) const;

	void deleteChild(const XmlElement *child);

	XmlElement *elementByName(const std::wstring &name) const;

public:
	bool isEmpty() const;
	
	typedef bool (__stdcall *PCB_XMLTRAVERSE)(const XmlElement *node, void* pContext);
	void traverse( PCB_XMLTRAVERSE fnTraverse,void *pCtx =NULL);
	bool saveToStream( std::wstring &xmlStream ) const;

	XmlElement * addChild(const std::wstring & str);
	XmlAttribute attr(const std::wstring &attrName) const;
	XmlAttribute firstAttr() const;
	XmlAttribute lastAttr() const;
	XmlAttribute appendAttr(const std::wstring & name);
	XmlAttribute prependAttr(const std::wstring & name);
	XmlAttribute insertAttrAfter(const std::wstring & name, const XmlAttribute& attr);
	XmlAttribute insertAttrBefore(const std::wstring & name, const XmlAttribute& attr);

protected:

	XmlElement(const pugi::xml_node & xmlNode);
	
	XmlElementPrivate	*d_ptr;
};
