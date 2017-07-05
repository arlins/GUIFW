//#include "Markup.h"

#include "../text/ustring.h"

#include "xmldocument.h"
#include "xmlelement.h"
#include "pugixml/pugixml.hpp"
using namespace pugi;


class NodeFilterWalker : public xml_tree_walker
{
public:
	NodeFilterWalker(XmlDocument::PFN_XMLFILTER pFn,void *pCtx):m_pFnFilter(pFn),m_pCtx(pCtx)
	{

	}
	virtual bool for_each(xml_node& node)
	{
		if(m_pFnFilter(XmlDocument::XmlElement_tag,node.name(),NULL,m_pCtx)) return false;
		xml_attribute attr=node.first_attribute();
		while(attr)
		{
			if(m_pFnFilter(XmlDocument::XmlElement_attr,attr.name(),attr.value(),m_pCtx)) return false;
			attr=attr.next_attribute();
		}
		return true;
	}
private:
	XmlDocument::PFN_XMLFILTER m_pFnFilter;
	void	*     m_pCtx;
};


XmlDocument::XmlDocument()
: m_pXmlDoc(new xml_document),m_filterContext(0),m_pFnFilter(0)
{
}


XmlDocument::~XmlDocument(void)
{
	delete m_pXmlDoc;
}


void XmlDocument::doNodeTraverse()
{
	if(m_pFnFilter)
	{
		NodeFilterWalker walker(m_pFnFilter,m_filterContext);
		m_pXmlDoc->traverse(walker);
	}
}

bool XmlDocument::loadFromFile( const std::wstring &xmlFile )
{
	bool bret = m_pXmlDoc->load_file(xmlFile.c_str());
	if(!bret || !m_pXmlDoc->first_child()) return false;
	doNodeTraverse();
	return true;
}

bool XmlDocument::loadFromString( const std::wstring &xmlString )
{
	bool bret =  m_pXmlDoc->load(xmlString.c_str());
	if(!bret || !m_pXmlDoc->first_child()) return false;
	doNodeTraverse();
	return true;
}

bool XmlDocument::loadFromString( const char *content, int lenght )
{
	if (isUtf8(content, lenght))
	{
		return loadFromString(Utility::text::toWideString(content + 3, lenght - 3, CP_UTF8));
	}
	if (isUtf16(content, lenght))
	{
		if (1 == (lenght & 1))
		{
			_ASSERT(false);
			return false;
		}
		std::wstring stream;
		stream.assign((wchar_t*)(content + 2), (lenght - 2) / 2);
		return loadFromString(stream);
	}
	return loadFromString(Utility::text::toWideString(content, lenght, CP_UTF8));
}


const XmlElement* XmlDocument::elementByPath( const std::wstring &elementPath ) const
{
	xml_node xmlNode= m_pXmlDoc->first_element_by_path(elementPath.c_str());
	if(!xmlNode) return NULL;
	return (XmlElement *)xmlNode.get_user_data();
}

XmlElement * XmlDocument::createElementByPath( const std::wstring &elementPath )
{
	std::vector<std::wstring> vectorElement;
	Utility::text::splitWString(elementPath, _T("/"), vectorElement);

	if (vectorElement.size() < 1)
	{
		//Path must have root,exmaple: root/subPath/thirdPath
		return NULL;
	}

	xml_node xmlNode=m_pXmlDoc->first_child();

	if (xmlNode.name() != vectorElement[0])
	{
		if(xmlNode)
		{
			//Xml only one root. Please use proper root.
			//you must do with this assert, It's very dangerous!!!!!
			m_pXmlDoc->reset();
		}
		xml_node root=m_pXmlDoc->append_child(vectorElement[0].c_str());
	}
	vectorElement.erase(vectorElement.begin());

	xmlNode=m_pXmlDoc->first_child();

	if(xmlNode)
	{
		XmlElement *currentElement = (XmlElement *)xmlNode.get_user_data();

		for (std::vector<std::wstring>::iterator iter = vectorElement.begin();
			vectorElement.end() != iter;
			++iter)
		{
			XmlElement *tempElement = currentElement->elementByName(*iter);
			if (!tempElement)
			{
				tempElement = currentElement->addChild(*iter);
			}
			currentElement = tempElement;
		}
		return currentElement;
	}else
	{
		_ASSERT(false);
		return NULL;
	}
}

std::wstring XmlDocument::query( const std::wstring &valuePath ) const
{
	std::vector<std::wstring> vectorElement;
	Utility::text::splitWString(valuePath, _T(":"), vectorElement);
	if (vectorElement.empty())
	{
		return std::wstring();
	}

	const XmlElement *currentElement = elementByPath(vectorElement[0]);
	if (!currentElement)
	{
		return std::wstring();
	}

	if (vectorElement.size() > 1)
	{
		return currentElement->attribute(vectorElement[1]);
	}
	else
	{
		return currentElement->text();
	}
}

bool XmlDocument::isUtf8( const char *content, int lenght )
{
	if (lenght > 3)
	{
		return 0xef == content[0] && 0xbb == content[1] && 0xbf == content[2];
	}
	return false;
}

bool XmlDocument::isUtf16( const char *content, int lenght )
{
	if (lenght > 2)
	{
		return 0xff == content[0] && 0xfe == content[1];
	}
	return false;
}

const XmlElement * XmlDocument::rootElement() const
{
	return (XmlElement*)(m_pXmlDoc->first_child().get_user_data());
}

bool XmlDocument::setValue( const std::wstring &valuePath, const std::wstring &value )
{
	std::vector<std::wstring> vectorElement;
	Utility::text::splitWString(valuePath, _T(":"), vectorElement);

	if (vectorElement.empty())
	{
		return false;
	}

	XmlElement *currentElement = createElementByPath(vectorElement[0]);
	if (!currentElement)
	{
		return false;
	}

	if (vectorElement.size() > 1)
	{
		currentElement->setAttribute(vectorElement[1], value);
	}
	else
	{
		currentElement->setText( value );
	}

	return true;
}

bool XmlDocument::saveToFile( const std::wstring &xmlFile )
{
	return m_pXmlDoc->save_file(xmlFile.c_str(),L"\t",format_default|format_write_bom,encoding_utf8);
}

bool XmlDocument::saveToStream( std::wstring &xmlStream )
{
	xmlStream.clear();
	xml_writer_string write(xmlStream);

	xmlStream=L"<?xml version=\"1.0\"?>\n";	//强制加入XML声明
	m_pXmlDoc->print(write,L"\t",format_default|format_no_declaration,encoding_utf16);
	return true;
}

bool XmlDocument::isValid() const
{
	return m_pXmlDoc->root()?true:false;
}

void XmlDocument::setXmlFilter( PFN_XMLFILTER pFnFilter, void* filterContext )
{
	m_pFnFilter=pFnFilter;
	m_filterContext=filterContext;
}

bool saveToWString( const XmlElement *element, std::wstring& xmlStream )
{
	return element->saveToStream(xmlStream);
}
