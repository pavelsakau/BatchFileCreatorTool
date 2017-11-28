#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <wx/wx.h>
#include <wx/frame.h>
#include "Toolbar.h"
#include "TestStack.h"
#include "TestSetup.h"
#include <map>
#include <wx/dirdlg.h>
#include <wx/filefn.h> 
#include <wx/filename.h>
#include <wx/ffile.h>

using namespace std;

class MainWindow : public wxFrame
{
private:
	Toolbar* toolbar;
	TestStack* stack;
	wxPanel* rightPanelWrapper;

	map<int, TestSetup> testData;

	const int TEST_BORDER_WIDTH = 5;

public:
	MainWindow(wxWindow *parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE,
		const wxString& name = wxFrameNameStr);

	void OnClose(wxCloseEvent& event);
	void OnPublish(wxCommandEvent& event);

	void OnItemDeselected(wxListEvent& event);
	void AddButtonClick(wxCommandEvent& event);
	void EditButtonClick(wxCommandEvent& event);
	void RemoveButtonClick(wxCommandEvent& event);

	void OnAddButtonClick(wxCommandEvent& event);
	void OnItemSelect(wxListEvent& event);
	void OnContextMenuClick(wxCommandEvent& event);
	void PerformPublish(wxFileName cmdFilename);
	void PerformCopy(wxFileName exeFilename);
	void PerformDelete();
	void PerformeEdit();

	wxString GetNextTestName();

	void SaveTestSetup(const TestSetup& test);
	void AddTestSetup(const TestSetup& test);
	void CancelAddOrEdit();
	void LoadTestSetup(int id);

	void CleanRightPanelSizer();

	wxString GetTestModeParam(int choice);
	wxString GetCodecParam(int codec);
	wxString GetPortParam(const TestSetup& test);

	void OnTextChange(wxCommandEvent& event);
	void RadioClick(wxCommandEvent& event);
};

#endif
