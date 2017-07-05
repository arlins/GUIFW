#include "xmlelement.h"
#include "pugixml/pugixml.hpp"
using namespace pugi;
#pragma warning(disable:4355)//关闭在构造函数是使用this的警告

//////////////////////////////////////////////////////////////////////////

class XmlElementPrivate
{
public:
	XmlElementPrivate(xml_node _xmlNode):xmlNode(_xmlNode),bManagered(true){}
	XmlElementPrivate(const std::wstring &strName,XmlElement *pEle):bManagered(false)
	{
		xmlNode=xmlDoc.append_child(strName.c_str());
		XmlElement *pEle2=(XmlElement *)xmlNode.get_user_data();
		delete pEle2;
		xmlNode.set_user_data(pEle);
	}

	~XmlElementPrivate(){}

	xml_node	xmlNode;
	xml_document xmlDoc;
	std::vector<XmlElement *> m_childs;	//子节点指针列表
	std::vector<XmlAttribute> m_attrs;	//节点属性列表,用于原有接口提供属性的随机索引
	bool		bManagered;					//结点是由调用都创建的。
};

class XmlAttributePrivate
{
public:
	XmlAttributePrivate(xml_attribute attr):xmlAttr(attr)
	{

	}

	XmlAttributePrivate(){}

	xml_attribute xmlAttr;
};

class CXmlNodeHook : public xml_node_hook
{
public:
	CXmlNodeHook()
	{
	}

	void onNodeCreate(xml_node node)
	{
		XmlElement *pEle=new XmlElement(node);
		node.set_user_data(pEle);
		xml_node parent=node.parent();
		if(parent && (parent.type() == node_element))
		{
			XmlElement *pParent=(XmlElement*)parent.get_user_data();
			pParent->d_ptr->m_childs.push_back(pEle);
		}
	}

	void onNodeDestory(xml_node node)
	{
		XmlElement *pEle = (XmlElement *)node.get_user_data();
		xml_node parent=node.parent();
		if(parent && (parent.type() == node_element))
		{
			XmlElement *pParent=(XmlElement*)parent.get_user_data();
			std::vector<XmlElement*>::iterator it=pParent->d_ptr->m_childs.begin();
			while(it!=pParent->d_ptr->m_childs.end())
			{
				if(*it == pEle)
				{
					pParent->d_ptr->m_childs.erase(it);
					break;
				}
				it++;
			}
		}
		if(pEle->d_ptr->bManagered) 
			delete pEle;//内部分配的节点才能自己删除
	}

	virtual void onFreeUserData(xml_node node)	//document destroy释放时调用
	{
		XmlElement *pEle = (XmlElement *)node.get_user_data();
		if(pEle && pEle->d_ptr->bManagered) delete pEle;
	}

	void onAttrCreate(xml_node node,xml_attribute attr)
	{
		XmlElement *pEle = (XmlElement *)node.get_user_data();
		pEle->d_ptr->m_attrs.push_back(XmlAttribute(attr));
	}

	void onAttrDestroy(xml_node node,xml_attribute attr)
	{
		XmlElement *pEle = (XmlElement *)node.get_user_data();
		std::vector<XmlAttribute>::iterator it=pEle->d_ptr->m_attrs.begin();

		while(it!=pEle->d_ptr->m_attrs.end())
		{
			if(it->d_ptr->xmlAttr == attr)
			{
				pEle->d_ptr->m_attrs.erase(it);
				break;
			}
			it++;
		}
	}

}xmlHook;

namespace pugi
{
	xml_node_hook * g_pNodeHook=&xmlHook;
}

//////////////////////////////////////////////////////////////////////////
XmlElement::XmlElement(const pugi::xml_node &xmlNode ): d_ptr(new XmlElementPrivate(xmlNode))
{
}

XmlElement::XmlElement( const std::wstring &name ) : d_ptr(new XmlElementPrivate(name,this))
{

}

