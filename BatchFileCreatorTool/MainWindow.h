#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <wx/wx.h>
#include <wx/frame.h>
#include "Toolbar.h"
#include "TestStack.h"
#include "TestSetup.h"
#include <map>

using namespace std;

class MainWindow : public wxFrame
{
private:
	Toolbar* toolbar;
	TestStack* stack;
	wxPanel* rightPanelWrapper;
	wxTextCtrl* serverAddrText;
	wxTextCtrl* customNumberText;
	int staticBoxId;
	int testCounter;

	map<int, TestSetup> testData;

public:
	MainWindow(wxWindow *parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE,
		const wxString& name = wxFrameNameStr);

	void OnPublish(wxCommandEvent& event);

	void OnAddButtonClick(wxCommandEvent& event);
	void OnItemSelect(wxListEvent& event);
	void ServerAddrTextChanged(wxCommandEvent& event);

	wxString GetNextTestName();

	void SaveTestSetup(const TestSetup& test);
	void LoadTestSetup(int id);

	void CleanRightPanelSizer();
};

#endif
