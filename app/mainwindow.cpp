#include "stable.h"
#include "mainwindow.h"
#include "guifw/guipushbutton.h"

GUI_IMPLEMENT_FRAME_DYNAMIC_CREATE_SELF( MainWindow )
MainWindow::MainWindow( GuiFrameWindow* parent )
: GuiFrameWindow( parent )
, m_changeSkinWindow( NULL )
{
	xsignals_helper::sig_connect( this->aboutToClose, this , &MainWindow::on_aboutToClose );
}

MainWindow::~MainWindow()
{
	if ( m_changeSkinWindow )
	{
		m_changeSkinWindow->close();
		m_changeSkinWindow = NULL;
	}
}

void MainWindow::on_aboutToClose()
{
	
}

void MainWindow::construct()
{
	GuiPushButton* skinButton = static_cast<GuiPushButton*>( findChild( L"skinButton" ) );
	GuiPushButton* minButton = static_cast<GuiPushButton*>( findChild( L"minButton" ) );
	GuiPushButton* maxButton = static_cast<GuiPushButton*>( findChild( L"maxButton" ) );
	GuiPushButton* closeButton = static_cast<GuiPushButton*>( findChild( L"closeButton" ) );
	GuiPushButton* msgBoxButton = static_cast<GuiPushButton*>( findChild( L"msgBoxButton" ) );
	GuiPushButton* wirelessButton = static_cast<GuiPushButton*>( findChild( L"wirelessButton" ) );

	if ( skinButton )
	{
		xsignals_helper::sig_connect( skinButton->clicked, this , &MainWindow::on_skinButton_clicked );
	}
	if ( minButton )
	{
		xsignals_helper::sig_connect( minButton->clicked, this , &MainWindow::on_minButton_clicked );
	}
	if ( closeButton )
	{
		xsignals_helper::sig_connect( closeButton->clicked, this , &MainWindow::on_closeButton_clicked );
	}
	if ( maxButton )
	{
		xsignals_helper::sig_connect( maxButton->clicked, this , &MainWindow::on_maxButton_clicked );
	}
	if ( msgBoxButton )
	{
		xsignals_helper::sig_connect( msgBoxButton->clicked, this , &MainWindow::on_msgBoxButton_clicked );
	}
	if ( wirelessButton )
	{
		xsignals_helper::sig_connect( wirelessButton->clicked, this , &MainWindow::on_wirelessButton_clicked );
	}
}

void MainWindow::on_skinButton_clicked()
{
	if ( m_changeSkinWindow == NULL )
	{
		m_changeSkinWindow = static_cast<ChangeSkinWindow*>(GuiXmlUI::createFromFile( L"layout/changeskinwindow.xml", L"",(GuiFrameWindow*)NULL ));
		xsignals_helper::sig_connect( m_changeSkinWindow->aboutToClose, this , &MainWindow::on_changeSkinWindow_aboutToClose );
		m_changeSkinWindow->centerWindow();
	}

	m_changeSkinWindow->show();
}

void MainWindow::on_changeSkinWindow_aboutToClose()
{
	m_changeSkinWindow = NULL;
}

void MainWindow::on_maxButton_clicked()
{
	if ( ::IsZoomed( hwnd() ) )
	{
		showRestore();
	}
	else
	{
		showMaximize();
	}
}

void MainWindow::on_minButton_clicked()
{
	showMinimize();
}

void MainWindow::on_closeButton_clicked()
{
	close();
}

void MainWindow::on_msgBoxButton_clicked()
{
	GuiWidget* headImageWidget = static_cast<GuiWidget*>( findChild( L"headImageWidget" ) );
	bool bVisible = headImageWidget->isVisible();
	headImageWidget->setVisible( !bVisible );
	GuiWidget* parentItem = static_cast<GuiWidget*>( headImageWidget->parent() );
	if ( parentItem )
	{
		parentItem->updateLayout();
	}
	headImageWidget->update();
}

void MainWindow::on_wirelessButton_clicked()
{
	GuiWidget* personInfoWidget = static_cast<GuiWidget*>( findChild( L"personInfoWidget" ) );
	bool bVisible = personInfoWidget->isVisible();
	personInfoWidget->setVisible( !bVisible );
	GuiWidget* parentItem = static_cast<GuiWidget*>( personInfoWidget->parent() );
	if ( parentItem )
	{
		parentItem->updateLayout();
	}
	personInfoWidget->update();
}
