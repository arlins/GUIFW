#include "guiglobal.h"
#include "guiskinmanager.h"
#include "private/guiskinmanager_p.h"
#include "guiapplication.h"
#include "../utility/graphics/graphics.h"
#include "guidefs.h"

GuiSkinManager* skinManager()
{
	static GuiSkinManager* s_skinManager = NULL;
	if ( s_skinManager == NULL )
	{
		s_skinManager = new GuiSkinManager;
	}

	return s_skinManager;
}

GuiSkinManager::GuiSkinManager()
: d_ptr( new GuiSkinManagerPrivate )
{

}

GuiSkinManager::~GuiSkinManager()
{
	Gui_SAFE_DELETE( d_ptr );
}

void GuiSkinManager::setSkinImagePath( const std::wstring& skinImagePath )
{
	d_ptr->skinImagePath = skinImagePath;

	skinImageChanged();
}

std::wstring GuiSkinManager::skinImagePath()
{
	return d_ptr->skinImagePath;
}

void GuiSkinManager::setSkinAlphaValue( int value )
{
	value = min( 255, value );
	value = max( 0, value );
	d_ptr->skinAlphaValue = value;

	skinAlphaValueChanged();
}

int GuiSkinManager::skinAlphaValue()
{
	return d_ptr->skinAlphaValue;
}

void GuiSkinManager::setSkinImage( const Color& color )
{
	int pictureWidth = 100;
	int pictureHeight = 100;
	Bitmap *bmp= new Bitmap(pictureWidth,pictureHeight);
	Graphics *graphics = new Graphics(bmp);
	SolidBrush textBrush( color );
	graphics->FillRectangle(&textBrush,0,0,pictureWidth,pictureHeight);

	CLSID Clsid;
	Utility::Graphics::getEncoderClsid( L"image/png", &Clsid );
	std::wstring imagePath = guiApp->exePath() + L"/" + KSkinImagePath;
	bmp->Save( imagePath.c_str(), &Clsid );
	delete bmp;
	delete graphics;
	graphics=NULL;
	bmp=NULL;
	
	setSkinImagePath( KSkinImagePath );
}
