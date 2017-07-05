#include <cassert>
#include "ustring.h"

namespace Utility
{
	namespace text
	{
		std::wstring toWideString( const char* pStr , int len,UINT CodePage /*=CP_ACP*/ )
		{
			std::wstring buf ;

			if(pStr == NULL)
			{
				assert(NULL);
				return buf;
			}

			if (len < 0 && len != -1)
			{
				assert(NULL);
				return buf;
			}

			// figure out how many wide characters we are going to get 
			int nChars = MultiByteToWideChar( CodePage , 0 , pStr , len , NULL , 0 ) ; 
			if ( len == -1 )
				-- nChars ; 
			if ( nChars == 0 )
				return L"" ;

			// convert the narrow string to a wide string 
			// nb: slightly naughty to write directly into the string like this
			buf.resize( nChars ) ; 
			MultiByteToWideChar( CodePage , 0 , pStr , len , 
				const_cast<wchar_t*>(buf.c_str()) , nChars ) ; 

			return buf ;
		}

		std::string toNarrowString( const wchar_t* pStr , int len, UINT CodePage )
		{
			std::string buf ;

			if(pStr == NULL)
			{
				assert(NULL);
				return buf;
			}

			if (len < 0 && len != -1)
			{
				assert(NULL);
				return buf;
			}

			// figure out how many narrow characters we are going to get 
			int nChars = WideCharToMultiByte( CodePage , 0 , 
				pStr , len , NULL , 0 , NULL , NULL ) ; 
			if ( len == -1 )
				-- nChars ; 
			if ( nChars == 0 )
				return "" ;

			// convert the wide string to a narrow string
			// nb: slightly naughty to write directly into the string like this
			buf.resize( nChars ) ;
			WideCharToMultiByte( CodePage , 0 , pStr , len , 
				const_cast<char*>(buf.c_str()) , nChars , NULL , NULL ) ; 

			return buf ; 
		}

		void splitWString( const std::wstring &stringOrg, const std::wstring & delimiter, std::vector<std::wstring> &vectorResult )
		{
			size_t last = 0;
			size_t index = stringOrg.find_first_of(delimiter,last);
			while ( index != std::string::npos )
			{
				vectorResult.push_back(stringOrg.substr(last,index-last));
				last = index + 1;
				index = stringOrg.find_first_of(delimiter,last);
			}
			if ( index - last > 0 )
			{
				vectorResult.push_back(stringOrg.substr(last ,index - last));
			}
		}

		std::string getHashString( const char *hashData, int length )
		{
			const char p[] = "0123456789abcdef";

			char out[64] = {0};
			for ( int i = 0; i < length; i++ )
			{
				unsigned char c = hashData[i];
				out[ i * 2 ] = p[c >> 4];
				out[ i * 2 + 1 ] = p[c & 0xf];
			}

			return std::string(out);
		}

		std::wstring Char2String(unsigned char c)
		{
			static wchar_t s_Table[] = {'0', '1', '2', '3', 
				'4', '5', '6', '7',
				'8', '9', 'A', 'B',
				'C', 'D', 'E', 'F'
			};

			std::wstring s;
			s.resize(2);
			s[0] = s_Table[c/16];
			s[1] = s_Table[c%16];

			return s;
		}

		std::wstring BinToHex(const std::string& bin)
		{
			std::wstring result;
			result.reserve(bin.size() * 2);
			for (size_t i = 0; i < bin.size(); ++i)
			{
				unsigned char c = (unsigned char)bin[i];
				result += Char2String(c);
			}
			return result;
		}

		std::string URLEncode2( const std::string& src )
		{
			static    char hex[] = "0123456789ABCDEF";  
			std::string dst;  

			for (size_t i = 0; i < src.size() && src[i] != 0; i++)  
			{  
				unsigned char ch = src[i];  
				if (isalnum(ch) || ch == '.')  
				{  
					dst += ch;  
				}  
				else
				{  
					unsigned char c = static_cast<unsigned char>(src[i]);  
					dst += '%';  
					dst += hex[c >> 4];  
					dst += hex[c % 16];  
				}  
			}  
			return dst;
		}

