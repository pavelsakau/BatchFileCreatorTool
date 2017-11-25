#ifndef TEST_SETUP_H_
#define TEST_SETUP_H_
#include <wx/wx.h>

class TestSetup
{
public:
	int id;
	int choice;
	
	wxString destinationIP;
	int delay;
	wxString remote;
	int listenUDP;
	int transmitUDP;
	int destinationUDP;
	int listenTCP;
	int transmitTCP;
	int codec;
	int numberOfCalls;
	int dscp;
	wxString randUse;
	bool enableDSCP;
	int duration;
	int chunk;
	wxString report;

	bool dscpCheck;
	bool randUseCheck;
	bool enableDSCPCheck;

	wxString GetReportFilenameForPublish()
	{
		wxString filename;
		switch (choice) {
		case 0:
			filename = wxString::Format("End-to-End_%s_DSCP%i(%s).htm", destinationIP, dscp, wxT("%DATE%%TIME%"));
			break;
		case 1:
			filename = wxString::Format("Link-Troubleshoot_%s(%s).htm", destinationIP, wxT("%DATE%%TIME%"));
			break;
		case 2:
			break;
		case 3:
			filename = wxString::Format("RTP-Transmitter_%s(port%i)(%s).htm", destinationIP, transmitUDP, wxT("%DATE%%TIME%"));
			break;
		case 4:
			break;
		case 5:
			filename = wxString::Format("TCP-Transmitter_%s(port%i)(%s).htm", destinationIP, transmitTCP, wxT("%DATE%%TIME%"));
			break;
		case 6:
			filename = wxString::Format("UDP-Firewall_%s(port%i)(%s).txt", destinationIP, destinationUDP, wxT("%DATE%%TIME%"));
			break;
		case 7:
			filename = wxString::Format("DSCP-Loss_%s_DSCP%i(%s).txt", destinationIP, dscp, wxT("%DATE%%TIME%"));
			break;
		}
		return wxString::Format(wxT("\"%s\""), filename);
	}
};

#endif
