#include "MainWindow.h"
#include "TestModuleCtrl.h"
#include <wx/dirdlg.h>
#include <wx/filefn.h> 
#include <wx/filename.h>
#include <wx/ffile.h>

MainWindow::MainWindow(wxWindow * parent, wxWindowID id, const wxString & title, const wxPoint & pos, const wxSize & size, long style, const wxString & name)
	: wxFrame(parent, id, title, pos, size, style, name), testCounter(1)
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	toolbar = new Toolbar(this, wxT("Toolbar"));
	toolbar->EnableTool(wxID_EXECUTE, false);
	vbox->Add(toolbar, 0, wxTOP | wxEXPAND);

	//wxBoxSizer* topControls = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* topPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* topLeftInputSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* serverAddrLabel = new wxStaticText(topPanel, wxID_ANY, wxT("TotalView server address"));
	serverAddrText = new wxTextCtrl(topPanel, wxID_ANY);
	topLeftInputSizer->AddStretchSpacer(1);
	topLeftInputSizer->Add(serverAddrLabel, 5, wxLEFT | wxALIGN_LEFT | wxFIXED_MINSIZE | wxALIGN_CENTER_VERTICAL);
	topLeftInputSizer->AddStretchSpacer(1);
	topLeftInputSizer->Add(serverAddrText, 15, wxLEFT);
	topLeftInputSizer->AddStretchSpacer(1);

	//wxBoxSizer* topRightInputSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* customNumberLabel = new wxStaticText(topPanel, wxID_ANY, wxT("Customer number"));
	customNumberText = new wxTextCtrl(topPanel, wxID_ANY);
	customNumberText->Enable(false);
	//topRightInputSizer->AddStretchSpacer(1);
	topLeftInputSizer->Add(customNumberLabel, 5, wxLEFT | wxALIGN_LEFT | wxFIXED_MINSIZE | wxALIGN_CENTER_VERTICAL);
	topLeftInputSizer->AddStretchSpacer(1);
	topLeftInputSizer->Add(customNumberText, 15, wxLEFT);
	topLeftInputSizer->AddStretchSpacer(30);

	topPanel->SetSizer(topLeftInputSizer);

	//topControls->Add(topLeftInputSizer, 1, wxALIGN_LEFT | wxEXPAND);
	//topControls->Add(topRightInputSizer, 3, wxALIGN_RIGHT | wxEXPAND);

	//vbox->Add(topLeftInputSizer, 0, wxALIGN_TOP | wxEXPAND);
	vbox->Add(topPanel, 0, wxTOP | wxEXPAND);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* leftPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* stackBox = new wxBoxSizer(wxVERTICAL);
	wxButton* addSimulationTestButton = new wxButton(leftPanel, wxID_ANY, "Add simulation test");
	stack = new TestStack(leftPanel, wxT("TestStack"));
	stackBox->Add(addSimulationTestButton, 0, wxTOP | wxALIGN_CENTER_HORIZONTAL | wxEXPAND);
	stackBox->Add(stack, 1, wxALL | wxEXPAND);

	leftPanel->SetSizer(stackBox);

	mainSizer->Add(leftPanel, 1, wxALIGN_LEFT | wxEXPAND);

	rightPanelWrapper = new wxPanel(this, wxID_ANY);
	wxBoxSizer* wrapperSizer =  new wxBoxSizer(wxHORIZONTAL);

	//TestModuleCtrl* testCtrl = new TestModuleCtrl(rightPanelWrapper, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, "Test #1");
	//staticBoxId = testCtrl->GetId();
	//wrapperSizer->Add((wxWindow*)testCtrl, 1, wxALL | wxEXPAND, 70);

	rightPanelWrapper->SetSizer(wrapperSizer);

	mainSizer->Add(rightPanelWrapper, 5, wxALIGN_RIGHT | wxEXPAND);

	vbox->Add(mainSizer, 1, wxALL | wxEXPAND);

	SetSizer(vbox);

	addSimulationTestButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MainWindow::OnAddButtonClick), nullptr, this);
	Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainWindow::OnPublish));
	leftPanel->Connect(wxID_ANY, wxEVT_LIST_ITEM_SELECTED, wxListEventHandler(MainWindow::OnItemSelect), nullptr, this);
	serverAddrText->Connect(wxEVT_TEXT, wxCommandEventHandler(MainWindow::ServerAddrTextChanged), nullptr, this);

	testData.clear();
}

