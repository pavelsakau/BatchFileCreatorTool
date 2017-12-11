#include "Application.h"
#include "BitmapHelper.h"
#include "resource.h"

bool Application::OnInit()
{
	wxInitAllImageHandlers();

	int desktopWidth = wxSystemSettings::GetMetric(wxSYS_SCREEN_X) ;
	int desktopHeight = wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) ;
	mainWindow = new MainWindow(nullptr, wxID_ANY, "Batch File Creator Tool", wxDefaultPosition, wxSize(desktopWidth*0.55 > 900 ? desktopWidth*0.55: 900, desktopHeight*0.65));

	mainWindow->SetIcon(wxIcon(BitmapHelper::GetResourceById(APPLICATIONICON), wxBITMAP_TYPE_ICO_RESOURCE));

	mainWindow->Center();
	mainWindow->Raise();
	mainWindow->Show();

	return true;
}

IMPLEMENT_APP(Application);