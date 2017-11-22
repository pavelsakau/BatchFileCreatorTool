#include "TestStack.h"
#include <wx/cursor.h>
#include <wx/settings.h>

class DndCustom : public wxDropTarget
{
private:
	TestStack* parent;

public:
	DndCustom(TestStack* parent) : parent(parent) {
		SetDataObject(new wxTextDataObject);
	}

	virtual wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult def)
	{
		parent->OnDrag(x, y);
		return def;
	}

	virtual wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult def)
	{
		if (!GetData())
			return wxDragNone;

		parent->CleanupEmptyLine();
		parent->DoSmthng(x, y, ((wxTextDataObject*) GetDataObject())->GetText());

		return def;
	}
};

void TestStack::CleanupEmptyLine() {
	if (lastAstericsId != wxNOT_FOUND) {
		stack->DeleteItem(lastAstericsId);
		lastAstericsId = wxNOT_FOUND;
	}
}

void TestStack::OnDrag(wxCoord x, wxCoord y)
{
	wxPoint mousePoint(x, y);
	int lookupflags = wxLIST_HITTEST_ONITEM;
	int i = stack->HitTest(mousePoint, lookupflags);
	if (i != lastAstericsId && i != wxNOT_FOUND) {
		if (lastAstericsId != wxNOT_FOUND) {
			stack->DeleteItem(lastAstericsId);
			//wxString astericsText = stack->GetItemText(lastAstericsId, 0);
			//if (astericsText.EndsWith("*")) {
			//	stack->SetItemText(lastAstericsId, astericsText.substr(0, astericsText.length() - 1));
			//}
		}
		//wxString itemText = stack->GetItemText(i, 0);
		//if (!itemText.EndsWith("*")) {
		//	stack->SetItemText(i, itemText.Append("*"));
		//}
		wxListItem item;
		item.SetId(i);
		item.SetText(dragText);
		item.SetTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
		item.SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
		//stack->InsertItem(i, item);
		stack->InsertItem(item);
		lastAstericsId = i;
	}

	//for (int i = 0; i < stack->GetItemCount(); i++) {
	//	wxRect rect;
	//	stack->GetItemRect(i, rect);
	//	if (rect.Contains(mousePoint) && i != lastAstericsId) {
	//		if (lastAstericsId != wxNOT_FOUND) {
	//			wxString astericsText = stack->GetItemText(lastAstericsId, 0);
	//			if (astericsText.EndsWith("*")) {
	//				stack->SetItemText(lastAstericsId, astericsText.substr(0, astericsText.length() - 1));
	//			}
	//		}
	//		wxString itemText = stack->GetItemText(i, 0);
	//		if (!itemText.EndsWith("*")) {
	//			stack->SetItemText(i, itemText.Append("*"));
	//		}
	//		lastAstericsId = i;
	//		return;
	//	}
	//}
}

TestStack::TestStack(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	stack = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME | wxLC_REPORT);

	stack->DeleteAllColumns();

	labelImageSet = false;

	wxListItem col0;
	col0.SetId(0);
	col0.SetText(wxT("Stack Test #"));
	col0.SetColumn(0);
	//col0.SetAlign(wxLIST_FORMAT_CENTER); don't work?
	col0.SetWidth(wxLIST_AUTOSIZE_USEHEADER);
	stack->InsertColumn(0, col0);

	for (int i = 0; i < 30; i++) {
		stack->InsertItem(i, wxString::Format(wxT("Test #%d"), i));
	}

	//DoSmthng(wxT("just test"));

	stack->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);

	vbox->Add(stack, 1, wxEXPAND | wxALL);

	SetSizer(vbox);

	stack->SetDropTarget(new DndCustom(this));

	Connect(wxID_ANY, wxEVT_SIZE, wxSizeEventHandler(TestStack::OnResize));
	stack->Connect(wxID_ANY, wxEVT_LIST_BEGIN_DRAG, wxListEventHandler(TestStack::OnBeginDrag), nullptr, this);
	//stack->Connect(wxID_ANY, wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(TestStack::OnErase), nullptr, this);
	//stack->Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(TestStack::OnStackPaint), nullptr, this);
	//Connect(wxID_ANY, wxEVT_MOTION, wxMouseEventHandler(TestStack::OnMoveDrag));
	//Connect(wxID_ANY, wxEVT_LEFT_UP, wxMouseEventHandler(TestStack::OnEndDrag));
}

