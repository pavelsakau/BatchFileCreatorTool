#include "Toolbar.h"
#include "BitmapHelper.h"
#include "resource.h"
#include <wx/sysopt.h>

Toolbar::Toolbar(wxWindow* parent, const wxString& title) : wxPanel(parent, wxID_ANY)
{
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL | wxNO_BORDER | wxTB_FLAT | wxTB_NODIVIDER);

	wxBitmap publish(BitmapHelper::GetResourceById(PUBLISHICON), wxBITMAP_TYPE_ICO_RESOURCE);
	wxBitmap addicon(BitmapHelper::GetResourceById(ICONPLUS), wxBITMAP_TYPE_ICO_RESOURCE);
	wxBitmap editicon(BitmapHelper::GetResourceById(ICONEDIT), wxBITMAP_TYPE_ICO_RESOURCE);
	wxBitmap minusicon(BitmapHelper::GetResourceById(ICONMINUS), wxBITMAP_TYPE_ICO_RESOURCE);

	//wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);
	toolbar->SetToolBitmapSize(wxSize(46, 46));
	toolbar->AddTool(wxID_EXECUTE, wxT("Publish"), publish, wxT("Publish"));
	toolbar->AddTool(wxID_ADD, wxT("Add"), addicon, wxT("Add test"));
	toolbar->AddTool(wxID_EDIT, wxT("Edit"), editicon, wxT("Edit test"));
	toolbar->AddTool(wxID_REMOVE, wxT("Delete"), minusicon, wxT("Delete test"));
	toolbar->Connect(wxID_ANY, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(Toolbar::OnToolbarClick));
	toolbar->Realize();
	//toolbarSizer->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxRIGHT, 10));
	hbox->Add(toolbar, wxSizerFlags(0).Align(wxALIGN_LEFT).Border(wxRIGHT));
	hbox->AddStretchSpacer(7);

	wxBoxSizer* radioSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* serverAddrSizer = new wxBoxSizer(wxHORIZONTAL);
	serverRadio = new wxRadioButton(this, wxID_ANY, wxT("TotalView server"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	serverRadioId = serverRadio->GetId();
	serverAddrSizer->Add(serverRadio, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	serverAddrText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	serverAddrTextID = serverAddrText->GetId();
	serverAddrSizer->Add(serverAddrText, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());

	//serverAddrSizer->AddStretchSpacer(7);

	radioSizer->Add(serverAddrSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP, 3).Expand());
	//toolbarSizer->Add(serverAddrSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP, 3).Expand());
	//hbox->Add(toolbarSizer, wxSizerFlags(0).Align(wxALIGN_TOP).Expand());

	wxBoxSizer* customerSizer = new wxBoxSizer(wxHORIZONTAL);

	//wxBoxSizer* buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	//addTestButton = new wxButton(this, wxID_ADD, "Add");
	//buttonsSizer->Add(addTestButton, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	//editTestButton = new wxButton(this, wxID_EDIT, "Edit");
	//buttonsSizer->Add(editTestButton, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	//deleteTestButton = new wxButton(this, wxID_DELETE, "Delete");
	//buttonsSizer->Add(deleteTestButton, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL));
	//customerSizer->Add(buttonsSizer, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	customerRadio = new wxRadioButton(this, wxID_ANY, wxT("Subscription customer number:"), wxDefaultPosition, wxDefaultSize);
	customerRadioId = customerRadio->GetId();
	customerSizer->Add(customerRadio, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	customerNumberText = new wxTextCtrl(this, wxID_ANY);
	customerNumberTextID = customerNumberText->GetId();
	customerSizer->Add(customerNumberText, wxSizerFlags(1).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Expand());

	//customerSizer->AddStretchSpacer(7);

	radioSizer->Add(customerSizer, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_TOP).Border(wxTOP | wxBOTTOM, 3).Expand());

	hbox->Add(radioSizer, wxSizerFlags(25).Border(wxRIGHT, 3).Expand());

	wxBoxSizer* serverPortSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* serverAddrSizerL1 = new wxBoxSizer(wxHORIZONTAL);
	serverPort = new wxStaticText(this, wxID_ANY, wxT("Port:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	serverAddrSizerL1->Add(serverPort, wxSizerFlags(0).Align(wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL).Border(wxRIGHT, 5));

	serverPortText = new wxTextCtrl(this, wxID_ANY, wxT("8084"));
	serverPortTextID = serverPortText->GetId();
	serverAddrSizerL1->Add(serverPortText, wxSizerFlags(3).Align(wxALIGN_CENTER_VERTICAL).Expand());
	serverAddrSizerL1->AddStretchSpacer(7);
	serverPortSizer->Add(serverAddrSizerL1, wxSizerFlags(0).Border(wxTOP | wxBOTTOM, 3).Expand());

	hbox->Add(serverPortSizer, wxSizerFlags(12).Expand());

	//hbox->Add(customerSizer, wxSizerFlags(0).Border(wxBOTTOM, 3).Expand());

	SetSizer(hbox);
	//wxMessageBox(wxString::Format("%i - %i", toolbar->GetSize().GetHeight(), this->GetSize().GetHeight()));
	//toolbar->SetSize(wxSize(toolbar->GetSize().GetWidth(), this->GetSize().GetHeight()));

	serverRadio->Connect(serverRadioId, wxEVT_RADIOBUTTON, wxCommandEventHandler(Toolbar::RadioClick), nullptr, this);
	customerRadio->Connect(customerRadioId, wxEVT_RADIOBUTTON, wxCommandEventHandler(Toolbar::RadioClick), nullptr, this);
	serverAddrText->Connect(wxID_ANY, wxEVT_TEXT, wxCommandEventHandler(Toolbar::OnTextChange), nullptr, this);
	serverPortText->Connect(wxID_ANY, wxEVT_TEXT, wxCommandEventHandler(Toolbar::OnTextChange), nullptr, this);
	customerNumberText->Connect(wxID_ANY, wxEVT_TEXT, wxCommandEventHandler(Toolbar::OnTextChange), nullptr, this);
	//addTestButton->Connect(wxID_ANY, wxEVT_BUTTON, wxCommandEventHandler(Toolbar::OnButtonClick), nullptr, this);
	//editTestButton->Connect(wxID_ANY, wxEVT_BUTTON, wxCommandEventHandler(Toolbar::OnButtonClick), nullptr, this);
	//deleteTestButton->Connect(wxID_ANY, wxEVT_BUTTON, wxCommandEventHandler(Toolbar::OnButtonClick), nullptr, this);

	SetCustomerNoVisible(false);
	SetAddButtonEnable(false);
	SetEditButtonEnable(false);
	SetDeleteButtonEnable(false);
}

wxWindowID Toolbar::GetServerTextID() {
	return serverAddrTextID;
}

wxWindowID Toolbar::GetServerPortID() {
	return serverPortTextID;
}

wxWindowID Toolbar::GetCustomerTextID() {
	return customerNumberTextID;
}

void Toolbar::OnTextChange(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}

void Toolbar::SetAddButtonEnable(bool flag) {
	toolbar->EnableTool(wxID_ADD, flag);
	//editTestButton->Enable(flag);
}

void Toolbar::SetEditButtonEnable(bool flag) {
	toolbar->EnableTool(wxID_EDIT, flag);
	//editTestButton->Enable(flag);
}

void Toolbar::SetDeleteButtonEnable(bool flag) {
	//deleteTestButton->Enable(flag);
	toolbar->EnableTool(wxID_REMOVE, flag);
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
	event.Skip();
	event.ShouldPropagate();
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
	toolbar->EnableTool(toolid, enable);
}

void Toolbar::OnToolbarClick(wxCommandEvent& event) {
	event.Skip();
	event.ShouldPropagate();
}
