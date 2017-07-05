#include "stable.h"
#include "changeskinwindow.h"
#include "guifw/guiskinmanager.h"
#include "guifw/guilabelwidget.h"
#include "guifw/guipushbutton.h"

#define SkinImageCount 20

GUI_IMPLEMENT_FRAME_DYNAMIC_CREATE_SELF( ChangeSkinWindow )
ChangeSkinWindow::ChangeSkinWindow( GuiFrameWindow* parent )
: GuiFrameWindow( parent )
, m_currentIndex( 0 )
{
	for ( int i = 0; i < SkinImageCount; i++ )
	{
		std::wstringstream wot;
		wot << L"theme/qq/bg/bg" << i << L".jpg";
		m_skinImageList.push_back( wot.str() );
	}
}

ChangeSkinWindow::~ChangeSkinWindow()
{

}

void ChangeSkinWindow::construct()
{
	/*LONG dwStyle = ::GetWindowLong( hwnd(), GWL_EXSTYLE );
	dwStyle &= ~WS_MAXIMIZEBOX;
	::SetWindowLong( hwnd(), GWL_EXSTYLE, dwStyle );*/

	GuiPushButton* randChangeSkinButton = static_cast<GuiPushButton*>( findChild( L"randChangeSkinButton" ) );
	GuiPushButton* disableSkinButton = static_cast<GuiPushButton*>( findChild( L"disableSkinButton" ) );
	GuiPushButton* minButton = static_cast<GuiPushButton*>( findChild( L"minButton" ) );
	GuiPushButton* closeButton = static_cast<GuiPushButton*>( findChild( L"closeButton" ) );

	m_redSliderWidget = static_cast<GuiSliderWidget*>( findChild( L"redSliderWidget" ) );
	m_greenSliderWidget = static_cast<GuiSliderWidget*>( findChild( L"greenSliderWidget" ) );
	m_blueSliderWidget = static_cast<GuiSliderWidget*>( findChild( L"blueSliderWidget" ) );
	m_alphaSliderWidget = static_cast<GuiSliderWidget*>( findChild( L"alphaSliderWidget" ) );

	if ( m_redSliderWidget )
	{
		m_redSliderWidget->setMaxValue( 255 );
		xsignals_helper::sig_connect( m_redSliderWidget->valueChanged, this , &ChangeSkinWindow::on_skinParm_changed );
	}
	if ( m_greenSliderWidget )
	{
		m_greenSliderWidget->setMaxValue( 255 );
		xsignals_helper::sig_connect( m_greenSliderWidget->valueChanged, this , &ChangeSkinWindow::on_skinParm_changed );
	}
	if ( m_blueSliderWidget )
	{
		m_blueSliderWidget->setMaxValue( 255 );
		xsignals_helper::sig_connect( m_blueSliderWidget->valueChanged, this , &ChangeSkinWindow::on_skinParm_changed );
	}
	if ( m_alphaSliderWidget )
	{
		m_alphaSliderWidget->setMaxValue( 255 );
		xsignals_helper::sig_connect( m_alphaSliderWidget->valueChanged, this , &ChangeSkinWindow::on_skinParm_changed);
	}
	if ( randChangeSkinButton )
	{
		xsignals_helper::sig_connect( randChangeSkinButton->clicked, this , &ChangeSkinWindow::on_randChangeSkinButton_clicked );
	}
	if ( disableSkinButton )
	{
		xsignals_helper::sig_connect( disableSkinButton->clicked, this , &ChangeSkinWindow::on_disableSkinButton_clicked );
	}
	if ( minButton )
	{
		xsignals_helper::sig_connect( minButton->clicked, this , &ChangeSkinWindow::on_minButton_clicked );
	}
	if ( closeButton )
	{
		xsignals_helper::sig_connect( closeButton->clicked, this , &ChangeSkinWindow::on_closeButton_clicked );
	}
}

void ChangeSkinWindow::on_skinParm_changed()
{
	if ( m_redSliderWidget == NULL 
		|| m_greenSliderWidget == NULL 
		|| m_blueSliderWidget == NULL 
		|| m_alphaSliderWidget == NULL )
	{
		return;
	}

	GuiLabelWidget* redValueLabel = static_cast<GuiLabelWidget*>(findChild( L"redValueLabel" ) );
	GuiLabelWidget* greenValueLabel = static_cast<GuiLabelWidget*>(findChild( L"greenValueLabel" ) );
	GuiLabelWidget* blueValueLabel = static_cast<GuiLabelWidget*>(findChild( L"blueValueLabel" ) );
	GuiLabelWidget* alphaValueLabel = static_cast<GuiLabelWidget*>(findChild( L"alphaValueLabel" ) );

	int r = m_redSliderWidget->maxValue() - m_redSliderWidget->currentValue();
	int g = m_greenSliderWidget->maxValue() - m_greenSliderWidget->currentValue();
	int b = m_blueSliderWidget->maxValue() - m_blueSliderWidget->currentValue();
	int a = m_alphaSliderWidget->maxValue() - m_alphaSliderWidget->currentValue();

	
	r = r > 240 ? 255 : r;
	g = g > 240 ? 255 : g;
	b = b > 240 ? 255 : b;
	a = a > 240 ? 255 : a;
	r = r < 10 ? 0 : r;
	g = g < 10 ? 0 : g;
	b = b < 10 ? 0 : b;
	a = a < 50 ? 50 : a;
	
	std::wstringstream ot_r;
	std::wstringstream ot_g;
	std::wstringstream ot_b;
	std::wstringstream ot_a;
	ot_r << r;
	redValueLabel->setText( ot_r.str() );
	ot_g << g;
	greenValueLabel->setText( ot_g.str() );
	ot_b << b;
	blueValueLabel->setText( ot_b.str() );
	ot_a << a;
	alphaValueLabel->setText( ot_a.str() );

	skinManager()->setSkinAlphaValue( a );
	skinManager()->setSkinImage( Color( r, g, b ) );
	//Image
}

void ChangeSkinWindow::on_disableSkinButton_clicked()
{
	std::wstring imagePath = skinManager()->skinImagePath();
	if ( imagePath == L"" )
	{
		std::wstring imagePath = m_skinImageList.at( m_currentIndex );
		skinManager()->setSkinImagePath( imagePath );
	}
	else
	{
		skinManager()->setSkinImagePath( L"" );
	}
}

void ChangeSkinWindow::on_randChangeSkinButton_clicked()
{
	m_currentIndex++;
	if ( m_currentIndex == SkinImageCount )
	{
		m_currentIndex = 0;
	}

	std::wstring imagePath = m_skinImageList.at( m_currentIndex );
	skinManager()->setSkinImagePath( imagePath );
}

void ChangeSkinWindow::on_minButton_clicked()
{
	showMinimize();
}

void ChangeSkinWindow::on_closeButton_clicked()
{
	close();
}
