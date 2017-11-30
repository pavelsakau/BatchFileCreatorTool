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

TestModuleCtrl::TestModuleCtrl(MainWindow* mainWindow, wxWindow *parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& label, bool addMode) : wxPanel(parent, winid, pos, size, style), staticLabel(label), mainWindow(mainWindow), addMode(addMode)
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
	wxBoxSizer* dscpSizerRight = new wxBoxSizer(wxHORIZONTAL);
	dscpSizerRight->Add(dscpCheck, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	dscpSizerRight->Add(dscpText, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5).Expand());
	dscpSizer->Add(dscpSizerRight, wxSizerFlags(50).Align(wxALIGN_LEFT).Expand());
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

	durationMOS = new wxPanel(this, wxID_ANY);
	wxBoxSizer* durationMOSSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* durationMOSLabel = new wxStaticText(durationMOS, wxID_ANY, wxT("Quit if MOS score drops below"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	durationMOSSizer->Add(durationMOSLabel, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5));
	wxBoxSizer* durationMOSSizerRight = new wxBoxSizer(wxHORIZONTAL);
	mosCheck = new wxCheckBox(durationMOS, wxID_ANY, wxT("MOS"));
	durationMOSSizerRight->Add(mosCheck, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));
	durationMOSText = new wxSpinCtrlDouble(durationMOS, wxID_ANY, wxT("4.0"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1.0, 4.4, 4.0, 0.1);
	durationMOSText->SetDigits(2);
	durationMOSText->Enable(false);
	durationMOSSizerRight->Add(durationMOSText, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	durationMOSSizer->Add(durationMOSSizerRight, wxSizerFlags(50).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	durationMOS->SetSizer(durationMOSSizer);
	bottomPanelSizer->Add(durationMOS, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	duration = new wxPanel(this, wxID_ANY);
	wxBoxSizer* durationSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* durationLabel = new wxStaticText(duration, wxID_ANY, wxT("Duration (seconds)"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
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
	wxBoxSizer* reportSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* reportLabel = new wxStaticText(report, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	reportText = new wxTextCtrl(report, wxID_ANY, wxT("End-to-End_8.8.8.8.htm"));
	reportSizer->Add(reportLabel, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5).Expand());
	reportSizer->Add(reportText, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxTOP, 5).Expand());
	reportText->Enable(false);
	report->SetSizer(reportSizer);
	bottomPanelSizer->Add(report, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	//reportWithRadio = new wxPanel(this, wxID_ANY);
	//wxBoxSizer* reportWithRadioSizer = new wxBoxSizer(wxVERTICAL);
	//wxBoxSizer* radioReportTypesSizer = new wxBoxSizer(wxHORIZONTAL);
	//wxStaticText* reportWithRadioLabel = new wxStaticText(reportWithRadio, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	//reportWithRadioText = new wxTextCtrl(reportWithRadio, wxID_ANY, wxT("End-to-End_8.8.8.8"));
	//radioReportTypesSizer->Add(reportWithRadioLabel, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5).Expand());
	//radioTypesHTML = new wxRadioButton(reportWithRadio, wxID_ANY, wxT("HTML"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	//radioTypesDOCX = new wxRadioButton(reportWithRadio, wxID_ANY, wxT("DOCX"));
	//radioTypesCSV = new wxRadioButton(reportWithRadio, wxID_ANY, wxT("CSV"));
	//radioTypesALL = new wxRadioButton(reportWithRadio, wxID_ANY, wxT("ALL"));
	//radioReportTypesSizer->Add(radioTypesHTML, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//radioReportTypesSizer->Add(radioTypesDOCX, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//radioReportTypesSizer->Add(radioTypesCSV, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//radioReportTypesSizer->Add(radioTypesALL, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//reportWithRadioSizer->Add(radioReportTypesSizer, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	//reportWithRadioSizer->Add(reportWithRadioText, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	//reportWithRadioText->Enable(false);
	//reportWithRadio->SetSizer(reportWithRadioSizer);
	//bottomPanelSizer->Add(reportWithRadio, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	//reportWithRadio2 = new wxPanel(this, wxID_ANY);
	//wxBoxSizer* reportWithRadioSizer2 = new wxBoxSizer(wxVERTICAL);
	//wxBoxSizer* radioReportTypesSizer2 = new wxBoxSizer(wxHORIZONTAL);
	//wxStaticText* reportWithRadioLabel2 = new wxStaticText(reportWithRadio2, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	//reportWithRadioText2 = new wxTextCtrl(reportWithRadio2, wxID_ANY, wxT("End-to-End_8.8.8.8"));
	//radioReportTypesSizer2->Add(reportWithRadioLabel2, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5).Expand());
	//radioTypesHTML2 = new wxRadioButton(reportWithRadio2, wxID_ANY, wxT("HTML"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	//radioTypesCSV2 = new wxRadioButton(reportWithRadio2, wxID_ANY, wxT("CSV"));
	//radioTypesALL2 = new wxRadioButton(reportWithRadio2, wxID_ANY, wxT("ALL"));
	//radioReportTypesSizer2->Add(radioTypesHTML2, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//radioReportTypesSizer2->Add(radioTypesCSV2, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//radioReportTypesSizer2->Add(radioTypesALL2, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	//reportWithRadioSizer2->Add(radioReportTypesSizer2, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	//reportWithRadioSizer2->Add(reportWithRadioText2, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	//reportWithRadioText2->Enable(false);
	//reportWithRadio2->SetSizer(reportWithRadioSizer2);
	//bottomPanelSizer->Add(reportWithRadio2, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	reportWithRadio = new wxPanel(this, wxID_ANY);
	wxBoxSizer* reportWithRadioSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* radioReportTypesSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* reportWithRadioLabel = new wxStaticText(reportWithRadio, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	reportWithRadioText = new wxTextCtrl(reportWithRadio, wxID_ANY, wxT("End-to-End_8.8.8.8"));
	radioReportTypesSizer->Add(reportWithRadioLabel, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5).Expand());
	radioTypesHTML = new wxCheckBox(reportWithRadio, wxID_ANY, wxT("HTML")); radioTypesHTML->SetValue(true);
	radioTypesDOCX = new wxCheckBox(reportWithRadio, wxID_ANY, wxT("DOCX"));
	radioTypesCSV = new wxCheckBox(reportWithRadio, wxID_ANY, wxT("CSV"));
	radioReportTypesSizer->Add(radioTypesHTML, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	radioReportTypesSizer->Add(radioTypesDOCX, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	radioReportTypesSizer->Add(radioTypesCSV, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	reportWithRadioSizer->Add(radioReportTypesSizer, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	reportWithRadioSizer->Add(reportWithRadioText, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxTOP, 5).Expand());
	reportWithRadioText->Enable(false);
	reportWithRadio->SetSizer(reportWithRadioSizer);
	bottomPanelSizer->Add(reportWithRadio, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	reportWithRadio2 = new wxPanel(this, wxID_ANY);
	wxBoxSizer* reportWithRadioSizer2 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* radioReportTypesSizer2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* reportWithRadioLabel2 = new wxStaticText(reportWithRadio2, wxID_ANY, wxT("Report file name"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	reportWithRadioText2 = new wxTextCtrl(reportWithRadio2, wxID_ANY, wxT("End-to-End_8.8.8.8"));
	radioReportTypesSizer2->Add(reportWithRadioLabel2, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 5).Expand());
	radioTypesHTML2 = new wxCheckBox(reportWithRadio2, wxID_ANY, wxT("HTML")); radioTypesHTML2->SetValue(true);
	radioTypesCSV2 = new wxCheckBox(reportWithRadio2, wxID_ANY, wxT("CSV"));
	radioReportTypesSizer2->Add(radioTypesHTML2, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	radioReportTypesSizer2->Add(radioTypesCSV2, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL));
	reportWithRadioSizer2->Add(radioReportTypesSizer2, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());
	reportWithRadioSizer2->Add(reportWithRadioText2, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxTOP, 5).Expand());
	reportWithRadioText2->Enable(false);
	reportWithRadio2->SetSizer(reportWithRadioSizer2);
	bottomPanelSizer->Add(reportWithRadio2, wxSizerFlags(0).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	save = new wxPanel(this, wxID_ANY);
	wxBoxSizer* saveSizer = new wxBoxSizer(wxHORIZONTAL);
	wxButton* saveButton = new wxButton(save, wxID_ANY, addMode ? wxT("Add test") : wxT("Save test"));
	wxButton* cancelButton = new wxButton(save, wxID_ANY, wxT("Cancel"));
	saveSizer->AddStretchSpacer(1);
	saveSizer->Add(saveButton, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_BOTTOM));
	saveSizer->Add(cancelButton, wxSizerFlags(0).Align(wxALIGN_RIGHT | wxALIGN_BOTTOM));
	save->SetSizer(saveSizer);
	bottomPanelSizer->Add(save, wxSizerFlags(1).Align(wxALIGN_TOP).Border(wxTOP, 10).Expand());

	testStaticSizer->Add(bottomPanelSizer, 90, wxALIGN_BOTTOM | wxEXPAND);

	SetSizer(testStaticSizer);

	testModeChoice->Connect(wxEVT_CHOICE, wxCommandEventHandler(TestModuleCtrl::TestChoiceChanged), nullptr, this);
	saveButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(TestModuleCtrl::OnSaveButtonClick), nullptr, this);
	cancelButton->Connect(wxEVT_BUTTON, wxCommandEventHandler(TestModuleCtrl::OnCancelButtonClick), nullptr, this);
	dscpCheck->Connect(wxEVT_CHECKBOX, wxCommandEventHandler(TestModuleCtrl::OnDSCPCheck), nullptr, this);
	destinationIPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	dscpText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	transmitUDPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	transmitTCPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	destinationUDPText->Connect(wxEVT_TEXT, wxCommandEventHandler(TestModuleCtrl::OnReportNamePartChange), nullptr, this);
	mosCheck->Connect(wxEVT_CHECKBOX, wxCommandEventHandler(TestModuleCtrl::OnMosCheckbox), nullptr, this);
	//radioTypesHTML->Connect(radioTypesHTML->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio1Click), nullptr, this);
	//radioTypesDOCX->Connect(radioTypesDOCX->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio1Click), nullptr, this);
	//radioTypesCSV->Connect(radioTypesCSV->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio1Click), nullptr, this);
	//radioTypesALL->Connect(radioTypesALL->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio1Click), nullptr, this);
	//radioTypesHTML2->Connect(radioTypesHTML2->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio2Click), nullptr, this);
	//radioTypesCSV2->Connect(radioTypesCSV2->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio2Click), nullptr, this);
	//radioTypesALL2->Connect(radioTypesALL2->GetId(), wxEVT_RADIOBUTTON, wxCommandEventHandler(TestModuleCtrl::OnRadio2Click), nullptr, this);

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

	test.isMos = mosCheck->GetValue();
	test.mos = durationMOSText->GetValue();
	test.report1_HTML = radioTypesHTML->GetValue();
	test.report1_DOCX = radioTypesDOCX->GetValue();
	test.report1_CSV = radioTypesCSV->GetValue();
	test.report2_HTML = radioTypesHTML2->GetValue();
	test.report2_CSV = radioTypesCSV2->GetValue();

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

	mosCheck->SetValue(test.isMos);
	durationMOSText->Enable(test.isMos);
	durationMOSText->SetValue(test.mos);
	radioTypesHTML->SetValue(test.report1_HTML);
	radioTypesDOCX->SetValue(test.report1_DOCX);
	radioTypesCSV->SetValue(test.report1_CSV);
	radioTypesHTML2->SetValue(test.report2_HTML);
	radioTypesCSV2->SetValue(test.report2_CSV);
}

void TestModuleCtrl::OnRadio1Click(wxCommandEvent& event) {
	UpdateReportFilename();
}

void TestModuleCtrl::OnRadio2Click(wxCommandEvent& event) {
	UpdateReportFilename();
}

void TestModuleCtrl::OnMosCheckbox(wxCommandEvent& event) {
	durationMOSText->Enable(event.IsChecked());
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

void TestModuleCtrl::OnCancelButtonClick(wxCommandEvent& event) {
	mainWindow->CancelAddOrEdit();
}

bool TestModuleCtrl::WasTestExtensionChosen() {
	int testmode = testModeChoice->GetSelection();
	if (testmode == 0 || testmode == 3) {
		return radioTypesHTML->GetValue() || radioTypesDOCX->GetValue() || radioTypesCSV->GetValue();
	} else if (testmode == 1) {
		return radioTypesHTML2->GetValue() || radioTypesCSV2->GetValue();
	}
	return true;
}

void TestModuleCtrl::OnSaveButtonClick(wxCommandEvent& event)
{
	TestSetup test = GetTestSetup();
	if (!IsDestinationIPCorrect(test.destinationIP)) {
		wxMessageBox(wxString::Format(wxT("Destination IP '%s' is not valid IP address"), test.destinationIP));
	} else if (!WasTestExtensionChosen()) {
		wxMessageBox(wxT("Please choose report file name extension"));
	} else {
		if (addMode) {
			mainWindow->AddTestSetup(test);
		} else {
			mainWindow->SaveTestSetup(test);
		}
	}
}

void TestModuleCtrl::UpdateReportFilename()
{
	wxDateTime time = wxDateTime::Now();
	wxString timeStr = time.Format(wxT("%Y.%m.%dT%Hh%Mm%Ss"));
	//wxString extension = wxT("");
	//if (radioTypesHTML->GetValue()) { extension = wxT(".html"); } else if (radioTypesDOCX->GetValue()) { extension = wxT(".docx"); } else if (radioTypesCSV->GetValue()) { extension = wxT(".csv"); }
	//wxString extension2 = wxT("");
	//if (radioTypesHTML2->GetValue()) { extension2 = wxT(".html"); } else if (radioTypesCSV2->GetValue()) { extension2 = wxT(".csv"); }
	switch (testModeChoice->GetSelection()) {
	case 0:
		//reportWithRadioText->SetValue(wxString::Format("End-to-End_%s(%s)%s", destinationIPText->GetValue(), timeStr, extension));
		reportWithRadioText->SetValue(wxString::Format("End-to-End_%s(%s)", destinationIPText->GetValue(), timeStr));
		break;
	case 1:
		//reportWithRadioText2->SetValue(wxString::Format("Link-Troubleshoot_%s(%s)%s", destinationIPText->GetValue(), timeStr, extension2));
		reportWithRadioText2->SetValue(wxString::Format("Link-Troubleshoot_%s(%s)", destinationIPText->GetValue(), timeStr));
		break;
	case 2:
		break;
	case 3:
		//reportWithRadioText->SetValue(wxString::Format("RTP-Transmitter_%s(port%i)(%s)%s", destinationIPText->GetValue(), transmitUDPText->GetValue(), timeStr, extension));
		reportWithRadioText->SetValue(wxString::Format("RTP-Transmitter_%s(port%i)(%s)", destinationIPText->GetValue(), transmitUDPText->GetValue(), timeStr));
		break;
	case 4:
		break;
	case 5:
		reportText->SetValue(wxString::Format("TCP-Transmitter_%s(port%i)(%s).html", destinationIPText->GetValue(), transmitTCPText->GetValue(), timeStr));
		break;
	case 6:
		reportText->SetValue(wxString::Format("UDP-Firewall_%s(port%i)(%s).txt", destinationIPText->GetValue(), destinationUDPText->GetValue(), timeStr));
		break;
	case 7:
		reportText->SetValue(wxString::Format("DSCP-Loss_%s(%s).txt", destinationIPText->GetValue(), timeStr));
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
		SetRtpTransmitter();
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
	durationMOS->Hide();
	duration->Hide();
	chunk->Hide();
	randUse->Hide();
	report->Hide();
	reportWithRadio->Hide();
	reportWithRadio2->Hide();
	save->Hide();
}

void TestModuleCtrl::SetEndToEnd()
{
	HideAllInputPanels();
	destinationIP->Show();
	codec->Show();
	numberOfCalls->Show();
	dscp->Show();
	durationMOS->Show();
	duration->Show();
	reportWithRadio->Show();
	save->Show();
	testStaticSizer->Layout();
}

void TestModuleCtrl::SetLinkTroubleshooting()
{
	HideAllInputPanels();
	destinationIP->Show();
	delay->Show();
	duration->Show();
	reportWithRadio2->Show();
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

void TestModuleCtrl::SetRtpTransmitter()
{
	HideAllInputPanels();
	destinationIP->Show();
	transmitUDP->Show();
	codec->Show();
	numberOfCalls->Show();
	dscp->Show();
	durationMOS->Show();
	duration->Show();
	reportWithRadio->Show();
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
