#include "Toolbar.h"
#include "BitmapHelper.h"
#include "resource.h"
#include <wx/sysopt.h>

Toolbar::Toolbar(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER);

	wxBitmap publish(BitmapHelper::GetResourceById(PUBLISHICON), wxBITMAP_TYPE_ICO_RESOURCE);

	wxBoxSizer* toolbarSizer = new wxBoxSizer(wxVERTICAL);
	toolbar->AddTool(wxID_EXECUTE, wxT("Publish"), publish, wxT("Publish"));
	toolbar->Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Toolbar::OnToolbarClick));
	toolbar->Realize();
	toolbarSizer->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Expand());
	hbox->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxRIGHT, 10));

	wxBoxSizer* radioSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* serverAddrSizer = new wxBoxSizer(wxHORIZONTAL);
	serverRadio = new wxRadioButton(this, wxID_ANY, wxT("TotalView server"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	serverRadioId = serverRadio->GetId();
	serverAddrSizer->Add(serverRadio, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	serverAddrText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	serverAddrSizer->Add(serverAddrText, wxSizerFlags(10).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	serverPort = new wxStaticText(this, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	serverAddrSizer->Add(serverPort, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	serverPortText = new wxTextCtrl(this, wxID_ANY, wxT("8084"));
	serverAddrSizer->Add(serverPortText, wxSizerFlags(3).Align(wxALIGN_CENTER_VERTICAL));

	serverAddrSizer->AddStretchSpacer(7);

	radioSizer->Add(serverAddrSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP, 3).Expand());

	wxBoxSizer* customerSizer = new wxBoxSizer(wxHORIZONTAL);
	customerRadio = new wxRadioButton(this, wxID_ANY, wxT("Subscription customer number:"), wxDefaultPosition, wxDefaultSize);
	customerRadioId = customerRadio->GetId();
	customerSizer->Add(customerRadio, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	customerNumberText = new wxTextCtrl(this, wxID_ANY);
	customerSizer->Add(customerNumberText, wxSizerFlags(5).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));

	customerSizer->AddStretchSpacer(15);

	radioSizer->Add(customerSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP | wxBOTTOM, 3).Expand());

	//wxBoxSizer* box2 = new wxBoxSizer(wxHORIZONTAL);
	//wxStaticText* serverAddr = new wxStaticText(this, wxID_ANY, wxT("TotalView server address"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	//box2->Add(serverAddr, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 30));
	//serverAddrText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	//box2->Add(serverAddrText, wxSizerFlags(10).Align(wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 10));

	//customerNumber = new wxStaticText(this, wxID_ANY, wxT("Customer number"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
	//box2->Add(customerNumber, wxSizerFlags(0).Align(wxALIGN_CENTER_VERTICAL	).Border(wxLEFT, 30).ReserveSpaceEvenIfHidden());
	//customerNumberText = new wxTextCtrl(this, wxID_ANY);
	//box2->Add(customerNumberText, wxSizerFlags(5).Align(wxALIGN_CENTER_VERTICAL).Border(wxLEFT, 10).ReserveSpaceEvenIfHidden());

	//box2->AddStretchSpacer(1);

	//hbox->Add(box2, wxSizerFlags(1).Expand());
	hbox->Add(radioSizer, wxSizerFlags(1).Expand());

	SetSizer(hbox);

	//serverAddrText->Connect(wxEVT_TEXT, wxCommandEventHandler(Toolbar::ServerAddrTextChanged), nullptr, this);
	serverRadio->Connect(serverRadioId, wxEVT_RADIOBUTTON, wxCommandEventHandler(Toolbar::RadioClick), nullptr, this);
	customerRadio->Connect(customerRadioId, wxEVT_RADIOBUTTON, wxCommandEventHandler(Toolbar::RadioClick), nullptr, this);

	SetCustomerNoVisible(false);
}

void Toolbar::RadioClick(wxCommandEvent& event) {
	SetCustomerNoVisible(!(event.GetId() == serverRadioId));
}

void Toolbar::ServerAddrTextChanged(wxCommandEvent& event) {
	//SetCustomerNoVisible(wxString("sub01.nlsubscription.com:443").CompareTo(serverAddrText->GetValue()) == 0);
}

wxString Toolbar::GetServerAddrText() {
	return serverAddrText->GetValue();
}

wxString Toolbar::GetPortText() {
	return serverPortText->GetValue();
}

wxString Toolbar::GetCustomerNoText() {
	return customerNumberText->GetValue();
}

bool Toolbar::IsCustomerNoVisible() {
	return customerNumberText->IsEnabled();
}

void Toolbar::SetCustomerNoVisible(bool isVisible) {
	customerNumberText->Enable(isVisible);

	serverAddrText->Enable(!isVisible);
	serverPort->Enable(!isVisible);
	serverPortText->Enable(!isVisible);
}

void Toolbar::EnableTool(int toolid, bool enable) {
	this->toolbar->EnableTool(toolid, enable);
}

void Toolbar::OnToolbarClick(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}
