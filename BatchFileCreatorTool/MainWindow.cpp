#include "MainWindow.h"
#include "TestModuleCtrl.h"

MainWindow::MainWindow(wxWindow * parent, wxWindowID id, const wxString & title, const wxPoint & pos, const wxSize & size, long style, const wxString & name)
	: wxFrame(parent, id, title, pos, size, style ^ wxRESIZE_BORDER, name), testCounter(1)
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	toolbar = new Toolbar(this, wxT("Toolbar"));
	toolbar->EnableTool(wxID_EXECUTE, false);
	vbox->Add(toolbar, 0, wxALIGN_TOP | wxEXPAND);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* stackBox = new wxBoxSizer(wxVERTICAL);
	wxButton* addSimulationTestButton = new wxButton(this, wxID_ANY, "Add simulation test");
	stack = new TestStack(this, wxT("TestStack"));
	stackBox->Add(addSimulationTestButton, 0, wxALIGN_CENTER_HORIZONTAL | wxEXPAND);
	stackBox->Add(stack, 1, wxEXPAND);

	mainSizer->Add(stackBox, 1, wxALIGN_LEFT | wxEXPAND);

	rightPanelWrapper = new wxPanel(this, wxID_ANY);
	wxBoxSizer* wrapperSizer =  new wxBoxSizer(wxHORIZONTAL);
	rightPanelWrapper->SetSizer(wrapperSizer);

	mainSizer->Add(rightPanelWrapper, 4, wxALIGN_LEFT | wxEXPAND);

	vbox->Add(mainSizer, 1, wxEXPAND);

	SetSizer(vbox);

	addSimulationTestButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(MainWindow::OnAddButtonClick), nullptr, this);
	Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainWindow::OnPublish), nullptr, this);
	Connect(wxID_ANY, wxEVT_LIST_ITEM_SELECTED, wxListEventHandler(MainWindow::OnItemSelect), nullptr, this);
	Connect(wxID_REMOVE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnRemoveClick), nullptr, this);

	testData.clear();
}

void MainWindow::OnItemSelect(wxListEvent& event)
{
	LoadTestSetup(event.GetData());
}

