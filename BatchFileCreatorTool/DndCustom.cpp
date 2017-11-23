#include "DndCustom.h"

DndCustom::DndCustom(TestStack* parent) : parent(parent) {
	SetDataObject(new wxTextDataObject);
}

wxDragResult DndCustom::OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
{
	parent->OnDrag(x, y);
	return def;
}

wxDragResult DndCustom::OnData(wxCoord x, wxCoord y, wxDragResult def)
{
	if (!GetData())
		return wxDragNone;

	parent->CleanupEmptyLine();
	parent->DoSmthng(x, y, ((wxTextDataObject*) GetDataObject())->GetText());

	return def;
}