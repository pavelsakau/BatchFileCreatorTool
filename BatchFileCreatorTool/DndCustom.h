#ifndef DND_CUSTOM_H_
#define DND_CUSTOM_H_

#include <wx/wx.h>
#include <wx/dnd.h>
#include "TestStack.h"

class DndCustom : public wxDropTarget
{
private:
	TestStack* parent;

public:
	DndCustom(TestStack* parent);

	virtual wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def);

	virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def);
};


#endif
