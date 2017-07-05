#pragma once 
#include "guifw/guiframewindow.h"
#include "guifw/guisliderwidget.h"

class ChangeSkinWindow : public GuiFrameWindow
{
	GUI_DECLARE_FRAME_DYNAMIC_CREATE_SELF( ChangeSkinWindow );

public:
	ChangeSkinWindow( GuiFrameWindow* parent = NULL );
	~ChangeSkinWindow();

protected:
	virtual void construct();

gui_slots:
	void on_skinParm_changed();
	void on_disableSkinButton_clicked();
	void on_randChangeSkinButton_clicked();
	void on_minButton_clicked();
	void on_closeButton_clicked();

private:
	GuiSliderWidget* m_redSliderWidget;
	GuiSliderWidget* m_greenSliderWidget;
	GuiSliderWidget* m_blueSliderWidget;
	GuiSliderWidget* m_alphaSliderWidget;
	std::vector<std::wstring> m_skinImageList;
	int m_currentIndex;
};

