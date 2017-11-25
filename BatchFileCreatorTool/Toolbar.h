#ifndef TOOLBAR_H_
#define TOOLBAR_H_

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/toolbar.h>
#include <wx/radiobut.h>

class Toolbar : public wxPanel
{
private:
	wxToolBar* toolbar;
	wxStaticText* serverAddr;
	wxStaticText* serverPort;
	wxStaticText* customerNumber;
	wxTextCtrl* customerNumberText;
	wxTextCtrl* serverAddrText;
	wxTextCtrl* serverPortText;
	wxRadioButton* serverRadio;
	wxRadioButton* customerRadio;
	wxWindowID serverRadioId;
	wxWindowID customerRadioId;

public:
	Toolbar(wxWindow* parent, const wxString& title);
	void OnToolbarClick(wxCommandEvent& event);
	void EnableTool(int toolid, bool enable);
	void SetCustomerNoVisible(bool isVisible);
	bool IsCustomerNoVisible();
	wxString GetServerAddrText();
	wxString GetPortText();
	wxString GetCustomerNoText();
	void ServerAddrTextChanged(wxCommandEvent& event);
	void RadioClick(wxCommandEvent& event);
};

#endif
