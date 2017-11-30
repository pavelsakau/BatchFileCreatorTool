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
	bool addMode;

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
	wxPanel* durationMOS;
	wxPanel* duration;
	wxPanel* chunk;
	wxPanel* report;
	wxPanel* reportWithRadio;
	wxPanel* reportWithRadio2;
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
	wxSpinCtrlDouble* durationMOSText;
	wxSpinCtrl* durationText;
	wxSpinCtrl* chunkText;
	wxTextCtrl* reportText;
	wxTextCtrl* reportWithRadioText;
	wxTextCtrl* reportWithRadioText2;
	wxCheckBox* mosCheck;
	wxSpinCtrl* dscpText;

	//wxRadioButton* radioTypesHTML;
	//wxRadioButton* radioTypesDOCX;
	//wxRadioButton* radioTypesCSV;
	//wxRadioButton* radioTypesALL;

	//wxRadioButton* radioTypesHTML2;
	//wxRadioButton* radioTypesCSV2;
	//wxRadioButton* radioTypesALL2;

	wxCheckBox* radioTypesHTML;
	wxCheckBox* radioTypesDOCX;
	wxCheckBox* radioTypesCSV;

	wxCheckBox* radioTypesHTML2;
	wxCheckBox* radioTypesCSV2;

public:

	static const wxString END_TO_END_TEST_TEXT;
	static const wxString LINK_TROUBLESHOOTING_TEST_TEXT;
	static const wxString RTP_RECEIVER_TEXT;
	static const wxString RTP_TRANSMITTER_TEXT;
	static const wxString TCP_RECEIVER_TEXT;
	static const wxString TCP_TRANSMITTER_TEXT;
	static const wxString UDP_FIREWALL_TEST_TEXT;
	static const wxString DSCP_LOSS_TEST_TEXT;

	TestModuleCtrl(MainWindow* mainWindow, wxWindow *parent, wxWindowID winid = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxTAB_TRAVERSAL | wxNO_BORDER, const wxString& label = wxEmptyString, bool addMode = true);

	void TestChoiceChanged(wxCommandEvent& event);
	void OnSaveButtonClick(wxCommandEvent& event);
	void OnCancelButtonClick(wxCommandEvent& event);
	void OnDSCPCheck(wxCommandEvent& event);
	void OnReportNamePartChange(wxCommandEvent& event);
	void OnMosCheckbox(wxCommandEvent& event);
	void OnRadio1Click(wxCommandEvent& event);
	void OnRadio2Click(wxCommandEvent& event);

	void HideAllInputPanels();
	void SetEndToEnd();
	void SetLinkTroubleshooting();
	void SetRtpReceiver();
	void SetRtpTransmitter();
	void SetTcpReceiver();
	void SetTcpTransmitter();
	void SetUdpFirewall();
	void SetDscpLoss();

	void UpdateReportFilename();
	bool IsDestinationIPCorrect(const wxString& ip);
	bool WasTestExtensionChosen();

	TestSetup GetTestSetup();
	void LoadTestSetup(const TestSetup& test);
};

#endif