XmlElement::~XmlElement()
{
	delete d_ptr;
	d_ptr = NULL;
}

std::wstring XmlElement::tag() const
{
	return d_ptr->xmlNode.name();
}

std::wstring XmlElement::text() const
{
	return d_ptr->xmlNode.text().get();
}

void XmlElement::setText( const std::wstring& text )
{
	d_ptr->xmlNode.text().set(text.c_str());
}

int XmlElement::childCount() const
{
	return d_ptr->m_childs.size();
}

const XmlElement* XmlElement::child( int index ) const
{
	if(index<0 || index>=(int)d_ptr->m_childs.size())
		return NULL;
	return d_ptr->m_childs[index];
}

XmlElement * XmlElement::addChild(const std::wstring & str)
{
	xml_node added=d_ptr->xmlNode.append_child(str.c_str());
	if(added)
	{
		return (XmlElement *)added.get_user_data();
	}else
	{
		return NULL;
	}
}

//
void XmlElement::addChild( XmlElement *child )
{
	xml_node source = child->d_ptr->xmlNode;
	xml_node dest=d_ptr->xmlNode.append_child(source.name());

	XmlElement * pXmlDest = (XmlElement *)dest.get_user_data();
	d_ptr->m_childs.pop_back();
	d_ptr->m_childs.push_back(child);

	//copy value
	dest.text().set(source.text().get());

	//copy attributes
	for (xml_attribute a = source.first_attribute(); a; a = a.next_attribute())
		dest.append_attribute(a.name()).set_value(a.value());

	dest.set_user_data(child);
	child->d_ptr->xmlNode = dest;
	child->d_ptr->m_attrs = pXmlDest->d_ptr->m_attrs;
	child->d_ptr->bManagered = true;//将结点的属性设置为接受doc管理

	delete pXmlDest;
	source.set_user_data(NULL);

	//深度优先递归插入新child树上的结点
	std::vector<XmlElement*> childs=child->d_ptr->m_childs;
	child->d_ptr->m_childs.clear();
	for(UINT i=0;i<childs.size();i++)
	{
		XmlElement *  p=childs[i];
		child->addChild(p);
	}
	child->d_ptr->xmlDoc.reset();
}

std::wstring XmlElement::attribute( const std::wstring &attrName ) const
{
	return d_ptr->xmlNode.attribute(attrName.c_str()).value();
}

std::wstring XmlElement::attribute( int index ) const
{
	if(index<0 || index>= (int)d_ptr->m_attrs.size()) return L"";
	return d_ptr->m_attrs[index].value();
}

std::wstring XmlElement::attributeName( int index ) const
{
	if(index<0 || index>= (int)d_ptr->m_attrs.size()) return L"";
	return d_ptr->m_attrs[index].name();
}

void XmlElement::setAttribute( const std::wstring &attrName, const std::wstring &attrValue )
{
	xml_attribute attr=d_ptr->xmlNode.attribute(attrName.c_str());
	if(!attr) attr=d_ptr->xmlNode.append_attribute(attrName.c_str());
	attr.set_value(attrValue.c_str());
}

void XmlElement::removeAttribute(const std::wstring &attrName)
{
	d_ptr->xmlNode.remove_attribute(attrName.c_str());
}

XmlElement * XmlElement::elementByName( const std::wstring &name ) const
{
	return (XmlElement*)(d_ptr->xmlNode.child(name.c_str()).get_user_data());
}

std::wstring XmlElement::operator[]( const std::wstring &attrName ) const
{
	return attribute(attrName);
}

const XmlElement* XmlElement::operator[]( int index ) const
{
	return child(index);
}


int XmlElement::attributeCount() const
{
	return d_ptr->m_attrs.size();
}

void XmlElement::deleteChild(const XmlElement *child)
{
	if(!child) return;
	xml_node node=child->d_ptr->xmlNode;
	d_ptr->xmlNode.remove_child(node);
}

bool XmlElement::isEmpty() const
{
	return d_ptr->xmlNode?false:true;
}


