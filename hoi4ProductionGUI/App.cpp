#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Hoi4 Production Checker");
	mainFrame->SetClientSize(600, 450);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}