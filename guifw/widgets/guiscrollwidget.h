#pragma once
#include "guifw/guiwidget.h"

class GuiScrollWidgetPrivate;

class GUIFW_DECL_EXPORT GuiScrollWidget : public GuiWidget
{
	GUI_DECLARE_WIDGET_DYNAMIC_CREATE_SELF( GuiScrollWidget )

public:
	GuiScrollWidget( GuiWidget* parent = NULL );
	~GuiScrollWidget(void);

	enum ScrollBarPolicy 
	{
		ScrollBarAsNeeded,
		ScrollBarAlwaysOff,
		ScrollBarAlwaysOn
	}; 

	GuiScrollWidget::ScrollBarPolicy scrollBarPolicy() const;
	void setScrollBarPolicy( GuiScrollWidget::ScrollBarPolicy policy );

	int scrollPos();
	void setScrollPos( int pos );

protected:
	virtual void construct();
	virtual void paintEvent( GuiPainter* painter );
	virtual void resizeEvent( GuiEvent* msg );

private:
	void on_scrollBar_valueChanged();
	GuiWidget* _contentWidget();

private:
	void _layout();
	void _scroll();

private:
	GuiScrollWidgetPrivate* d_ptr;
};
