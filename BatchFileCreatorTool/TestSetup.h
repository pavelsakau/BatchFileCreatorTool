#ifndef TEST_SETUP_H_
#define TEST_SETUP_H_

#include <wx/wx.h>

class TestSetup
{
public:
	int id;
	int choice;
	
	wxString destinationIP;
	wxString delay;
	wxString remote;
	wxString listenUDP;
	wxString transmitUDP;
	wxString destinationUDP;
	wxString listenTCP;
	wxString transmitTCP;
	wxString codec;
	wxString numberOfCalls;
	wxString dscp;
	wxString randUse;
	bool enableDSCP;
	wxString duration;
	wxString chunk;
	wxString report;

	bool dscpCheck;
	bool randUseCheck;
	bool enableDSCPCheck;
};

#endif
