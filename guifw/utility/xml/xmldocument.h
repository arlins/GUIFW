#pragma once

#include "guiglobal.h"
#include "xmlelement.h"
#include <set>

namespace pugi
{
	class xml_document;
}

class XmlDocument
{
public:
	enum XmlElementType 
	{
		XmlElement_tag,
		XmlElement_attr,
	};

	typedef bool (__stdcall *PFN_XMLFILTER)(XmlElementType type, LPCWSTR name, LPCWSTR value, void* filterContext);

public:
	explicit XmlDocument();
	~XmlDocument(void);

public:
	bool loadFromFile( const std::wstring &xmlFile);
	bool loadFromString( const std::wstring &xmlString );
	bool loadFromString( const char *content, int lenght );


	void setXmlFilter(PFN_XMLFILTER pFnFilter, void* filterContext);
	
	const XmlElement *elementByPath( const std::wstring &elementPath ) const;
	std::wstring query( const std::wstring &valuePath ) const;
	bool setValue( const std::wstring &valuePath, const std::wstring &value );

	const XmlElement *rootElement() const;

	bool saveToFile(const std::wstring &xmlFile);
	bool saveToStream(std::wstring &xmlStream);

	bool isValid() const;
	XmlElement *createElementByPath( const std::wstring &elementPath );
	
private:
	bool isUtf8( const char *content, int lenght );
	bool isUtf16( const char *content, int lenght );

	void doNodeTraverse();

private:
	pugi::xml_document *m_pXmlDoc;
	PFN_XMLFILTER m_pFnFilter;
	void* m_filterContext;
};

bool saveToWString(const XmlElement *element, std::wstring& xmlStream);
