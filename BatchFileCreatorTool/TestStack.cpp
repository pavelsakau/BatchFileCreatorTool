#include "TestStack.h"
#include <wx/cursor.h>
#include <wx/settings.h>
#include "DndCustom.h"

void TestStack::AppendTestItem(const wxString& text) {
	stack->InsertItem(stack->GetItemCount(), text);
}

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
		}
		wxListItem item;
		item.SetId(i);
		item.SetText(dragText);
		item.SetTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
		item.SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
		stack->InsertItem(item);
		lastAstericsId = i;
	}
}

TestStack::TestStack(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	stack = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME | wxLC_REPORT | wxLC_NO_HEADER | wxLC_SINGLE_SEL);

	stack->DeleteAllColumns();

	labelImageSet = false;

	wxListItem col0;
	col0.SetId(0);
	col0.SetText(wxT("Stack Test #"));
	col0.SetColumn(0);
	//col0.SetAlign(wxLIST_FORMAT_CENTER); don't work?
	col0.SetWidth(wxLIST_AUTOSIZE_USEHEADER);
	stack->InsertColumn(0, col0);

	stack->SetColumnWidth(0, wxLIST_AUTOSIZE_USEHEADER);

	vbox->Add(stack, 1, wxEXPAND | wxALL);

	SetSizer(vbox);

	stack->SetDropTarget(new DndCustom(this));

	Connect(wxID_ANY, wxEVT_SIZE, wxSizeEventHandler(TestStack::OnResize));
	stack->Connect(wxID_ANY, wxEVT_LIST_BEGIN_DRAG, wxListEventHandler(TestStack::OnBeginDrag), nullptr, this);
	stack->Connect(wxID_ANY, wxEVT_LIST_ITEM_SELECTED, wxListEventHandler(TestStack::OnItemSelect), nullptr, this);
	//stack->Connect(wxID_ANY, wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(TestStack::OnErase), nullptr, this);
	//stack->Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(TestStack::OnStackPaint), nullptr, this);
	//Connect(wxID_ANY, wxEVT_MOTION, wxMouseEventHandler(TestStack::OnMoveDrag));
	//Connect(wxID_ANY, wxEVT_LEFT_UP, wxMouseEventHandler(TestStack::OnEndDrag));
}

void TestStack::OnItemSelect(wxListEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}

void TestStack::OnErase(wxEraseEvent& event) {
}

//void TestStack::OnStackPaint(wxPaintEvent& event) {
//	long selectedItem = stack->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
//	if (selectedItem == wxNOT_FOUND) {
//		return;
//	}
//
//	wxRect rect;
//	if (!stack->GetItemRect(selectedItem, rect, wxLIST_RECT_LABEL)) {
//		return;
//	}
//
//	wxPaintDC dc(stack);
//
//	event.Skip();
//	event.ShouldPropagate();
//}

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
	SetCol0Width(event.GetSize().GetWidth() - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X));
	//if (HasScrollbar(wxVERTICAL)) {
	//	SetCol0Width(event.GetSize().GetWidth() - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X));
	//} else {
	//	SetCol0Width(event.GetSize().GetWidth() - wxSystemSettings::GetMetric(wxSYS_VSCROLL_X));
	//}
	event.Skip();
}