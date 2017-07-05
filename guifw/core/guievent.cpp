#include "guiglobal.h"
#include "guievent.h"

GuiEvent::GuiEvent()
: type( GuiEventType )
, wParam( 0 )
, lParam( 0 )
, bAccepted( true )
{

}

GuiEvent::~GuiEvent()
{

}

