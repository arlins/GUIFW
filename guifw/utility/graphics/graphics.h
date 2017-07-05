#pragma once

#include "guiglobal.h"

namespace Utility
{
	namespace Graphics
	{
		GUIFW_DECL_EXPORT SizeF getTextBounds( const Font& font,const StringFormat& strFormat,const std::wstring& szText );
		GUIFW_DECL_EXPORT int getEncoderClsid( const WCHAR* format, CLSID* pClsid );
	}
}