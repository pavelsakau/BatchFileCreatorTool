#ifndef TEST_STACK_H_
#define TEST_STACK_H_

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/frame.h>
#include <wx/dnd.h>

class TestStack : public wxPanel
{
private:
	wxListCtrl* stack;
	wxImage labelImage;
	bool labelImageSet;
	int lastAstericsId;
	wxString dragText;

public:
	TestStack(wxWindow* parent, const wxString& title);

	void OnErase(wxEraseEvent& event);
	void OnResize(wxSizeEvent& event);
	void SetCol0Width(int width);

	void OnBeginDrag(wxListEvent& event);

	void OnItemSelect(wxListEvent& event);

	void DoSmthng(wxCoord x, wxCoord y, const wxString& str);
	void OnDrag(wxCoord x, wxCoord y);
	void CleanupEmptyLine();
	void AppendTestItem(const wxString& text);
};

#endif