		std::string URLEncode2( const std::wstring& str )
		{
			//按照要求，必须先转换为utf8，再urlencode
			int size = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, NULL, NULL, NULL);
			char* buffer = new char[size];
			::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, buffer, size, NULL, NULL);
			std::string data(buffer);
			delete[] buffer;

			return URLEncode2(data);
		}

		std::wstring URLEncode(const std::wstring& src)
		{
			std::wstring result;
			wchar_t buf[8] = {0};
			wchar_t c;

			for(size_t i = 0; i < src.length(); ++i)
			{
				c = src.at(i);      
				if( iswalnum(c) || c == L'.' )
				{
					result += c;
				}
				else
				{
					wsprintf(buf, L"%%%02X", c);
					result += buf;
				}
			}
			return result;
		}

        bool isUtf8Text(const char *text, size_t size)
        {
            bool isUtf8 = true;
            unsigned char* start = (unsigned char*)text;
            unsigned char* end = start + size;

            while (start < end)
            {
                if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符
                {
                    start++;
                }
                else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符
                {
                    isUtf8 = false;
                    break;
                }
                else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符
                {
                    if (start >= end - 1)
                    {
                        break;
                    }
                    if ((start[1] & (0xC0)) != 0x80)
                    {
                        isUtf8 = false;
                        break;
                    }
                    start += 2;
                } 
                else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符
                {
                    if (start >= end - 2)
                    {
                        break;
                    }
                    if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
                    {
                        isUtf8 = false;
                        break;
                    }
                    start += 3;
                } 
                else
                {
                    isUtf8 = false;
                    break;
                }
            }

            return isUtf8;
        }

		const char KBase64Chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		std::string toBase64String( const void *data, size_t size )
		{
			const unsigned char *inputData = (const unsigned char*)data;

			/* valid output size ? */
			size_t len2 = 4 * ((size + 2) / 3) + 1;
			std::auto_ptr<char> out(new char[len2]);
			char *p = out.get();

			size_t leven = 3 * (size / 3);
			size_t i = 0;
			for ( i = 0; i < leven; i += 3) 
			{
				*p++ = KBase64Chars[(inputData[0] >> 2) & 0x3F];
				*p++ = KBase64Chars[(((inputData[0] & 3) << 4) + (inputData[1] >> 4)) & 0x3F];
				*p++ = KBase64Chars[(((inputData[1] & 0xf) << 2) + (inputData[2] >> 6)) & 0x3F];
				*p++ = KBase64Chars[inputData[2] & 0x3F];
				inputData += 3;
			}
			/* Pad it if necessary...  */
			if (i < size) 
			{
				unsigned a = inputData[0];
				unsigned b = (i+1 < size) ? inputData[1] : 0;

				*p++ = KBase64Chars[(a >> 2) & 0x3F];
				*p++ = KBase64Chars[(((a & 3) << 4) + (b >> 4)) & 0x3F];
				*p++ = (i+1 < size) ? KBase64Chars[(((b & 0xf) << 2)) & 0x3F] : L'=';
				*p++ = L'=';
			}

			/* append a NULL byte */
			*p = '\0';
			return out.get();
		}

		void spliteString( const std::wstring& src, const std::wstring& delimiter, std::vector<std::wstring>& containter )
		{
			size_t pos = 0, found = 0;

			while ( found != std::wstring::npos )
			{
				found = src.find(delimiter, pos);
				containter.push_back( std::wstring(src, pos, found - pos));
				pos = found + delimiter.size();
			}
		}

		int stringToInt( const std::wstring& data )
		{
			int value = 0;
			swscanf_s( data.c_str(), L"%d", &value );
			return value;
		}
	}
}