void MainWindow::OnAddButtonClick(wxCommandEvent& event) {
	CleanRightPanelSizer();
	wxSizer* sizer = rightPanelWrapper->GetSizer();
	
	wxString nextStackName = GetNextTestName();

	Freeze();
	TestModuleCtrl* testCtrl = new TestModuleCtrl(this, rightPanelWrapper, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, nextStackName);
	sizer->Add((wxWindow*)testCtrl, wxSizerFlags(1).Border(wxALL, TEST_BORDER_WIDTH).Expand());
	sizer->Layout();
	Thaw();
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

wxString MainWindow::GetTestModeParam(int choice) {
	char* params[] = {"end-to-end", "link-troubleshoot", "rtp-receiver", "rtp-transmit", "tcp-receiver", "tcp-transmit", "udp-firewall", "dscp-loss"};
	return wxString(params[choice]);
}

wxString MainWindow::GetCodecParam(int codec) {
	char* params[] = {"G.711(64)", "G.729(8)", "G.723.1(6.3)", "G.723.1(5.3)", "G.726(32)", "G.726(24)", "G.728(16)", "T.38(64)", "G.722(64)", "G.722(56)", "G.722(48)", 
					  "Data64k", "Data1meg", "Skype.Silk(36)", "Skype.Silk(26)", "Skype.Silk(20)", "Skype.Silk(13)", "Skype.Siren", "Skype.RTAudio(29)", "Skype.RTAudio(11.8)", 
					  "Skype.H264(240p)", "Skype.H264(480p)", "Skype.H264(720p)", "Skype.H264(1080p)", "Skype.RTVideo(240p)", "Skype.RTVideo(480p)", "Skype.RTVideo(720p)"};
	return wxString(params[codec]);
}

wxString MainWindow::GetPortParam(const TestSetup& test) {
	if (test.choice == 3) {
		return wxString::Format(wxT("%i"), test.transmitUDP);
	} else if (test.choice == 2) {
		return wxString::Format(wxT("%i"), test.listenUDP);
	} else if (test.choice == 5) {
		return wxString::Format(wxT("%i"), test.transmitTCP);
	} else {
		return wxString::Format(wxT("%i"), test.listenTCP);
	}
}

void MainWindow::PerformPublish(wxFileName cmdFilename) {
	wxFFile cmdFile(cmdFilename.GetFullPath(), "w");
	cmdFile.Write(wxT("set CURRENT_DATE=%date:~10,4%-%date:~4,2%-%date:~7,2%\n"));
	cmdFile.Write(wxT("set CURRENT_TIME=%time:~0,2%-%time:~3,2%-%time:~6,2%\n\n"));

	vector<int> order = stack->GetItemsOrder();

	for (auto id : order) {
		TestSetup test = testData[id];
		wxString mode = wxString::Format("-mode %s ", GetTestModeParam(test.choice));
		wxString a_address = wxString::Format("-a %s ", test.destinationIP);
		wxString c_codec = wxString::Format("-c %s ", GetCodecParam(test.codec));
		wxString n_calls = wxString::Format(wxT("-n %i "), test.numberOfCalls);
		wxString delay = wxString::Format(wxT("-delay %i "), test.delay);
		wxString port = wxString::Format("-port %s ", GetPortParam(test));
		wxString dscp = test.dscpCheck ? wxString::Format(wxT("-dscp %i "), test.dscp) : wxT("");
		wxString t_duration = wxString::Format(wxT("-t %i "), test.duration);
		wxString tcpchunk = wxString::Format(wxT("-tcpchunk %i "), test.chunk);
		wxString tcprandom = test.randUseCheck ? wxT("-tcprandom ") : wxT("");
		wxString f_filename = wxString::Format(wxT("-f %s "), test.GetReportFilenameForPublish());
		wxString s_silent = wxT("-s ");

		wxString command;
		switch (test.choice) {
		case 0:
			command = mode + a_address + c_codec + n_calls + dscp + t_duration + f_filename + s_silent;
			break;
		case 1:
			command = mode + a_address + delay + t_duration + f_filename + s_silent;
			break;
		case 2:
			command = mode + port + s_silent; // RTP Receiver: remote name and enable dscp not used
			break;
		case 3:
			command = mode + a_address + c_codec + n_calls + dscp + t_duration + port + f_filename + s_silent;
			break;
		case 4:
			command = mode + port + s_silent; // TCP Receiver: remote name not used
			break;
		case 5:
			command = mode + a_address + port + tcprandom + t_duration + tcpchunk + f_filename + s_silent;
			break;
		case 6:
			command = mode + a_address + port + f_filename + s_silent;
			break;
		case 7:
			command = mode + a_address + dscp + f_filename + s_silent;
			break;
		}

		wxString license = wxString::Format(wxT("-license %s:%s "), toolbar->GetServerAddrText(), toolbar->GetPortText());
		wxString customer = wxT("");
		if (toolbar->IsCustomerNoVisible()) {
			license = wxT("-license sub01.nlsubscription.com:443 ");
			customer = wxString::Format(wxT("-customer %s "), toolbar->GetCustomerNoText());
		}

		cmdFile.Write(wxString::Format(wxT("REM ********************************************** Test #%i **********************************************\n"), test.id));
		cmdFile.Write(wxString::Format(wxT("CallSimulator.exe %s%s%s\n\n"), command, license, customer));
	}

	cmdFile.Close();
	wxMessageBox(wxString::Format(wxT("Publish to %s complete"), cmdFilename.GetFullPath()));
}

void MainWindow::PerformCopy(wxFileName exeFilename) {
	if (!wxCopyFile("CallSimulator.exe", exeFilename.GetFullPath())) {
		wxMessageBox(wxString::Format(wxT("Can't copy CallSimulator.exe to %s"), exeFilename.GetFullPath()));
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
				PerformPublish(cmdFilename);
				PerformCopy(exeFilename);
			} else {
				wxMessageBox(wxString::Format(wxT("Can't open %s"), path));
			}
		}
	}
}

wxString MainWindow::GetNextTestName() {
	return wxString::Format(wxT("Test #%i"), testCounter++);
}

void MainWindow::OnRemoveClick(wxCommandEvent& event) {
	int removedId = stack->RemoveSelected();
	CleanRightPanelSizer();
	if (testData.find(removedId) != testData.end()) {
		testData.erase(removedId);
	}
}

void MainWindow::SaveTestSetup(const TestSetup& test)
{
	if (testData.find(test.id) != testData.end()) {
		testData[test.id] = test;
		stack->UpdateTestItem(test);
	} else {
		testData.insert(pair<int, TestSetup>(test.id, test));
		stack->AppendTestItem(test);
	}
	toolbar->EnableTool(wxID_EXECUTE, true);
}

void MainWindow::LoadTestSetup(int id)
{
	if (testData.find(id) != testData.end()) {
		CleanRightPanelSizer();
		wxSizer* sizer = rightPanelWrapper->GetSizer();

		Freeze();
		TestModuleCtrl* testCtrl = new TestModuleCtrl(this, rightPanelWrapper, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxRAISED_BORDER, wxString::Format(wxT("Test #%i"), id));
		sizer->Add((wxWindow*)testCtrl, 1, wxALL | wxEXPAND, TEST_BORDER_WIDTH);
		sizer->Layout();

		testCtrl->LoadTestSetup(testData[id]);
		wxCommandEvent event;
		event.SetInt(testData[id].choice);
		testCtrl->TestChoiceChanged(event);
		Thaw();
	}
}