void MainWindow::ServerAddrTextChanged(wxCommandEvent& event)
{
	customNumberText->Enable(wxString("sub01.nlsubscription.com:443").CompareTo(serverAddrText->GetValue()) == 0);
}

void MainWindow::OnItemSelect(wxListEvent& event)
{
	wxString itemText = event.GetItem().GetText();
	wxString idStr = itemText.substr(itemText.find('#') + 1, itemText.length() - itemText.find('#'));
	int id;
	idStr.ToLong((long*)&id);
	LoadTestSetup(id);
}

void MainWindow::OnAddButtonClick(wxCommandEvent& event) {
	CleanRightPanelSizer();
	wxSizer* sizer = rightPanelWrapper->GetSizer();
	
	wxString nextStackName = GetNextTestName();

	TestModuleCtrl* testCtrl = new TestModuleCtrl(this, rightPanelWrapper, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, nextStackName);
	staticBoxId = testCtrl->GetId();
	sizer->Add((wxWindow*)testCtrl, 1, wxALL | wxEXPAND, 70);
	sizer->Layout();
}

void MainWindow::CleanRightPanelSizer()
{
	wxSizer* sizer = rightPanelWrapper->GetSizer();
	wxSizerItemList ls = sizer->GetChildren();
	for (auto item : ls) {
		int i = item->GetId();
		wxWindow* wnd = item->GetWindow();
		if (wnd != nullptr) {
			sizer->Detach(wnd);
			wnd->Destroy();
			sizer->Layout();
		}
	}
}

void MainWindow::OnPublish(wxCommandEvent& event) {
	wxDirDialog dlg(NULL, "Choose save directory", "",	wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK) {
		wxString path = dlg.GetPath();
		if (path.length() > 0) {
			if (::wxDirExists(path)) {
				wxFileName cmdFilename(path, "CallSimBatch.cmd");
				wxFileName exeFilename(path, "CallSimulator.exe");
				wxFFile cmdFile(cmdFilename.GetFullPath(), "w");
				cmdFile.Write(wxT("CallSimulator.exe\n"));
				cmdFile.Close();
				wxString a = exeFilename.GetFullName();
				if (!wxCopyFile("CallSimulator.exe", exeFilename.GetFullPath())) {
					wxMessageBox(wxString::Format(wxT("Can't copy CallSimulator.exe to %s"), exeFilename.GetFullPath()));
				}
			} else {
				wxMessageBox(wxString::Format(wxT("Can't open %s"), path));
			}
		}
	}
}

wxString MainWindow::GetNextTestName() {
	return wxString::Format(wxT("Test #%i"), testCounter++);
}

void MainWindow::SaveTestSetup(const TestSetup& test)
{
	if (testData.find(test.id) != testData.end()) {
		testData[test.id] = test;
	} else {
		testData.insert(pair<int, TestSetup>(test.id, test));
		stack->AppendTestItem(wxString::Format(wxT("Test #%i"), test.id));
	}
	toolbar->EnableTool(wxID_EXECUTE, true);
}

void MainWindow::LoadTestSetup(int id)
{
	if (testData.find(id) != testData.end()) {
		CleanRightPanelSizer();
		wxSizer* sizer = rightPanelWrapper->GetSizer();

		TestModuleCtrl* testCtrl = new TestModuleCtrl(this, rightPanelWrapper, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, wxString::Format(wxT("Test #%i"), id));
		staticBoxId = testCtrl->GetId();
		sizer->Add((wxWindow*)testCtrl, 1, wxALL | wxEXPAND, 70);
		sizer->Layout();

		testCtrl->LoadTestSetup(testData[id]);
		wxCommandEvent event;
		event.SetId(testData[id].choice);
		testCtrl->TestChoiceChanged(event);
	}
}