#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <wx/wx.h>
#include <wx/frame.h>
#include "Toolbar.h"
#include "TestStack.h"

class MainWindow : public wxFrame
{
private:
	Toolbar* toolbar;
	TestStack* stack;

public:
	MainWindow(wxWindow *parent,
		wxWindowID id,
		const wxString& title,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxDEFAULT_FRAME_STYLE,
		const wxString& name = wxFrameNameStr);

	void OnPublish(wxCommandEvent& event);
};

#endif
