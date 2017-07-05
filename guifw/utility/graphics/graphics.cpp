#include "graphics.h"

namespace Utility
{
	namespace Graphics
	{
		SizeF getTextBounds( const Font& font,const StringFormat& strFormat,const std::wstring& szText )
		{
			//GraphicsPath path;
			//FontFamily fontfamily;
			//font.GetFamily(&fontfamily);
			//path.AddString(szText.c_str(),-1,&fontfamily,font.GetStyle(),font.GetSize(),PointF(0,0),&strFormat);
			//RectF rcBound;
			//path.GetBounds(&rcBound);

			//return SizeF(rcBound.Width,rcBound.Height); //path ÔõÃ´²â²»×¼£¿£¿

			HDC hDC = ::GetDC(NULL);
			Gdiplus::Graphics gh(hDC);
			Gdiplus::RectF out;
			Gdiplus::StringFormat *stringFormat = Gdiplus::StringFormat::GenericTypographic()->Clone();
			stringFormat->SetFormatFlags( stringFormat->GetFormatFlags() | Gdiplus::StringFormatFlagsMeasureTrailingSpaces  );
			gh.MeasureString(szText.c_str(),szText.length(),&font,Gdiplus::PointF(0,0),stringFormat,&out);
			::ReleaseDC(NULL,hDC);
			delete stringFormat;
			return Gdiplus::SizeF(out.Width,out.Height);
		}

		int getEncoderClsid( const WCHAR* format, CLSID* pClsid )
		{
			UINT num = 0;         // number of image encoders
			UINT size = 0;        // size of the image encoder array in bytes
			ImageCodecInfo* pImageCodecInfo = NULL;
			GetImageEncodersSize(&num, &size);
			if(size == 0)
				return -1; // Failure
			pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
			if(pImageCodecInfo == NULL)
				return -1; // Failure
			GetImageEncoders(num, size, pImageCodecInfo);
			for(UINT j = 0; j < num; ++j)
			{
				if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
				{
					*pClsid = pImageCodecInfo[j].Clsid;
					free(pImageCodecInfo);
					return j; // Success
				}
			}
			free(pImageCodecInfo);
			return -1; // Failure
		}
	}
}