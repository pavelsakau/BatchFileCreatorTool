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
	bool enableDSCP;
	int duration;
	int chunk;
	wxString report;
	bool dscpCheck;
	bool randUseCheck;

	bool EqualTo(const TestSetup& test) {
		return (id == test.id && choice == test.choice && destinationIP.compare(test.destinationIP) == 0 && delay == test.delay && remote.compare(test.remote) == 0 && 
			listenUDP == test.listenUDP && transmitUDP == test.transmitUDP && destinationUDP == test.destinationUDP && listenTCP == test.listenTCP && transmitTCP == test.transmitTCP &&
			codec == test.codec && numberOfCalls == test.numberOfCalls && dscp == test.dscp && enableDSCP == test.enableDSCP && duration == test.duration && chunk == test.chunk && 
			dscpCheck == test.dscpCheck && randUseCheck == test.randUseCheck);
	}

	wxString GetReportFilenameForPublish()
	{
		wxString filename;
		switch (choice) {
		case 0:
			filename = wxString::Format("End-to-End_%s_DSCP%i(%s).htm", destinationIP, dscp, wxT("%CURRENT_DATE%%CURRENT_TIME%"));
			break;
		case 1:
			filename = wxString::Format("Link-Troubleshoot_%s(%s).htm", destinationIP, wxT("%CURRENT_DATE%%CURRENT_TIME%"));
			break;
		case 2:
			break;
		case 3:
			filename = wxString::Format("RTP-Transmitter_%s(port%i)(%s).htm", destinationIP, transmitUDP, wxT("%CURRENT_DATE%%CURRENT_TIME%"));
			break;
		case 4:
			break;
		case 5:
			filename = wxString::Format("TCP-Transmitter_%s(port%i)(%s).htm", destinationIP, transmitTCP, wxT("%CURRENT_DATE%%CURRENT_TIME%"));
			break;
		case 6:
			filename = wxString::Format("UDP-Firewall_%s(port%i)(%s).txt", destinationIP, destinationUDP, wxT("%CURRENT_DATE%%CURRENT_TIME%"));
			break;
		case 7:
			filename = wxString::Format("DSCP-Loss_%s_DSCP%i(%s).txt", destinationIP, dscp, wxT("%CURRENT_DATE%%CURRENT_TIME%"));
			break;
		}
		return wxString::Format(wxT("\"%s\""), filename);
	}
};

#endif
