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
	wxWindowID customerNumberTextID;
	wxTextCtrl* serverAddrText;
	wxWindowID serverAddrTextID;
	wxTextCtrl* serverPortText;
	wxWindowID serverPortTextID;
	wxRadioButton* serverRadio;
	wxRadioButton* customerRadio;
	wxWindowID serverRadioId;
	wxWindowID customerRadioId;
	//wxButton* addTestButton;
	//wxButton* editTestButton;
	//wxButton* deleteTestButton;

public:
	Toolbar(wxWindow* parent, const wxString& title);
	void OnToolbarClick(wxCommandEvent& event);
	void EnableTool(int toolid, bool enable);
	bool IsToolEnable(int toolid);
	void SetCustomerNoVisible(bool isVisible);
	bool IsCustomerNoVisible();
	wxString GetServerAddrText();
	wxString GetPortText();
	wxString GetCustomerNoText();
	void RadioClick(wxCommandEvent& event);
	void OnButtonClick(wxCommandEvent& event);
	void SetAddButtonEnable(bool flag);
	void SetEditButtonEnable(bool flag);
	void SetDeleteButtonEnable(bool flag);
	void OnTextChange(wxCommandEvent& event);
	wxWindowID GetServerTextID();
	wxWindowID GetServerPortID();
	wxWindowID GetCustomerTextID();
};

#endif
