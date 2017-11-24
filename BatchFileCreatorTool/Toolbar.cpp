#include "Toolbar.h"
#include "BitmapHelper.h"
#include "resource.h"
#include <wx/sysopt.h>

Toolbar::Toolbar(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER);

	wxBitmap publish(BitmapHelper::GetResourceById(PUBLISHICON), wxBITMAP_TYPE_ICO_RESOURCE);

	toolbar->AddTool(wxID_EXECUTE, wxT("Publish"), publish, wxT("Publish"));
	toolbar->Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Toolbar::OnToolbarClick));
	toolbar->Realize();
	hbox->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT));

	wxBoxSizer* box2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* serverAddr = new wxStaticText(this, wxID_ANY, wxT("TotalView server address"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	box2->Add(serverAddr, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 30));
	serverAddrText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	box2->Add(serverAddrText, wxSizerFlags(20).Align(wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 10));

	customerNumber = new wxStaticText(this, wxID_ANY, wxT("Customer number"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	box2->Add(customerNumber, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL	).Border(wxLEFT, 30).ReserveSpaceEvenIfHidden());
	customerNumberText = new wxTextCtrl(this, wxID_ANY);
	box2->Add(customerNumberText, wxSizerFlags(5).Align(wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 10).ReserveSpaceEvenIfHidden());

	SetCustomerNoVisible(false);

	box2->AddStretchSpacer(1);

	hbox->Add(box2, wxSizerFlags(1).Expand());

	SetSizer(hbox);

	serverAddrText->Connect(wxEVT_TEXT, wxCommandEventHandler(Toolbar::ServerAddrTextChanged), nullptr, this);
}

void Toolbar::ServerAddrTextChanged(wxCommandEvent& event)
{
	SetCustomerNoVisible(wxString("sub01.nlsubscription.com:443").CompareTo(serverAddrText->GetValue()) == 0);
}

wxString Toolbar::GetServerAddrText() {
	return serverAddrText->GetValue();
}

wxString Toolbar::GetCustomerNoText() {
	return customerNumberText->GetValue();
}

bool Toolbar::IsCustomerNoVisible() {
	return customerNumberText->IsShown();
}

void Toolbar::SetCustomerNoVisible(bool isVisible) {
	if (isVisible) {
		customerNumber->Show();
		customerNumberText->Show();
	} else {
		customerNumber->Hide();
		customerNumberText->Hide();
	}
}

void Toolbar::EnableTool(int toolid, bool enable) {
	this->toolbar->EnableTool(toolid, enable);
}

void Toolbar::OnToolbarClick(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}
