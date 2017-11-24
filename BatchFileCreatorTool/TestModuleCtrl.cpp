#include "TestModuleCtrl.h"

#include <wx/combo.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/datetime.h>
#include <wx/tokenzr.h>

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
	wxStaticText* testModeLabel = new wxStaticText(testModePanel, wxID_ANY, "Test mode", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	testModeChoice = new wxChoice(testModePanel, wxID_ANY);
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
	testModeSizer->AddStretchSpacer(10);
	testModeSizer->Add(testModeLabel, wxSizerFlags(60).Align(wxALIGN_CENTER));
	testModeSizer->Add(testModeChoice, wxSizerFlags(30).Align(wxALIGN_CENTER_VERTICAL).Expand());
	testModeSizer->AddStretchSpacer(10);
	testModePanel->SetSizer(testModeSizer);

	testStaticSizer->Add(testModePanel, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 5).Expand());
	testStaticSizer->AddSpacer(15);

	wxBoxSizer* bottomPanelSizer = new wxBoxSizer(wxVERTICAL);

	destinationIP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* destinationIPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* destinationIPLabel = new wxStaticText(destinationIP, wxID_ANY, wxT("Destination IP"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	destinationIPText = new wxTextCtrl(destinationIP, wxID_ANY, wxT("8.8.8.8"));
	destinationIPSizer->Add(destinationIPLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	destinationIPSizer->Add(destinationIPText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	destinationIP->SetSizer(destinationIPSizer);
	bottomPanelSizer->Add(destinationIP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	delay = new wxPanel(this, wxID_ANY);
	wxBoxSizer* delaySizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* delayLabel = new wxStaticText(delay, wxID_ANY, wxT("Delay"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	delayText = new wxSpinCtrl(delay, wxID_ANY, wxT("100"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 100);
	delaySizer->Add(delayLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	delaySizer->Add(delayText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	delay->SetSizer(delaySizer);
	bottomPanelSizer->Add(delay, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	remote = new wxPanel(this, wxID_ANY);
	wxBoxSizer* remoteSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* remoteLabel = new wxStaticText(remote, wxID_ANY, wxT("Remote Name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	remoteText = new wxTextCtrl(remote, wxID_ANY, wxT("Remote1"));
	remoteSizer->Add(remoteLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	remoteSizer->Add(remoteText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	remote->SetSizer(remoteSizer);
	bottomPanelSizer->Add(remote, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	listenUDP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* listenUDPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* listenUDPLabel = new wxStaticText(listenUDP, wxID_ANY, wxT("Listen UDP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	listenUDPText = new wxSpinCtrl(listenUDP, wxID_ANY, wxT("5010"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 65534, 5010);
	listenUDPSizer->Add(listenUDPLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	listenUDPSizer->Add(listenUDPText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	listenUDP->SetSizer(listenUDPSizer);
	bottomPanelSizer->Add(listenUDP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	transmitUDP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* transmitUDPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* transmitUDPLabel = new wxStaticText(transmitUDP, wxID_ANY, wxT("Transmit UDP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	transmitUDPText = new wxSpinCtrl(transmitUDP, wxID_ANY, wxT("5010"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 65534, 5010);
	transmitUDPSizer->Add(transmitUDPLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	transmitUDPSizer->Add(transmitUDPText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	transmitUDP->SetSizer(transmitUDPSizer);
	bottomPanelSizer->Add(transmitUDP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	destinationUDP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* destinationUDPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* destinationUDPLabel = new wxStaticText(destinationUDP, wxID_ANY, wxT("Destination UDP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	destinationUDPText = new wxSpinCtrl(destinationUDP, wxID_ANY, wxT("5010"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 65534, 5010);
	destinationUDPSizer->Add(destinationUDPLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	destinationUDPSizer->Add(destinationUDPText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	destinationUDP->SetSizer(destinationUDPSizer);
	bottomPanelSizer->Add(destinationUDP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	listenTCP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* listenTCPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* listenTCPLabel = new wxStaticText(listenTCP, wxID_ANY, wxT("Listen TCP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	listenTCPText = new wxSpinCtrl(listenTCP, wxID_ANY, wxT("5004"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 65534, 5004);
	listenTCPSizer->Add(listenTCPLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	listenTCPSizer->Add(listenTCPText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	listenTCP->SetSizer(listenTCPSizer);
	bottomPanelSizer->Add(listenTCP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	transmitTCP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* transmitTCPSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* transmitTCPLabel = new wxStaticText(transmitTCP, wxID_ANY, wxT("Transmit TCP port"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	transmitTCPText = new wxSpinCtrl(transmitTCP, wxID_ANY, wxT("5004"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 65534, 5004);
	transmitTCPSizer->Add(transmitTCPLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	transmitTCPSizer->Add(transmitTCPText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	transmitTCP->SetSizer(transmitTCPSizer);
	bottomPanelSizer->Add(transmitTCP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	codec = new wxPanel(this, wxID_ANY);
	wxBoxSizer* codecSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* codecLabel = new wxStaticText(codec, wxID_ANY, wxT("Codec"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	codecText = new wxChoice(codec, wxID_ANY);
	const char* CodecNames[27] = {"G.711 (64kbits)", "G.729 (8kbps)", "G.723.1 (6.3kbps)", "G.723.1 (5.3kbps)", "G.726 (32kbps)", "G.726 (24kbps)", "G.728 (16kbps)", "T.38 (64kbps)",
		"G.722 (64kbps)", "G.722 (56kbps)", "G.722 (48kbps)", "Bulk Data (64kbps)", "Bulk Data (1mbps)", "Skype: Silk (36k)", "Skype: Silk (26k)", "Skype: Silk (20k)",
		"Skype: Silk (13k)", "Skype: Siren (16k)", "Skype: RTAudio (29k)", "Skype: RTAudio (11.8k)", "Skype: H.264 (240p)", "Skype: H.264 (480p)", "Skype: H.264 (720p)",
		"Skype: H.264 (1080p)", "Skype: RTVideo (240p)", "Skype: RTVideo (480p)", "Skype: RTVideo (720p)"};
	for (int i = 0; i < 27; i++) {
		codecText->Append(wxString(CodecNames[i]));
	}
	codecText->SetSelection(0);
	codecSizer->Add(codecLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	codecSizer->Add(codecText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	codec->SetSizer(codecSizer);
	bottomPanelSizer->Add(codec, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	numberOfCalls = new wxPanel(this, wxID_ANY);
	wxBoxSizer* numberOfCallsSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* numberOfCallsLabel = new wxStaticText(numberOfCalls, wxID_ANY, wxT("Number of calls"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	numberOfCallsText = new wxSpinCtrl(numberOfCalls, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 1000, 1);
	numberOfCallsSizer->Add(numberOfCallsLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	numberOfCallsSizer->Add(numberOfCallsText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	numberOfCalls->SetSizer(numberOfCallsSizer);
	bottomPanelSizer->Add(numberOfCalls, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	dscp = new wxPanel(this, wxID_ANY);
	wxBoxSizer* dscpSizer = new wxBoxSizer(wxHORIZONTAL);
	dscpCheck = new wxCheckBox(dscp, wxID_ANY, wxT("DSCP Tag"));
	dscpText = new wxSpinCtrl(dscp, wxID_ANY, wxT("46"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 63, 46);
	dscpSizer->AddStretchSpacer(50);
	dscpSizer->Add(dscpCheck, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	dscpSizer->AddStretchSpacer(1);
	dscpSizer->Add(dscpText, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	dscp->SetSizer(dscpSizer);
	dscpCheck->SetValue(true);
	bottomPanelSizer->Add(dscp, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	randUse = new wxPanel(this, wxID_ANY);
	wxBoxSizer* randUseSizer = new wxBoxSizer(wxHORIZONTAL);
	randUseCheck = new wxCheckBox(randUse, wxID_ANY, wxT("Random Usage Fluctuation"));
	randUseSizer->AddStretchSpacer(50);
	randUseSizer->Add(randUseCheck, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	randUse->SetSizer(randUseSizer);
	randUseCheck->SetValue(true);
	bottomPanelSizer->Add(randUse, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	enableDSCP = new wxPanel(this, wxID_ANY);
	wxBoxSizer* enableDSCPSizer = new wxBoxSizer(wxHORIZONTAL);
	enableDSCPCheck = new wxCheckBox(enableDSCP, wxID_ANY, wxT("Enable DSCP"));
	enableDSCPSizer->AddStretchSpacer(50);
	enableDSCPSizer->Add(enableDSCPCheck, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	enableDSCP->SetSizer(enableDSCPSizer);
	enableDSCPCheck->SetValue(true);
	bottomPanelSizer->Add(enableDSCP, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	duration = new wxPanel(this, wxID_ANY);
	wxBoxSizer* durationSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* durationLabel = new wxStaticText(duration, wxID_ANY, wxT("Duration"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	durationText = new wxSpinCtrl(duration, wxID_ANY, wxT("300"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000000, 300);
	durationSizer->Add(durationLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	durationSizer->Add(durationText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	duration->SetSizer(durationSizer);
	bottomPanelSizer->Add(duration, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	chunk = new wxPanel(this, wxID_ANY);
	wxBoxSizer* chunkSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* chunkLabel = new wxStaticText(chunk, wxID_ANY, wxT("Chunk size"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	chunkText = new wxSpinCtrl(chunk, wxID_ANY, wxT("1400"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 64, 9500, 1400);
	chunkSizer->Add(chunkLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	chunkSizer->Add(chunkText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	chunk->SetSizer(chunkSizer);
	bottomPanelSizer->Add(chunk, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	report = new wxPanel(this, wxID_ANY);
	wxBoxSizer* reportSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* reportLabel = new wxStaticText(report, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	reportText = new wxTextCtrl(report, wxID_ANY, wxT("End-to-End_8.8.8.8.htm"));
	reportSizer->Add(reportLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	reportSizer->Add(reportText, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	reportText->Enable(false);
	report->SetSizer(reportSizer);
	bottomPanelSizer->Add(report, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	save = new wxPanel(this, wxID_ANY);
	wxBoxSizer* saveSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* saveButton = new wxButton(save, wxID_ANY, "Save block");
	saveSizer->AddStretchSpacer(1);
	saveSizer->Add(saveButton, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_BOTTOM));
	save->SetSizer(saveSizer);
	bottomPanelSizer->Add(save, wxSizerFlags(1).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	testStaticSizer->Add(bottomPanelSizer, 90, wxALIGN_BOTTOM | wxEXPAND);

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
	test.codec = codecText->GetSelection();
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
	chunkText->SetValue(test.chunk);
	codecText->SetSelection(test.codec);
	delayText->SetValue(test.delay);
	destinationIPText->SetValue(test.destinationIP);
	destinationUDPText->SetValue(test.destinationUDP);
	dscpText->SetValue(test.dscp);
	dscpCheck->SetValue(test.dscpCheck); OnDSCPCheck(wxCommandEvent());
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
	dscpText->Enable(dscpCheck->IsChecked());
}

bool TestModuleCtrl::IsDestinationIPCorrect(const wxString& ip) {
	wxStringTokenizer tokenizer(ip, ".");
	int count = 0;
	while (tokenizer.HasMoreTokens())
	{
		wxString token = tokenizer.GetNextToken();
		long part;
		if (!token.ToLong(&part)) {
			return false;
		}
		if (part < 0 || part > 255) {
			return false;
		}
		count++;
	}
	if (count != 4) {
		return false;
	}
	return true;
}

void TestModuleCtrl::OnSaveButtonClick(wxCommandEvent& event)
{
	TestSetup test = GetTestSetup();
	if (!IsDestinationIPCorrect(test.destinationIP)) {
		wxMessageBox(wxString::Format(wxT("Destination IP '%s' is not valid IP address"), test.destinationIP));
	} else {
		mainWindow->SaveTestSetup(test);
	}
}

void TestModuleCtrl::UpdateReportFilename()
{
	wxDateTime time = wxDateTime::Now();
	switch (testModeChoice->GetSelection()) {
	case 0:
		reportText->SetValue(wxString::Format("End-to-End_%s_DSCP%i(%s).htm", destinationIPText->GetValue(), dscpText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 1:
		reportText->SetValue(wxString::Format("Link-Troubleshoot_%s(%s).htm", destinationIPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 2:
		break;
	case 3:
		reportText->SetValue(wxString::Format("RTP-Transmitter_%s(port%i)(%s).htm", destinationIPText->GetValue(), transmitUDPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 4:
		break;
	case 5:
		reportText->SetValue(wxString::Format("TCP-Transmitter_%s(port%i)(%s).htm", destinationIPText->GetValue(), transmitTCPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 6:
		reportText->SetValue(wxString::Format("UDP-Firewall_%s(port%i)(%s).htm", destinationIPText->GetValue(), destinationUDPText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
		break;
	case 7:
		reportText->SetValue(wxString::Format("DSCP-Loss_%s_DSCP%i(%s).htm", destinationIPText->GetValue(), dscpText->GetValue(), time.Format(wxDefaultDateTimeFormat, wxDateTime::Local)));
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
