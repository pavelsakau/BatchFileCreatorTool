#include "Application.h"

bool Application::OnInit()
{
	wxInitAllImageHandlers();

	//int desktopWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X) ;
	//int desktopHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) ;
	mainWindow = new MainWindow(nullptr, wxID_ANY, "Batch File Creator Tool", wxDefaultPosition, wxSize(800, 640));

	mainWindow->Center();
	mainWindow->Raise();
	mainWindow->Show();

	return true;
}

IMPLEMENT_APP(Application);