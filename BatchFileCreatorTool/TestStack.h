#ifndef TEST_STACK_H_
#define TEST_STACK_H_

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/frame.h>
#include <wx/dnd.h>
#include <vector>
#include "TestSetup.h"

using namespace std;

class TestStack : public wxPanel
{
private:
	wxListCtrl* stack;
	wxMenu* removePopupMenu;
	int lastAstericsId;
	wxString dragText;
	int dragId;

public:
	TestStack(wxWindow* parent, const wxString& title);

	void OnErase(wxEraseEvent& event);
	void OnResize(wxSizeEvent& event);
	void SetCol0Width(int width);

	void OnBeginDrag(wxListEvent& event);

	void OnItemSelect(wxListEvent& event);

	void OnContextMenu(wxListEvent& event);
	void OnContextMenuClick(wxCommandEvent& event);
	int GetSelectedId();

	void DropItem(wxCoord x, wxCoord y, wxTextDataObject* obj);
	void OnDrag(wxCoord x, wxCoord y);
	void CleanupEmptyLine();
	void AppendTestItem(const TestSetup& test);
	void UpdateTestItem(const TestSetup& test);
	vector<int> GetItemsOrder();
	wxString GetAppendStrFormat(const TestSetup& test);
	int RemoveSelected();
};

#endif
