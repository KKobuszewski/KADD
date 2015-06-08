#include <TGraphErrors.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>


	//https://root.cern.ch/drupal/content/how-fit-histograms-or-data-points

void generate_data(Double_t* x, Double_t* y, const Int_t n, void (*function) (Double_t*, Double_t*, Int_t));
void theoretical(Double_t*, Double_t*, Int_t);

void graph_from_file(TString fnameData = "data.txt"){

	float xmin = 0, xmax = 8.5;
	float ymin = 0.0, ymax = 0.2;
	
	const Int_t n = 100;
	Double_t* x1 = new Double_t[n];
	Double_t* y1 = new Double_t[n];
	
	TGraphErrors* grErr = new TGraphErrors(fnameData,"%lg %lg %lg");
	grErr->SetTitle("Data vs p_{T}");
	grErr->SetLineColor(kBlack);
	grErr->SetMarkerColor(kBlack);
	grErr->SetMarkerStyle(25);
	grErr->SetMarkerSize(0.5);
	
	
	TCanvas* c1 = new  TCanvas("Dane","Dane",800,600);
	c1->DrawFrame(0.,0.,1200.,180.);
	c1->SetGrid();

	grErr->Draw("AP");
	grErr->GetYaxis()->SetTitle("Ilosc kwantow gamma N");
	grErr->GetXaxis()->SetTitle("t [s]");
	//	grErr->GetXaxis()->SetLimits(Xmin,Xmax);
	//	grErr->GetYaxis()->SetRangeUser(Ymin,Ymax);
	
	
	//Fitting function
	//TF1* fExpo = new TF1("fExpo","[0]*exp([1]*x)",0,500);
	//fExpo->SetParameter(170.,1);
	
	//
	TLine* lZero = new TLine(xmin,0,xmax,0);
	lZero->Draw();
	
	//Defining and drawing legend
	TLegend *leg = new TLegend(0.2,0.7,0.4,0.80);
	leg->SetFillStyle(0);
	leg->SetTextSize(0.04);
	leg->AddEntry(grErr,"Data","p");
	leg->AddEntry(fExpo,"Fitted curve","l");
	leg->Draw("same");
	
	TFitResultPtr frp = grErr->Fit("expo","F");
	//float a=frp->GetParameter(0);
	//float b=frp->GetParameter(1);
	//cout<<"Parametr a wynosi: "<<a<<endl<<"Parametr b wynosi: "<<b<<endl;
	
	c1->Modified();
	c1->Update();
}

/* ******************************** Jak zrobic by sie nie krzaczyl przy kompilacji ******************************** */

#ifndef __CINT__
int main(){
	macro1();
}
#endif