class XmlNodeWalker: public xml_tree_walker
{
public:
	XmlNodeWalker(XmlElement::PCB_XMLTRAVERSE _fnCB,void * _pCtx):fnCb(_fnCB),pCtx(_pCtx)
	{
	}
protected:
	virtual bool for_each(xml_node& node){
		if(!fnCb) return false;
		return fnCb((XmlElement *)(node.get_user_data()),pCtx);
	}

	XmlElement::PCB_XMLTRAVERSE fnCb;
	void	*pCtx;
};


void XmlElement::traverse( PCB_XMLTRAVERSE fnTraverse,void *pCtx )
{
	XmlNodeWalker walker(fnTraverse,pCtx);
	d_ptr->xmlNode.traverse(walker);
}

bool XmlElement::saveToStream( std::wstring &xmlStream ) const
{
	xmlStream.clear();
	xml_writer_string write(xmlStream);
	xmlStream=L"<?xml version=\"1.0\"?>\n";	//强制加入XML声明
	d_ptr->xmlNode.print(write,L"\t",format_default|format_no_declaration,encoding_utf16);
	return true;
}

XmlAttribute XmlElement::attr( const std::wstring &attrName ) const
{
	return XmlAttribute(d_ptr->xmlNode.attribute(attrName.c_str()));	
}

XmlAttribute XmlElement::firstAttr() const
{
	return XmlAttribute(d_ptr->xmlNode.first_attribute());
}

XmlAttribute XmlElement::lastAttr() const
{
	return XmlAttribute(d_ptr->xmlNode.last_attribute());
}

XmlAttribute XmlElement::appendAttr( const std::wstring & name )
{
	return XmlAttribute(d_ptr->xmlNode.append_attribute(name.c_str()));
}

XmlAttribute XmlElement::prependAttr( const std::wstring & name )
{
	return XmlAttribute(d_ptr->xmlNode.prepend_attribute(name.c_str()));
}

XmlAttribute XmlElement::insertAttrAfter( const std::wstring & name, const XmlAttribute& attr )
{
	return XmlAttribute(d_ptr->xmlNode.insert_attribute_after(name.c_str(),attr.d_ptr->xmlAttr));
}

XmlAttribute XmlElement::insertAttrBefore( const std::wstring & name, const XmlAttribute& attr )
{
	return XmlAttribute(d_ptr->xmlNode.insert_attribute_before(name.c_str(),attr.d_ptr->xmlAttr));
}

//////////////////////////////////////////////////////////////////////////

XmlAttribute::XmlAttribute():d_ptr(new XmlAttributePrivate)
{

}

XmlAttribute::XmlAttribute( pugi::xml_attribute attr ):d_ptr(new XmlAttributePrivate(attr))
{

}

XmlAttribute::XmlAttribute( const XmlAttribute & src ):d_ptr(new XmlAttributePrivate(src.d_ptr->xmlAttr))
{
	
}

XmlAttribute::~XmlAttribute()
{
	delete d_ptr;
}

bool XmlAttribute::isEmpty() const
{
	return d_ptr->xmlAttr.empty();
}

const std::wstring XmlAttribute::name() const
{
	return d_ptr->xmlAttr.name();
}

const std::wstring XmlAttribute::value() const
{
	return d_ptr->xmlAttr.value();
}

XmlAttribute XmlAttribute::nextAttribute() const
{
	return 	XmlAttribute(d_ptr->xmlAttr.next_attribute());
}

XmlAttribute XmlAttribute::prevAttribute() const
{
	return 	XmlAttribute(d_ptr->xmlAttr.previous_attribute());
}

void XmlAttribute::set( std::wstring value )
{
	d_ptr->xmlAttr.set_value(value.c_str());
}

XmlAttribute& XmlAttribute::operator=( const XmlAttribute & src )
{
	d_ptr->xmlAttr=src.d_ptr->xmlAttr;
	return *this;
}
