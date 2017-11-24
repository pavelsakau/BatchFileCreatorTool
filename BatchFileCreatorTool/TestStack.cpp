#include "TestStack.h"
#include <wx/cursor.h>
#include <wx/settings.h>
#include "DndCustom.h"

vector<int> TestStack::GetItemsOrder() {
	vector<int> order;
	int itemsCount = stack->GetItemCount();
	for (int i = 0; i < itemsCount; i++) {
		order.push_back(stack->GetItemData(i));
	}
	return order;
}

wxString TestStack::GetAppendStrFormat(const TestSetup& test) {
	wxString appendStr;
	switch (test.choice) {
	case 0:
		appendStr = wxString::Format("End-to-End to %s DSCP %i", test.destinationIP, test.dscp);
		break;
	case 1:
		appendStr = wxString::Format("Link-Troubleshoot to %s", test.destinationIP);
		break;
	case 2:
		appendStr = wxString::Format("RTP-Receiver from %s(port %i)", test.remote, test.listenUDP);
		break;
	case 3:
		appendStr = wxString::Format("RTP-Transmitter to %s(port %i)", test.destinationIP, test.transmitUDP);
		break;
	case 4:
		appendStr = wxString::Format("TCP-Receiver from %s(port %i)", test.remote, test.listenTCP);
		break;
	case 5:
		appendStr = wxString::Format("TCP-Transmitter to %s(port %i)", test.destinationIP, test.transmitTCP);
		break;
	case 6:
		appendStr = wxString::Format("UDP-Firewall %s(port %i)", test.destinationIP, test.destinationUDP);
		break;
	case 7:
		appendStr = wxString::Format("DSCP-Loss %s DSCP %i", test.destinationIP, test.dscp);
		break;
	}
	return appendStr;
}

void TestStack::UpdateTestItem(const TestSetup& test) {
	long selectedItem = stack->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (selectedItem == wxNOT_FOUND) {
		selectedItem = stack->FindItem(-1, (wxUIntPtr)test.id);
	}
	if (selectedItem != wxNOT_FOUND) {
		stack->SetItemText(selectedItem, wxString::Format(wxT("Test #%i: %s"), test.id, GetAppendStrFormat(test)));
	}
}

void TestStack::AppendTestItem(const TestSetup& test) {
	wxListItem item;
	item.SetId(stack->GetItemCount());
	item.SetText(wxString::Format(wxT("Test #%i: %s"), test.id, GetAppendStrFormat(test)));
	item.SetData(test.id);
	stack->InsertItem(item);
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
		item.SetData(dragId);
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

	removePopupMenu = new wxMenu();
	removePopupMenu->Append(wxID_REMOVE, wxT("Remove"));

	Connect(wxID_ANY, wxEVT_SIZE, wxSizeEventHandler(TestStack::OnResize));
	stack->Connect(wxID_ANY, wxEVT_LIST_BEGIN_DRAG, wxListEventHandler(TestStack::OnBeginDrag), nullptr, this);
	stack->Connect(wxID_ANY, wxEVT_LIST_ITEM_SELECTED, wxListEventHandler(TestStack::OnItemSelect), nullptr, this);
	stack->Connect(wxID_ANY, wxEVT_LIST_ITEM_RIGHT_CLICK, wxListEventHandler(TestStack::OnContextMenu), nullptr, this);
	removePopupMenu->Connect(wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(TestStack::OnRemoveClick), nullptr, this);
	//stack->Connect(wxID_ANY, wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(TestStack::OnErase), nullptr, this);
	//stack->Connect(wxID_ANY, wxEVT_PAINT, wxPaintEventHandler(TestStack::OnStackPaint), nullptr, this);
	//Connect(wxID_ANY, wxEVT_MOTION, wxMouseEventHandler(TestStack::OnMoveDrag));
	//Connect(wxID_ANY, wxEVT_LEFT_UP, wxMouseEventHandler(TestStack::OnEndDrag));
}

int TestStack::RemoveSelected() {
	long selectedItem = stack->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	int removedId = wxNOT_FOUND;
	if (!(selectedItem == wxNOT_FOUND)) {
		removedId = stack->GetItemData(selectedItem);
		stack->DeleteItem(selectedItem);
	}
	return removedId;
}

void TestStack::OnRemoveClick(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}

void TestStack::OnContextMenu(wxListEvent& event) {
	int i = event.GetId();
	if (i != wxNOT_FOUND) {
		stack->SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
		stack->PopupMenu(removePopupMenu, event.GetPoint());
	}
}

void TestStack::OnItemSelect(wxListEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}

void TestStack::OnErase(wxEraseEvent& event) {
}

void TestStack::DropItem(wxCoord x, wxCoord y, wxTextDataObject* obj)
{
	wxPoint mousePoint(x, y);
	int lookupflags = wxLIST_HITTEST_ONITEM;
	int i = stack->HitTest(mousePoint, lookupflags);
	if (i == wxNOT_FOUND) {
		i = stack->GetItemCount();
	}

	wxListItem item;
	item.SetId(i);
	item.SetText(dragText);
	item.SetData(dragId);
	stack->InsertItem(item);
}

void TestStack::OnBeginDrag(wxListEvent& event) {
	long selectedItem = stack->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	if (selectedItem == wxNOT_FOUND) {
		return;
	}

	dragText = stack->GetItemText(selectedItem);
	dragId = stack->GetItemData(selectedItem);
	
	wxTextDataObject textData;
	textData.SetText(dragText);
	wxDropSource dragSource(stack);
	dragSource.SetData(textData);

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
	event.Skip();
}