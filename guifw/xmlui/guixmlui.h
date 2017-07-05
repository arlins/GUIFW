#pragma once 
#include "guiglobal.h"

class GuiObject;
class GuiWidget;
class GuiFrameWindow;
class XmlElement;

class GuiXmlUI
{
public:
	static GUIFW_DECL_EXPORT bool createFromFile(const std::wstring& fileName, const std::wstring& rootPath, GuiWidget* parent);
	static GUIFW_DECL_EXPORT GuiFrameWindow* createFromFile(const  std::wstring& fileName, const  std::wstring &rootPath, GuiFrameWindow *parent);

private:
	static bool createChild(const XmlElement *child, GuiWidget *parent, GuiFrameWindow* frameWindow );
};

//
typedef GuiWidget* (* pGuiWidgetCreateFunc)(GuiWidget *parent);
typedef GuiFrameWindow* (* pGuiFramwWindowCreateFunc)(GuiFrameWindow *parent);

//
template<typename FUNC_TYPE >
struct TypeNode
{
	std::wstring class_name;
	FUNC_TYPE create_func;
	TypeNode( const  std::wstring& name, FUNC_TYPE func )
	{
		class_name = name;
		create_func = func;
		GuiTypeRegister<FUNC_TYPE>::getInstance()->registerClass( class_name, func );
	}
};

//
template<typename FUNC_TYPE >
class GuiTypeRegister
{
public:
	static GuiTypeRegister* getInstance()
	{
		static GuiTypeRegister* s_guiTypeRegister = NULL;
		if ( s_guiTypeRegister == NULL )
		{
			s_guiTypeRegister = new GuiTypeRegister();
		}

		return s_guiTypeRegister;
	}

	void registerClass( const  std::wstring& class_name, FUNC_TYPE func )
	{
		if ( g_typeList.find( class_name ) == g_typeList.end() )
		{
			g_typeList[class_name] = func;
		}
	}

	void unregisterClass( const  std::wstring& class_name, FUNC_TYPE func )
	{
		std::map< std::wstring, FUNC_TYPE>::iterator it = g_typeList.find( class_name );
		if ( it != g_typeList.end() )
		{
			g_typeList.erase( it );
		}
	}
	
	FUNC_TYPE findCreateFunc( const  std::wstring& class_name )
	{
		std::map< std::wstring, FUNC_TYPE>::iterator it = g_typeList.find( class_name );
		if ( it != g_typeList.end() )
		{
			return (*it).second;
		}

		return NULL;
	}

private:
	std::map< std::wstring, FUNC_TYPE> g_typeList;
};

template <typename OBJECT_TYPE, typename FUNC_TYPE, typename PARENTTYPE>
struct GuiDynamicList
{
	static OBJECT_TYPE* createObject( const std::wstring& class_name, PARENTTYPE* parent  )
	{
		OBJECT_TYPE* obj = NULL;
		FUNC_TYPE createFunc = GuiTypeRegister<FUNC_TYPE>::getInstance()->findCreateFunc( class_name );
		if ( createFunc != NULL )
		{
			obj = (*createFunc)( parent );
		}

		return obj;  
	}
};

//
#define  GUI_DECLARE_CLASSNAME( classname ) \
private: \
	static std::wstring s_classname##classname;\
public: \
	static std::wstring className() \
	{ \
	return classname::s_classname##classname; \
	} 

#define GUI_IMPLEMENT_CLASSNAME( classname ) \
	std::wstring classname::s_classname##classname = L#classname;

//
#define GUI_DECLARE_DYNAMIC_CREATE_SELF(classname,parenttype,functype)	\
public:\
	static parenttype* dynamicCreateObject##classname(parenttype* parent)	\
	{	\
		classname* p = new classname(parent);	\
		return static_cast<parenttype*>(p);\
	} \
private: \
	static TypeNode<functype> s_register##classname;

#define GUI_IMPLEMENT_DYNAMIC_CREATE_SELF( classname, functype ) \
	TypeNode<functype> classname::s_register##classname=TypeNode<functype>( L#classname, classname::dynamicCreateObject##classname  );

//
#define GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( classname ) \
	GUI_DECLARE_DYNAMIC_CREATE_SELF( classname, GuiWidget, pGuiWidgetCreateFunc );

#define GUI_IMPLEMENT_WIDGET_DYNAMIC_CREATE_SELF( classname ) \
	GUI_IMPLEMENT_DYNAMIC_CREATE_SELF( classname, pGuiWidgetCreateFunc );

//
#define GUI_DECLARE_FRAME_DYNAMIC_CREATE_SELF( classname ) \
	GUI_DECLARE_DYNAMIC_CREATE_SELF( classname, GuiFrameWindow, pGuiFramwWindowCreateFunc );

#define GUI_IMPLEMENT_FRAME_DYNAMIC_CREATE_SELF( classname ) \
	GUI_IMPLEMENT_DYNAMIC_CREATE_SELF( classname, pGuiFramwWindowCreateFunc );

typedef GuiDynamicList<GuiWidget,pGuiWidgetCreateFunc,GuiWidget> GuiDynamicWidgetList;
typedef GuiDynamicList<GuiFrameWindow,pGuiFramwWindowCreateFunc,GuiFrameWindow> GuiDynamicFrameList;

template struct GUIFW_DECL_EXPORT TypeNode<pGuiWidgetCreateFunc>;
template struct GUIFW_DECL_EXPORT TypeNode<pGuiFramwWindowCreateFunc>;