void TestStack::OnErase(wxEraseEvent& event) {
}

void TestStack::OnStackPaint(wxPaintEvent& event) {
	long selectedItem = stack->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (selectedItem == wxNOT_FOUND) {
		return;
	}

	wxRect rect;
	if (!stack->GetItemRect(selectedItem, rect, wxLIST_RECT_LABEL)) {
		return;
	}

	wxPaintDC dc(stack);

	////wxBitmap *m_buffer = new wxBitmap(rect.GetWidth(), rect.GetHeight(), dc);
	////wxMemoryDC memory_dc;
	////memory_dc.SelectObject(*m_buffer);
	////memory_dc.Blit(0, 0, rect.GetWidth(), rect.GetHeight(), &dc, rect.GetX(), rect.GetY()); 
	////dc.Blit();

	//wxBitmap labelBitmap = dc.GetAsBitmap(&rect);
	////labelImage = labelBitmap.ConvertToImage();
	//labelImage = labelBitmap.ConvertToImage();
	//labelImageSet = true;

	event.Skip();
	event.ShouldPropagate();
}

void TestStack::DoSmthng(wxCoord x, wxCoord y, const wxString& str)
{
	wxPoint mousePoint(x, y);
	int lookupflags = wxLIST_HITTEST_ONITEM;
	int i = stack->HitTest(mousePoint, lookupflags);
	if (i == wxNOT_FOUND) {
		i = stack->GetItemCount();
	}
	stack->InsertItem(i, str);

	//stack->InsertItem(stack->GetItemCount(), str);
}

void TestStack::OnBeginDrag(wxListEvent& event) {

	long selectedItem = stack->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (selectedItem == -1) {
		return;
	}

	//wxRect rect;
	//if (!stack->GetItemRect(selectedItem, rect, wxLIST_RECT_LABEL)) {
	//	return;
	//}

	//wxClientDC dc(stack);

	//dc.SetFont(stack->GetFont());
	//int width = dc.GetTextExtent(stack->GetItemText(selectedItem, 0).Append(" ")).GetWidth();

	//wxBitmap bitmap(width, rect.GetHeight());
	//wxMemoryDC memDC;
	//memDC.SelectObject(bitmap);
	//memDC.Blit(0, 0, width, rect.GetHeight(), &dc, rect.GetX(), rect.GetY());
	//memDC.SelectObject(wxNullBitmap);
	//labelImage = bitmap.ConvertToImage();
	//labelImageSet = true;

	dragText = stack->GetItemText(selectedItem, 0);

	wxTextDataObject data;
	data.SetText(dragText);
	wxDropSource dragSource(stack);
	dragSource.SetData(data);
	//if (labelImageSet) {
	//	dragSource.SetCursor(wxDragCopy, wxCursor(labelImage));
	//} else {
	//	dragSource.SetCursor(wxDragCopy, wxCursor(*wxHOURGLASS_CURSOR));
	//}
	//dragSource.SetCursor(wxDragCopy, wxCursor(*wxCROSS_CURSOR));

	stack->DeleteItem(selectedItem);
	lastAstericsId = wxNOT_FOUND;

	dragSource.DoDragDrop(wxDragMove);
}

void TestStack::SetCol0Width(int width)
{
	stack->SetColumnWidth(0, width);
	stack->Refresh();
}

void TestStack::OnResize(wxSizeEvent& event)
{
	if (HasScrollbar(wxVERTICAL)) {
		SetCol0Width(event.GetSize().GetWidth() - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X));
	} else {
		SetCol0Width(event.GetSize().GetWidth());
	}
	event.Skip();
}