#include "MainFrame.h"
#include <wx/wx.h>
#include <math.h>
#include <vector>
#include <string>

float eff_growth(float prod_eff, float prod_cap, float prod_growth) {
	return (0.001 * pow(prod_cap, 2) / prod_eff) * (1 + prod_growth);
}

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {


	CreateControls();
	CreateStatusBar();
	BindEventHandlers();
}

void MainFrame::BindEventHandlers()
{
	calculateButton->Bind(wxEVT_BUTTON, &MainFrame::OnCalculateButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnExitButtonClicked, this);
	prodBase->Bind(wxEVT_TEXT, &MainFrame::OnTextChangedEfficiency, this);
	prodCap->Bind(wxEVT_TEXT, &MainFrame::OnTextChangedEfficiency, this);
	prodGrowth->Bind(wxEVT_TEXT, &MainFrame::OnTextChangedEfficiency, this);
}

void MainFrame::CreateControls()
{
	wxFont headlineFont(wxFontInfo(wxSize(0, 34)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 15)));
	wxFont supportFont(wxFontInfo(wxSize(0, 15)).Bold());

	panel = new wxPanel(this);

	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "HOI4 Production Checker",
		wxPoint(0, 22), wxSize(600, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);

	factoryCount = new wxSpinCtrl(panel, wxID_ANY, "", wxPoint(80, 80), wxSize(60, -1));
	prodCap = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(480, 80), wxSize(60, -1));
	firstlineText = new  wxStaticText(panel, wxID_ANY, "Amount of Factories        Production Cap", wxPoint(180, 80), wxSize(300, -1));
	firstlineTextProcentage = new wxStaticText(panel, wxID_ANY," %", wxPoint(550,80), wxSize(300,-1));
	
	
	

	cost = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(80, 150), wxSize(60, -1));
	prodBase = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(480, 150), wxSize(60, -1));
	secondlineText = new  wxStaticText(panel, wxID_ANY, "Cost                                Production Base", wxPoint(180, 150), wxSize(300, -1));
	secondlineTextProcentage = new wxStaticText(panel, wxID_ANY, " %", wxPoint(550, 150), wxSize(300, -1));


	requested = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(80, 220), wxSize(60, -1));
	factoryOutput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(480, 220), wxSize(60, -1));
	thirdlineText = new  wxStaticText(panel, wxID_ANY, "Requested Amount            Factory Output", wxPoint(180, 220), wxSize(300, -1));
	thirdlineTextProcentage = new wxStaticText(panel, wxID_ANY," %", wxPoint(550,220), wxSize(300,-1));


	prodGrowth = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(480, 290), wxSize(60, -1));
	forthlineText = new  wxStaticText(panel, wxID_ANY, "                                 Production Growth", wxPoint(180, 290), wxSize(300, -1));
	forthlineTextProcentage = new wxStaticText(panel, wxID_ANY," %", wxPoint(550,290), wxSize(300,-1));


	calculateButton = new wxButton(panel, wxID_ANY, "Calculate", wxPoint(80, 300), wxSize(100, 25));
	
	TimeToProdCapText = new wxStaticText(panel, wxID_ANY, "Time for Maximum Efficiency : ", wxPoint(280, 330), wxSize(300, -1), wxBOLD);
	TimeToProdCapText->SetFont(supportFont);
}

void MainFrame::OnCalculateButtonClicked(wxCommandEvent& evt)
{
	UseDataFromInputs();
}

void MainFrame::OnTextChangedEfficiency(wxCommandEvent& evt)
{
	wxString prodCapString = prodCap->GetValue();
	wxString prodBaseString = prodBase->GetValue();
	wxString prodGrowthString = prodGrowth->GetValue();
	if (prodCapString.IsEmpty() || prodBaseString.IsEmpty()) {
		return;
	}
	else if (prodGrowthString.IsEmpty()) {
		prodGrowthString = '0';
	}
	float prod_eff = wxAtof(prodBaseString) / 100;
	float prod_cap = wxAtof(prodCapString) / 100;
	float prod_growth = wxAtof(prodGrowthString) / 100;
	unsigned long days = 0;
	do {
		days++;
		prod_eff = prod_eff + eff_growth(prod_eff, prod_cap, prod_growth);
	} while (prod_eff < prod_cap);
	wxString text = "Time for Maximum Efficiency : ";
	text << days << " days";
	TimeToProdCapText->SetLabel(text);
}

void MainFrame::OnExitButtonClicked(wxCloseEvent& evt)
{
	int answer = wxMessageBox("Do you want to quit the program?","Confirm", wxYES_NO);
	if (answer == wxYES) {
		evt.Skip();
	}
}

void MainFrame::UseDataFromInputs()
{

	int factories = factoryCount->GetValue();
	wxString costString = cost->GetValue();
	wxString prodCapString = prodCap->GetValue();
	wxString prodBaseString = prodBase->GetValue();
	wxString factoryOutputString = factoryOutput->GetValue();
	wxString prodGrowthString = prodGrowth->GetValue();
	wxString requestedString = requested->GetValue();

	if (costString.IsEmpty() || prodCapString.IsEmpty() || prodBaseString.IsEmpty() || 
		factoryOutputString.IsEmpty() || prodGrowthString.IsEmpty()) {
		return;
	}
	float production = 0;
	float f_output = wxAtof(factoryOutputString) / 100;
	float prod_eff = wxAtof(prodBaseString) / 100;
	float prod_cap = wxAtof(prodCapString) / 100;
	float prod_growth = wxAtof(prodGrowthString) / 100;
	float cost = wxAtof(costString);
	float used_ic = cost;
	int requested = wxAtoi(requestedString);
	float requested_f = (float)requested;
    float produced = 0;
	unsigned long days = 0;
	do {
		days++;
		production = 4.5 * factories * (1 + f_output) * prod_eff;
		prod_eff = prod_eff + eff_growth(prod_eff, prod_cap, prod_growth);
		if (prod_eff > prod_cap) {
			prod_eff = prod_cap;
		};
		produced = produced + (production / cost);
	} while (produced<requested_f);
	unsigned long daysTest = 0;
	prod_eff = wxAtof(prodBaseString) / 100;
	produced = 0;
	do {
		daysTest++;
		production = 4.5 * factories * (1 + f_output) * prod_eff;
		//prod_eff = prod_eff + eff_growth(prod_eff, prod_cap, prod_growth);
		//if (prod_eff > prod_cap) {
		//	prod_eff = prod_cap;
		//};
		produced = produced + (production / cost);
	} while (produced < requested_f);
	wxLogStatus("Days : %d. Will show %d in logistics tab", days, daysTest);
}
