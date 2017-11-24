#ifndef TOOLBAR_H_
#define TOOLBAR_H_

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/toolbar.h>

class Toolbar : public wxPanel
{
private:
	wxToolBar* toolbar;
	wxStaticText* customerNumber;
	wxTextCtrl* customerNumberText;
	wxTextCtrl* serverAddrText;

public:
	Toolbar(wxWindow* parent, const wxString& title);
	void OnToolbarClick(wxCommandEvent& event);
	void EnableTool(int toolid, bool enable);
	void SetCustomerNoVisible(bool isVisible);
	bool IsCustomerNoVisible();
	wxString GetServerAddrText();
	wxString GetCustomerNoText();
	void ServerAddrTextChanged(wxCommandEvent& event);
};

#endif
