#ifndef TEST_MODULE_CTRL_H_
#define TEST_MODULE_CTRL_H_

#include <wx/wx.h>
#include <wx/statbox.h>
#include "TestSetup.h"
#include "MainWindow.h"
#include <wx/spinctrl.h>

class TestModuleCtrl : public wxPanel
{
private:
	MainWindow* mainWindow;

	wxStaticBoxSizer* testStaticSizer;
	wxChoice* testModeChoice;
	wxString staticLabel;
	wxPanel* destinationIP;
	wxPanel* delay;
	wxPanel* remote;
	wxPanel* listenUDP;
	wxPanel* transmitUDP;
	wxPanel* destinationUDP;
	wxPanel* listenTCP;
	wxPanel* transmitTCP;
	wxPanel* codec;
	wxPanel* numberOfCalls;
	wxPanel* dscp;
	wxPanel* randUse;
	wxPanel* enableDSCP;
	wxPanel* duration;
	wxPanel* chunk;
	wxPanel* report;
	wxPanel* save;
	wxCheckBox* dscpCheck;
	wxCheckBox* randUseCheck;
	wxCheckBox* enableDSCPCheck;

	wxTextCtrl* destinationIPText;
	wxSpinCtrl* delayText;
	wxTextCtrl* remoteText;
	wxSpinCtrl* listenUDPText;
	wxSpinCtrl* transmitUDPText;
	wxSpinCtrl* destinationUDPText;
	wxSpinCtrl* listenTCPText;
	wxSpinCtrl* transmitTCPText;
	wxChoice* codecText;
	wxSpinCtrl* numberOfCallsText;
	wxSpinCtrl* durationText;
	wxSpinCtrl* chunkText;
	wxTextCtrl* reportText;
	wxSpinCtrl* dscpText;

public:

	static const wxString END_TO_END_TEST_TEXT;
	static const wxString LINK_TROUBLESHOOTING_TEST_TEXT;
	static const wxString RTP_RECEIVER_TEXT;
	static const wxString RTP_TRANSMITTER_TEXT;
	static const wxString TCP_RECEIVER_TEXT;
	static const wxString TCP_TRANSMITTER_TEXT;
	static const wxString UDP_FIREWALL_TEST_TEXT;
	static const wxString DSCP_LOSS_TEST_TEXT;

	TestModuleCtrl(MainWindow* mainWindow, wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER, const wxString& label = wxEmptyString);

	void TestChoiceChanged(wxCommandEvent& event);
	void OnSaveButtonClick(wxCommandEvent& event);
	void OnDSCPCheck(wxCommandEvent& event);
	void OnReportNamePartChange(wxCommandEvent& event);

	void HideAllInputPanels();
	void SetEndToEnd();
	void SetLinkTroubleshooting();
	void SetRtpReceiver();
	void SetTrpTransmitter();
	void SetTcpReceiver();
	void SetTcpTransmitter();
	void SetUdpFirewall();
	void SetDscpLoss();

	void UpdateReportFilename();
	bool IsDestinationIPCorrect(const wxString& ip);

	TestSetup GetTestSetup();
	void LoadTestSetup(const TestSetup& test);
};

#endif
