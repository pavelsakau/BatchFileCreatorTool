#include "Toolbar.h"
#include "BitmapHelper.h"
#include "resource.h"
#include <wx/sysopt.h>

Toolbar::Toolbar(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	//wxSystemOptions::SetOption("msw.remap", 2);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	toolbar = new wxToolBar(this, wxID_ANY);
	//toolbar->SetToolBitmapSize(wxSize(100, 100));

	wxBitmap publish(BitmapHelper::GetResourceById(PUBLISHICON), wxBITMAP_TYPE_ICO_RESOURCE);

	toolbar->AddTool(wxID_EXECUTE, wxT("Publish"), publish, wxT("Publish"));

	toolbar->Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Toolbar::OnToolbarClick));

	toolbar->Realize();
	hbox->Add(toolbar, 1, wxEXPAND | wxALL);

	SetSizer(hbox);
}

void Toolbar::EnableTool(int toolid, bool enable) {
	this->toolbar->EnableTool(toolid, enable);
}

void Toolbar::OnToolbarClick(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}
