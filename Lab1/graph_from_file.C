#include <TGraphErrors.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>

void generate_data(Double_t* x, Double_t* y, const Int_t n, void (*function) (Double_t*, Double_t*, Int_t));
void theoretical(Double_t*, Double_t*, Int_t);

void graph_from_file(TString fnameData = "lab2_data.txt"){

	float Xmin = 0, Xmax = 8.5;
	float Ymin = 0.0, Ymax = 0.2;
	
	const Int_t n = 100;
	Double_t* x1 = new Double_t[n];
	Double_t* y1 = new Double_t[n];
	
	//Wygenerowac dane i wrzucic krzywa teoretyczna na wykres
	//Jak dopasowywac dane
	//https://root.cern.ch/drupal/content/how-fit-histograms-or-data-points
	
	TGraph gr = new TGraph();
	
	TGraphErrors* grErr = new TGraphErrors(fnameData,"%lg %lg %lg");
	grErr->SetTitle("Data vs p_{T}");
	grErr->SetLineColor(kBlack);
	grErr->SetMarkerColor(kBlack);
	grErr->SetMarkerStyle(25);
	grErr->SetMarkerSize(0.5);
	
	
	TCanvas* cAsymmetry = new  TCanvas("Asymmetry","Asymmetry",800,600);
	cAsymmetry->SetGrid();

	grErr->Draw("ap");
	grErr->GetYaxis()->SetTitle("Ilosc kwantow gamma N");
	grErr->GetXaxis()->SetTitle("t [s]");
	//	grErr->GetXaxis()->SetLimits(Xmin,Xmax);
	//	grErr->GetYaxis()->SetRangeUser(Ymin,Ymax);

	TLine* lZero = new TLine(Xmin,0,Xmax,0);
	lZero->Draw();

	TLegend *leg = new TLegend(0.2,0.7,0.4,0.80);
	leg->SetFillStyle(0);
	leg->SetTextSize(0.04);

	leg->AddEntry(grErr,"Data","p");
	leg->Draw("same");

	/*TF1* fExpo = new TF1("fExpo","expo",0,1200);
	grErr->Fit(fExpo);
	float a=fExpo->GetParameter(0);
	float b=fExpo->GetParameter(1);
	cout<<"Parametr a wynosi: "<<a<<endl<<"Parametr b wynosi: "<<b<<endl; */
	
	
}


//_____________________macro fitexample.C___________________________
Double_t fitf(Double_t *v, Double_t *par)
{
   Double_t arg = 0;
   if (par[2] != 0) arg = (v[0] - par[1])/par[2];
 
   Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}
 
void fitexample()
{
   TFile *f = new TFile("hsimple.root");
 
   TH1F *hpx = (TH1F*)f->Get("hpx");
 
   //create a function with 3 parameters in the range [-3,3]
   TF1 *func = new TF1("fit",fitf,-3,3,3);
   func->SetParameters(500,hpx->GetMean(),hpx->GetRMS());
   func->SetParNames("Constant","Mean_value","Sigma");
   hpx->Fit("fit");
}