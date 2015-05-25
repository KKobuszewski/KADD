#include <fstream>

void lab4(){
  std::fstream plik;
  plik.open( "NumericalRecipes.txt", std::ios::in | std::ios::out );
  
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1000,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  
  c1->Divide(2,1);
  
  //Zakres
  Double_t x_min = 0.0;
  Double_t x_max = 50.0;
  Int_t num_bins = 100;
  Double_t bin_width = (x_max - x_min)/num_bins;
  
  //Stale
  Double_t a = 5.0;
  
  TF1* f1 = new TF1("f1","exp(-x/[0])/[0]",x_min-0.00001,x_max);
  f1->SetParameter(0,a);
  
  TH1D *h1 = new TH1D("h1","generator LCG",num_bins,x_min,x_max);
  TH1D *h2 = new TH1D("h2","generator TRandom",num_bins,x_min,x_max);
  
  c1->cd(1);
  c1_1->SetGrid();
  
  if (plik.good()){
      while ( !plik.eof() ){
	Double_t value =0.0;
	plik>>value;
	if (value != 0.0){
	  h1->Fill(-a*log(value));
	}
	h2->Fill(-a*log(gRandom->Uniform(0.,1.)));
      }
      plik.close();
  }
  
  h1->Scale(1./(bin_width*h1->Integral()));
  h1->GetXaxis()->SetTitle("x");
  h1->GetYaxis()->SetTitle("g(x)");
  h1->SetFillColor(kGreen);
  h1->SetFillStyle(3003);
  h1->Draw();
  f1->Draw("same");
  
  TLegend *leg1 = new TLegend(0.5,0.4,0.9,0.75);
  //leg1->SetHeader("Matching histogram and teoretical density of probability");
  leg1->AddEntry(h1,"Histogram","f");
  leg1->AddEntry(f1,"Teoria","l");
  leg1->Draw("same");
  
  c1->cd(2);
  c1_2->SetGrid();
  
  h2->GetXaxis()->SetTitle("x");
  h2->GetYaxis()->SetTitle("g(x)");
  h2->Scale(1./(h2->Integral(1,num_bins,"width"))); // Sposob na normowanie calki
  h2->SetFillColor(kRed);
  h2->SetFillStyle(3003);
  h2->Draw();
  h2->GetXaxis()->SetTitle("x");
  h2->GetYaxis()->SetTitle("g(x)");
  f1->Draw("same");
  
  TLegend *leg2 = new TLegend(0.5,0.4,0.9,0.75);
  //leg2->SetHeader("Matching histogram and teoretical density of probability");
  leg2->AddEntry(h2,"Histogram","f");
  leg2->AddEntry(f1,"Teoria","l");
  leg2->Draw("same");
}