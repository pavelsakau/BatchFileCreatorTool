#ifndef TEST_SETUP_H_
#define TEST_SETUP_H_
#include <wx/wx.h>

class TestSetup
{
public:

	enum EXTENSION {HTML, DOCX, CSV, ALL};

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

	bool isMos;
	double mos;
	bool report1_HTML;
	bool report1_DOCX;
	bool report1_CSV;
	bool report2_HTML;
	bool report2_CSV;

	bool EqualTo(const TestSetup& test) {
		return (id == test.id && choice == test.choice && destinationIP.compare(test.destinationIP) == 0 && delay == test.delay && remote.compare(test.remote) == 0 && 
			listenUDP == test.listenUDP && transmitUDP == test.transmitUDP && destinationUDP == test.destinationUDP && listenTCP == test.listenTCP && transmitTCP == test.transmitTCP &&
			codec == test.codec && numberOfCalls == test.numberOfCalls && dscp == test.dscp && enableDSCP == test.enableDSCP && duration == test.duration && chunk == test.chunk && 
			dscpCheck == test.dscpCheck && randUseCheck == test.randUseCheck && isMos == test.isMos && mos == test.mos && report1_HTML == test.report1_HTML && report1_DOCX == test.report1_DOCX && 
			report1_CSV == test.report1_CSV && report2_HTML == test.report2_HTML && report2_CSV == test.report2_CSV);
	}

	wxString GetReportFilenameForPublish()
	{
		wxString filename = wxT("");
		wxString filenamebase;
		wxString extension = wxT("");
		switch (choice) {
		case 0:
			filenamebase = wxString::Format("End-to-End_%s(%s)", destinationIP, wxT("%CURRENT_DATE%T%CURRENT_TIME%"));
			if (report1_HTML) filename = filename + wxT(",") + wxString::Format("%s.html", filenamebase);
			if (report1_DOCX) filename = filename + wxT(",") + wxString::Format("%s.docx", filenamebase);
			if (report1_CSV) filename = filename + wxT(",") + wxString::Format("%s.csv", filenamebase);
			filename = filename.substr(1, filename.length() - 1);
			break;
		case 1:
			filenamebase = wxString::Format("Link-Troubleshoot_%s(%s)", destinationIP, wxT("%CURRENT_DATE%T%CURRENT_TIME%"));
			if (report2_HTML) filename = filename + wxT(",") + wxString::Format("%s.html", filenamebase);
			if (report2_CSV) filename = filename + wxT(",") + wxString::Format("%s.csv", filenamebase);
			filename = filename.substr(1, filename.length() - 1);
			break;
		case 2:
			break;
		case 3:
			filenamebase = wxString::Format("RTP-Transmitter_%s(port%i)(%s)", destinationIP, transmitUDP, wxT("%CURRENT_DATE%T%CURRENT_TIME%"));
			if (report1_HTML) filename = filename + wxT(",") + wxString::Format("%s.html", filenamebase);
			if (report1_DOCX) filename = filename + wxT(",") + wxString::Format("%s.docx", filenamebase);
			if (report1_CSV) filename = filename + wxT(",") + wxString::Format("%s.csv", filenamebase);
			filename = filename.substr(1, filename.length() - 1);
			break;
		case 4:
			break;
		case 5:
			filename = wxString::Format("TCP-Transmitter_%s(port%i)(%s).html", destinationIP, transmitTCP, wxT("%CURRENT_DATE%T%CURRENT_TIME%"));
			break;
		case 6:
			filename = wxString::Format("UDP-Firewall_%s(port%i)(%s).txt", destinationIP, destinationUDP, wxT("%CURRENT_DATE%T%CURRENT_TIME%"));
			break;
		case 7:
			filename = wxString::Format("DSCP-Loss_%s(%s).txt", destinationIP, wxT("%CURRENT_DATE%T%CURRENT_TIME%"));
			break;
		}
		return wxString::Format(wxT("\"%s\""), filename);
	}
};

#endif
