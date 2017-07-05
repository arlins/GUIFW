#pragma once

class GuiFrameWindow;
class GuiWidgetEventDispatcherPrivate;

class GuiWidgetEventDispatcher
{
public:
	GuiWidgetEventDispatcher( GuiFrameWindow* frameWindow );
	~GuiWidgetEventDispatcher(void);

	void closeEvent( GuiEvent* msg );
	void resizeEvent( GuiEvent* msg );
	void paintEvent( GuiPainter* painter );

	void mouseWheelEvent( GuiEvent* msg );
	void mouseHoverEvent( GuiEvent* msg );
	void mouseMoveEvent( GuiEvent* msg );
	void mouseEnterEvent( GuiEvent* msg );
	void mouseLeaveEvent( GuiEvent* msg );
	void mouseLButtonPressEvent( GuiEvent* msg );
	void mouseLButtonReleaseEvent( GuiEvent* msg );
	void mouseMButtonPressEvent( GuiEvent* msg );
	void mouseMButtonReleaseEvent( GuiEvent* msg );
	void mouseRButtonPressEvent( GuiEvent* msg );
	void mouseRButtonReleaseEvent( GuiEvent* msg );
	void mouseMButtonDoubleClickEvent( GuiEvent* msg );
	void mouseLButtonDoubleClickEvent( GuiEvent* msg );
	void mouseRButtonDoubleClickEvent( GuiEvent* msg );

private:
	GuiWidgetEventDispatcherPrivate* d_ptr;
};
