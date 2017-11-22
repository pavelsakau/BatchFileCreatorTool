#include "MainWindow.h"

MainWindow::MainWindow(wxWindow * parent, wxWindowID id, const wxString & title, const wxPoint & pos, const wxSize & size, long style, const wxString & name)
	: wxFrame(parent, id, title, pos, size, style, name)
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	toolbar = new Toolbar(this, wxT("Toolbar"));
	toolbar->EnableTool(wxID_EXECUTE, false);
	vbox->Add(toolbar, 0, wxTOP | wxEXPAND);

	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
	stack = new TestStack(this, wxT("TestStack"));
	hbox->Add(stack, 1, wxALL | wxEXPAND);
	vbox->Add(hbox, 1, wxALIGN_CENTER | wxEXPAND);

	SetSizer(vbox);

	Connect(wxID_EXECUTE, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MainWindow::OnPublish));
}

void MainWindow::OnPublish(wxCommandEvent& event) {
	wxMessageBox(wxT("Pulish"));
}