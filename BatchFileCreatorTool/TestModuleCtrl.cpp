#include "TestModuleCtrl.h"

#include <wx/combo.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/datetime.h>

const wxString TestModuleCtrl::END_TO_END_TEST_TEXT = wxT("End-to-End Test");
const wxString TestModuleCtrl::LINK_TROUBLESHOOTING_TEST_TEXT = wxT("Link Troubleshooting Test");
const wxString TestModuleCtrl::RTP_RECEIVER_TEXT = wxT("RTP Receiver");
const wxString TestModuleCtrl::RTP_TRANSMITTER_TEXT = wxT("RTP Transmitter");
const wxString TestModuleCtrl::TCP_RECEIVER_TEXT = wxT("TCP Receiver");
const wxString TestModuleCtrl::TCP_TRANSMITTER_TEXT = wxT("TCP Transmitter");
const wxString TestModuleCtrl::UDP_FIREWALL_TEST_TEXT = wxT("UDP Firewall Test");
const wxString TestModuleCtrl::DSCP_LOSS_TEST_TEXT = wxT("DSCP Loss Test");

TestModuleCtrl::TestModuleCtrl(MainWindow* mainWindow, wxWindow *parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& label) : wxPanel(parent, winid, pos, size, style), staticLabel(label), mainWindow(mainWindow)
{
	wxStaticBox* testStaticBox = new wxStaticBox(this, wxID_ANY, label);
	testStaticSizer = new wxStaticBoxSizer(testStaticBox, wxVERTICAL);

	wxPanel* testModePanel = new wxPanel(testStaticBox, wxID_ANY);
	wxBoxSizer* testModeSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* testModeLabel = new wxStaticText(testModePanel, wxID_ANY, "Test mode", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	//wxStaticText* testModeLabel = new wxStaticText(testModePanel, wxID_ANY, "Test mode");
	testModeChoice = new wxChoice(testModePanel, wxID_ANY);
	testModeChoice->SetColumns(1);
	wxArrayString str;
	str.Add(END_TO_END_TEST_TEXT);
	str.Add(LINK_TROUBLESHOOTING_TEST_TEXT);
	str.Add(RTP_RECEIVER_TEXT);
	str.Add(RTP_TRANSMITTER_TEXT);
	str.Add(TCP_RECEIVER_TEXT);
	str.Add(TCP_TRANSMITTER_TEXT);
	str.Add(UDP_FIREWALL_TEST_TEXT);
	str.Add(DSCP_LOSS_TEST_TEXT);
	testModeChoice->Append(str);
	testModeSizer->Add(testModeLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	testModeSizer->AddStretchSpacer(1);
	testModeSizer->Add(testModeChoice, 25, wxALIGN_TOP | wxALIGN_LEFT);
	testModeSizer->AddStretchSpacer(25);
	testModePanel->SetSizer(testModeSizer);

	testStaticSizer->Add(testModePanel, 10, wxALIGN_TOP | wxTOP | wxEXPAND);

	wxPanel* bottomPanel = new wxPanel(testStaticBox, wxID_ANY);
	wxBoxSizer* bottomPanelSizer = new wxBoxSizer(wxVERTICAL);

	destinationIP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* destinationIPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* destinationIPLabel = new wxStaticText(destinationIP, wxID_ANY, wxT("Destination IP"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	destinationIPText = new wxTextCtrl(destinationIP, wxID_ANY, wxT("8.8.8.8"));
	destinationIPSizer->Add(destinationIPLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	destinationIPSizer->AddStretchSpacer(1);
	destinationIPSizer->Add(destinationIPText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	destinationIPSizer->AddStretchSpacer(25);
	destinationIP->SetSizer(destinationIPSizer);
	bottomPanelSizer->Add(destinationIP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	delay = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* delaySizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* delayLabel = new wxStaticText(delay, wxID_ANY, wxT("Delay"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	delayText = new wxTextCtrl(delay, wxID_ANY, wxT("100"));
	delaySizer->Add(delayLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	delaySizer->AddStretchSpacer(1);
	delaySizer->Add(delayText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	delaySizer->AddStretchSpacer(25);
	delay->SetSizer(delaySizer);
	bottomPanelSizer->Add(delay, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	remote = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* remoteSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* remoteLabel = new wxStaticText(remote, wxID_ANY, wxT("Remote Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	remoteText = new wxTextCtrl(remote, wxID_ANY, wxT("Remote1"));
	remoteSizer->Add(remoteLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	remoteSizer->AddStretchSpacer(1);
	remoteSizer->Add(remoteText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	remoteSizer->AddStretchSpacer(25);
	remote->SetSizer(remoteSizer);
	bottomPanelSizer->Add(remote, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	listenUDP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* listenUDPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* listenUDPLabel = new wxStaticText(listenUDP, wxID_ANY, wxT("Listen UDP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	listenUDPText = new wxTextCtrl(listenUDP, wxID_ANY, wxT("5010"));
	listenUDPSizer->Add(listenUDPLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	listenUDPSizer->AddStretchSpacer(1);
	listenUDPSizer->Add(listenUDPText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	listenUDPSizer->AddStretchSpacer(25);
	listenUDP->SetSizer(listenUDPSizer);
	bottomPanelSizer->Add(listenUDP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	transmitUDP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* transmitUDPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* transmitUDPLabel = new wxStaticText(transmitUDP, wxID_ANY, wxT("Transmit UDP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	transmitUDPText = new wxTextCtrl(transmitUDP, wxID_ANY, wxT("5010"));
	transmitUDPSizer->Add(transmitUDPLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	transmitUDPSizer->AddStretchSpacer(1);
	transmitUDPSizer->Add(transmitUDPText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	transmitUDPSizer->AddStretchSpacer(25);
	transmitUDP->SetSizer(transmitUDPSizer);
	bottomPanelSizer->Add(transmitUDP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	destinationUDP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* destinationUDPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* destinationUDPLabel = new wxStaticText(destinationUDP, wxID_ANY, wxT("Destination UDP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	destinationUDPText = new wxTextCtrl(destinationUDP, wxID_ANY, wxT("5010"));
	destinationUDPSizer->Add(destinationUDPLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	destinationUDPSizer->AddStretchSpacer(1);
	destinationUDPSizer->Add(destinationUDPText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	destinationUDPSizer->AddStretchSpacer(25);
	destinationUDP->SetSizer(destinationUDPSizer);
	bottomPanelSizer->Add(destinationUDP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	listenTCP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* listenTCPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* listenTCPLabel = new wxStaticText(listenTCP, wxID_ANY, wxT("Listen TCP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	listenTCPText = new wxTextCtrl(listenTCP, wxID_ANY, wxT("5004"));
	listenTCPSizer->Add(listenTCPLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	listenTCPSizer->AddStretchSpacer(1);
	listenTCPSizer->Add(listenTCPText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	listenTCPSizer->AddStretchSpacer(25);
	listenTCP->SetSizer(listenTCPSizer);
	bottomPanelSizer->Add(listenTCP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	transmitTCP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* transmitTCPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* transmitTCPLabel = new wxStaticText(transmitTCP, wxID_ANY, wxT("Transmit TCP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	transmitTCPText = new wxTextCtrl(transmitTCP, wxID_ANY, wxT("5004"));
	transmitTCPSizer->Add(transmitTCPLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	transmitTCPSizer->AddStretchSpacer(1);
	transmitTCPSizer->Add(transmitTCPText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	transmitTCPSizer->AddStretchSpacer(25);
	transmitTCP->SetSizer(transmitTCPSizer);
	bottomPanelSizer->Add(transmitTCP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	codec = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* codecSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* codecLabel = new wxStaticText(codec, wxID_ANY, wxT("Codec"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	codecText = new wxTextCtrl(codec, wxID_ANY, wxT("G.711"));
	codecSizer->Add(codecLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	codecSizer->AddStretchSpacer(1);
	codecSizer->Add(codecText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	codecSizer->AddStretchSpacer(25);
	codec->SetSizer(codecSizer);
	bottomPanelSizer->Add(codec, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	numberOfCalls = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* numberOfCallsSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* numberOfCallsLabel = new wxStaticText(numberOfCalls, wxID_ANY, wxT("Number of calls"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	numberOfCallsText = new wxTextCtrl(numberOfCalls, wxID_ANY, wxT("1"));
	numberOfCallsSizer->Add(numberOfCallsLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	numberOfCallsSizer->AddStretchSpacer(1);
	numberOfCallsSizer->Add(numberOfCallsText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	numberOfCallsSizer->AddStretchSpacer(25);
	numberOfCalls->SetSizer(numberOfCallsSizer);
	bottomPanelSizer->Add(numberOfCalls, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	dscp = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* dscpSizer = new wxBoxSizer(wxHORIZONTAL);
	dscpCheck = new wxCheckBox(dscp, wxID_ANY, wxT("DSCP Tag"));
	dscpText = new wxTextCtrl(dscp, wxID_ANY, wxT("46"));
	dscpSizer->AddStretchSpacer(41);
	dscpSizer->Add(dscpCheck, 9, wxRIGHT | wxALIGN_TOP | wxALIGN_RIGHT);
	dscpSizer->AddStretchSpacer(1);
	dscpSizer->Add(dscpText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	dscpSizer->AddStretchSpacer(25);
	dscp->SetSizer(dscpSizer);
	dscpCheck->SetValue(true);
	bottomPanelSizer->Add(dscp, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	randUse = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* randUseSizer = new wxBoxSizer(wxHORIZONTAL);
	randUseCheck = new wxCheckBox(randUse, wxID_ANY, wxT("Random Usage Fluctuation"));
	randUseSizer->AddStretchSpacer(47);
	randUseSizer->Add(randUseCheck, 3, wxRIGHT | wxALIGN_TOP | wxALIGN_RIGHT);
	randUseSizer->AddStretchSpacer(51);
	randUse->SetSizer(randUseSizer);
	randUseCheck->SetValue(true);
	bottomPanelSizer->Add(randUse, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	enableDSCP = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* enableDSCPSizer = new wxBoxSizer(wxHORIZONTAL);
	enableDSCPCheck = new wxCheckBox(enableDSCP, wxID_ANY, wxT("Enable DSCP"));
	enableDSCPSizer->AddStretchSpacer(51);
	enableDSCPSizer->Add(enableDSCPCheck, 9, wxRIGHT | wxALIGN_TOP | wxALIGN_RIGHT);
	enableDSCPSizer->AddStretchSpacer(51);
	enableDSCP->SetSizer(enableDSCPSizer);
	enableDSCPCheck->SetValue(true);
	bottomPanelSizer->Add(enableDSCP, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	duration = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* durationSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* durationLabel = new wxStaticText(duration, wxID_ANY, wxT("Duration"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	durationText = new wxTextCtrl(duration, wxID_ANY, wxT("300"));
	durationSizer->Add(durationLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	durationSizer->AddStretchSpacer(1);
	durationSizer->Add(durationText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	durationSizer->AddStretchSpacer(25);
	duration->SetSizer(durationSizer);
	bottomPanelSizer->Add(duration, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	chunk = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* chunkSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* chunkLabel = new wxStaticText(chunk, wxID_ANY, wxT("Chunk size"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	chunkText = new wxTextCtrl(chunk, wxID_ANY, wxT("1400"));
	chunkSizer->Add(chunkLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	chunkSizer->AddStretchSpacer(1);
	chunkSizer->Add(chunkText, 25, wxALIGN_TOP | wxALIGN_LEFT);
	chunkSizer->AddStretchSpacer(25);
	chunk->SetSizer(chunkSizer);
	bottomPanelSizer->Add(chunk, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	report = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* reportSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* reportLabel = new wxStaticText(report, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT | wxST_NO_AUTORESIZE);
	reportText = new wxTextCtrl(report, wxID_ANY, wxT("End-to-End_8.8.8.8.htm"));
	reportText->Enable(false);
	reportSizer->Add(reportLabel, 50, wxALIGN_TOP | wxALIGN_RIGHT);
	reportSizer->AddStretchSpacer(1);
	reportSizer->Add(reportText, 35, wxALIGN_TOP | wxALIGN_LEFT);
	reportSizer->AddStretchSpacer(15);
	report->SetSizer(reportSizer);
	bottomPanelSizer->Add(report, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	save = new wxPanel(bottomPanel, wxID_ANY);
	wxBoxSizer* saveSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* saveButton = new wxButton(save, wxID_ANY, "Save block");
	saveSizer->AddStretchSpacer(51);
	saveSizer->Add(saveButton, 50, wxALIGN_TOP | wxALIGN_RIGHT | wxEXPAND);
	saveSizer->AddStretchSpacer(51);
	save->SetSizer(saveSizer);
	bottomPanelSizer->Add(save, 1, wxALIGN_TOP | wxTOP | wxEXPAND);

	//bottomPanelSizer->AddStretchSpacer(1);

	bottomPanel->SetSizer(bottomPanelSizer);

	testStaticSizer->Add(bottomPanel, 90, wxALIGN_BOTTOM | wxBOTTOM | wxALL | wxEXPAND);

	SetSizer(testStaticSizer);

	testModeChoice->Connect(wxEVT_CHOICE, wxCommandEventHandler(TestModuleCtrl::TestChoiceChanged), nullptr, this);
	saveButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(TestModuleCtrl::OnSaveButtonClick), nullptr, this);
	dscpCheck->Connect(wxEVT_CHECKBOX, wxCommandEventHandler(TestModuleCtrl::OnDSCPCheck), nullptr, this);
	destinationIPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	dscpText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	transmitUDPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	transmitTCPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	destinationUDPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);

	UpdateReportFilename();
	HideAllInputPanels();
}

void TestModuleCtrl::OnReportNamePartChange(wxCommandEvent& event)
{
	UpdateReportFilename();
	event.Skip();
}

TestSetup TestModuleCtrl::GetTestSetup()
{
	TestSetup test;
	test.choice = testModeChoice->GetSelection();
	wxString id = staticLabel.substr(staticLabel.find('#') + 1, staticLabel.length() - staticLabel.find('#'));
	id.ToLong((long*)&test.id);
	test.chunk = chunkText->GetValue();
	test.codec = codecText->GetValue();
	test.delay = delayText->GetValue();
	test.destinationIP = destinationIPText->GetValue();
	test.destinationUDP = destinationUDPText->GetValue();
	test.dscp = dscpText->GetValue();
	test.dscpCheck = dscpCheck->IsChecked();
	test.duration = durationText->GetValue();
	test.enableDSCP = enableDSCPCheck->IsChecked();
	test.listenTCP = listenTCPText->GetValue();
	test.listenUDP = listenUDPText->GetValue();
	test.numberOfCalls = numberOfCallsText->GetValue();
	test.randUseCheck = randUseCheck->IsChecked();
	test.remote = remoteText->GetValue();
	test.report = reportText->GetValue();
	test.transmitTCP = transmitTCPText->GetValue();
	test.transmitUDP = transmitUDPText->GetValue();
	return test;
}

void TestModuleCtrl::LoadTestSetup(const TestSetup& test)
{
	testModeChoice->SetSelection(test.choice);
	//staticLabel.substr(staticLabel.find('#'), staticLabel.length() - staticLabel.find('#')).ToLong((long*)&test.id);
	chunkText->SetValue(test.chunk);
	codecText->SetValue(test.codec);
	delayText->SetValue(test.delay);
	destinationIPText->SetValue(test.destinationIP);
	destinationUDPText->SetValue(test.destinationUDP);
	dscpText->SetValue(test.dscp);
	dscpCheck->SetValue(test.dscpCheck);
	durationText->SetValue(test.duration);
	enableDSCPCheck->SetValue(test.enableDSCP);
	listenTCPText->SetValue(test.listenTCP);
	listenUDPText->SetValue(test.listenUDP);
	numberOfCallsText->SetValue(test.numberOfCalls);
	randUseCheck->SetValue(test.randUseCheck);
	remoteText->SetValue(test.remote);
	reportText->SetValue(test.report);
	transmitTCPText->SetValue(test.transmitTCP);
	transmitUDPText->SetValue(test.transmitUDP);
}

void TestModuleCtrl::OnDSCPCheck(wxCommandEvent& event)
{
	//wxMessageBox(wxT("DSCP check"));
	dscpText->Enable(!dscpText->IsEnabled());
}

void TestModuleCtrl::OnSaveButtonClick(wxCommandEvent& event)
{
	//wxMessageBox(wxT("Save block"));
	//UpdateReportFilename();
	TestSetup test = GetTestSetup();
	mainWindow->SaveTestSetup(test);
}

void TestModuleCtrl::UpdateReportFilename()
{
	wxDateTime time = wxDateTime::Now();
	switch (testModeChoice->GetSelection()) {
	case 0:
		reportText->SetValue(wxString::Format("End-to-End_%s_DSCP%s(%s).htm", destinationIPText->GetValue(), dscpText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 1:
		reportText->SetValue(wxString::Format("Link-Troubleshoot_%s(%s).htm", destinationIPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 2:
		break;
	case 3:
		reportText->SetValue(wxString::Format("RTP-Transmitter_%s(port%s)(%s).htm", destinationIPText->GetValue(), transmitUDPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 4:
		break;
	case 5:
		reportText->SetValue(wxString::Format("TCP-Transmitter_%s(port%s)(%s).htm", destinationIPText->GetValue(), transmitTCPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 6:
		reportText->SetValue(wxString::Format("UDP-Firewall_%s(port%s)(%s).htm", destinationIPText->GetValue(), destinationUDPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 7:
		reportText->SetValue(wxString::Format("DSCP-Loss_%s_DSCP%s(%s).htm", destinationIPText->GetValue(), dscpText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	}
}

void TestModuleCtrl::TestChoiceChanged(wxCommandEvent& event)
{
	UpdateReportFilename();
	switch (event.GetInt()) {
	case 0:
		SetEndToEnd();
		break;
	case 1:
		SetLinkTroubleshooting();
		break;
	case 2:
		SetRtpReceiver();
		break;
	case 3:
		SetTrpTransmitter();
		break;
	case 4:
		SetTcpReceiver();
		break;
	case 5:
		SetTcpTransmitter();
		break;
	case 6:
		SetUdpFirewall();
		break;
	case 7:
		SetDscpLoss();
		break;
	}
}

void TestModuleCtrl::HideAllInputPanels()
{
	destinationIP->Hide();
	delay->Hide();
	remote->Hide();
	listenUDP->Hide();
	transmitUDP->Hide();
	destinationUDP->Hide();
	listenTCP->Hide();
	transmitTCP->Hide();
	codec->Hide();
	numberOfCalls->Hide();
	dscp->Hide();
	enableDSCP->Hide();
	duration->Hide();
	chunk->Hide();
	randUse->Hide();
	report->Hide();
	save->Hide();
	//testStaticSizer->Layout();
}

void TestModuleCtrl::SetEndToEnd()
{
	HideAllInputPanels();
	destinationIP->Show();
	codec->Show();
	numberOfCalls->Show();
	dscp->Show();
	duration->Show();
	report->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetLinkTroubleshooting()
{
	HideAllInputPanels();
	destinationIP->Show();
	delay->Show();
	duration->Show();
	report->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetRtpReceiver()
{
	HideAllInputPanels();
	remote->Show();
	listenUDP->Show();
	enableDSCP->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetTrpTransmitter()
{
	HideAllInputPanels();
	destinationIP->Show();
	transmitUDP->Show();
	codec->Show();
	numberOfCalls->Show();
	dscp->Show();
	duration->Show();
	report->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetTcpReceiver()
{
	HideAllInputPanels();
	remote->Show();
	listenTCP->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetTcpTransmitter()
{
	HideAllInputPanels();
	destinationIP->Show();
	transmitTCP->Show();
	chunk->Show();
	randUse->Show();
	duration->Show();
	report->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetUdpFirewall()
{
	HideAllInputPanels();
	destinationIP->Show();
	destinationUDP->Show();
	report->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetDscpLoss()
{
	HideAllInputPanels();
	destinationIP->Show();
	dscp->Show();
	report->Show();
	save->Show();
	testStaticSizer->Layout();
}

//wxStaticBoxSizer* TestModuleCtrl::GetTestSizer() {
//	return testStaticSizer;
//}