#pragma once

#include "guiglobal.h"

namespace Utility
{
	namespace text
	{
		GUIFW_DECL_EXPORT std::wstring toWideString(const char* pStr, int len,UINT CodePage = CP_ACP );

		GUIFW_DECL_EXPORT std::string toNarrowString(const wchar_t* pStr, int len, UINT CodePage = CP_ACP);

		GUIFW_DECL_EXPORT void splitWString(const std::wstring &stringOrg, const std::wstring & delimiter, std::vector<std::wstring> &vectorResult);

		GUIFW_DECL_EXPORT std::string getHashString( const char *hashData, int length );

		GUIFW_DECL_EXPORT std::wstring Char2String(unsigned char c);

		GUIFW_DECL_EXPORT std::wstring BinToHex(const std::string& bin);

		GUIFW_DECL_EXPORT std::string URLEncode2(const std::string& src);
		GUIFW_DECL_EXPORT std::string URLEncode2(const std::wstring& str);
		GUIFW_DECL_EXPORT std::wstring URLEncode(const std::wstring& src);

        GUIFW_DECL_EXPORT bool isUtf8Text(const char *text, size_t size);

		GUIFW_DECL_EXPORT std::string toBase64String(const void *data, size_t size);
		GUIFW_DECL_EXPORT void spliteString( const std::wstring& src, const std::wstring& delimiter, std::vector<std::wstring>& containter );
		GUIFW_DECL_EXPORT int stringToInt( const std::wstring& data );
	}
}
