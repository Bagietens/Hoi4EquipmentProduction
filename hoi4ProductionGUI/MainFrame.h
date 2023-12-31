#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:

	void BindEventHandlers();
	void CreateControls();

	void OnCalculateButtonClicked(wxCommandEvent& evt);

	void OnExitButtonClicked(wxCloseEvent& evt);

	void OnTextChangedEfficiency(wxCommandEvent& evt);

	void UseDataFromInputs();

	wxPanel* panel;
	wxStaticText* firstlineTextProcentage;
	wxStaticText* secondlineTextProcentage;
	wxStaticText* thirdlineTextProcentage;
	wxStaticText* forthlineTextProcentage;
	
	wxStaticText* headlineText;
	wxStaticText* firstlineText;
	wxStaticText* secondlineText;
	wxStaticText* thirdlineText;
	wxStaticText* forthlineText;
	wxStaticText* TimeToProdCapText;

	wxSpinCtrl* factoryCount;
	wxTextCtrl* cost;
	wxTextCtrl* prodCap;
	wxTextCtrl* prodBase;
	wxTextCtrl* factoryOutput;
	wxTextCtrl* prodGrowth;
	wxTextCtrl* requested;
	wxButton* calculateButton;
};

