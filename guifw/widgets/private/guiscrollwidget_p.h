#pragma once
#include "guiglobal.h"
#include "../guiscrollbar.h"
#include "../../core/guiwidget.h"

class GuiScrollWidgetPrivate
{
public:
	GuiScrollWidgetPrivate()
		: scrollBarPolicy( GuiScrollWidget::ScrollBarAsNeeded )
	{

	}
	~GuiScrollWidgetPrivate()
	{

	}

	GuiScrollBar* scrollBar;
	GuiScrollWidget::ScrollBarPolicy scrollBarPolicy;
};
