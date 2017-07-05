#pragma once 
#include "guifw/guiframewindow.h"
#include "changeskinwindow.h"

class MainWindow : public GuiFrameWindow
{
	GUI_DECLARE_FRAME_DYNAMIC_CREATE_SELF( MainWindow );

public:
	MainWindow( GuiFrameWindow* parent = NULL );
	~MainWindow();

protected:
	virtual void construct();

gui_slots:
	void on_aboutToClose();
	void on_skinButton_clicked();
	void on_changeSkinWindow_aboutToClose();
	void on_minButton_clicked();
	void on_closeButton_clicked();
	void on_maxButton_clicked();
	void on_msgBoxButton_clicked();
	void on_wirelessButton_clicked();

private:
	ChangeSkinWindow* m_changeSkinWindow;
};

