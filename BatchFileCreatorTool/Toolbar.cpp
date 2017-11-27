#include "Toolbar.h"
#include "BitmapHelper.h"
#include "resource.h"
#include <wx/sysopt.h>

Toolbar::Toolbar(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *hbox = new wxBoxSizer(wxVERTICAL);
	toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER);

	wxBitmap publish(BitmapHelper::GetResourceById(PUBLISHICON), wxBITMAP_TYPE_ICO_RESOURCE);

	wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);
	toolbar->AddTool(wxID_EXECUTE, wxT("Publish"), publish, wxT("Publish"));
	toolbar->Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Toolbar::OnToolbarClick));
	toolbar->Realize();
	toolbarSizer->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxRIGHT, 10));
	//hbox->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxRIGHT, 10));

	//wxBoxSizer* radioSizer = new wxBoxSizer(wxVERTICAL);

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

	//radioSizer->Add(serverAddrSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP, 3).Expand());
	toolbarSizer->Add(serverAddrSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP, 3).Expand());
	hbox->Add(toolbarSizer, wxSizerFlags(0).Align(wxALIGN_TOP).Expand());

	wxBoxSizer* customerSizer = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	addTestButton = new wxButton(this, wxID_ADD, "Add");
	buttonsSizer->Add(addTestButton, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	editTestButton = new wxButton(this, wxID_EDIT, "Edit");
	buttonsSizer->Add(editTestButton, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	deleteTestButton = new wxButton(this, wxID_DELETE, "Delete");
	buttonsSizer->Add(deleteTestButton, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	customerSizer->Add(buttonsSizer, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	customerRadio = new wxRadioButton(this, wxID_ANY, wxT("Subscription customer number:"), wxDefaultPosition, wxDefaultSize);
	customerRadioId = customerRadio->GetId();
	customerSizer->Add(customerRadio, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	customerNumberText = new wxTextCtrl(this, wxID_ANY);
	customerSizer->Add(customerNumberText, wxSizerFlags(8).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));

	customerSizer->AddStretchSpacer(9);

	//radioSizer->Add(customerSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP | wxBOTTOM, 3).Expand());

	//hbox->Add(radioSizer, wxSizerFlags(1).Expand());
	hbox->Add(customerSizer, wxSizerFlags(0).Border(wxBOTTOM, 3).Expand());

	SetSizer(hbox);

	serverRadio->Connect(serverRadioId, wxEVT_RADIOBUTTON, wxCommandEventHandler(Toolbar::RadioClick), nullptr, this);
	customerRadio->Connect(customerRadioId, wxEVT_RADIOBUTTON, wxCommandEventHandler(Toolbar::RadioClick), nullptr, this);
	addTestButton->Connect(wxID_ANY, wxEVT_BUTTON, wxCommandEventHandler(Toolbar::OnButtonClick), nullptr, this);
	editTestButton->Connect(wxID_ANY, wxEVT_BUTTON, wxCommandEventHandler(Toolbar::OnButtonClick), nullptr, this);
	deleteTestButton->Connect(wxID_ANY, wxEVT_BUTTON, wxCommandEventHandler(Toolbar::OnButtonClick), nullptr, this);

	SetCustomerNoVisible(false);
	SetEditButtonEnable(false);
	SetDeleteButtonEnable(false);
}

void Toolbar::SetEditButtonEnable(bool flag) {
	editTestButton->Enable(flag);
}

void Toolbar::SetDeleteButtonEnable(bool flag) {
	deleteTestButton->Enable(flag);
}

void Toolbar::OnButtonClick(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}

bool Toolbar::IsToolEnable(int toolid) {
	return this->toolbar->GetToolEnabled(toolid);
}

void Toolbar::RadioClick(wxCommandEvent& event) {
	SetCustomerNoVisible(!(event.GetId() == serverRadioId));
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
