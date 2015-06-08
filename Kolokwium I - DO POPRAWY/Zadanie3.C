#include <float.h>

void Zadanie3(){
  
  
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1000,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  
  
  //Zakres
  Double_t x_min = 2.0;
  Double_t x_max = 32.;
  cout<<"x_min"<<x_min<<"x_max"<<x_max<<endl;
  Int_t num_bins = 900;
  Double_t bin_width = (x_max - x_min)/num_bins;
  
    
  TF1* f1 = new TF1("f1","[0]*x^(-6)",x_min,x_max);
  Double_t c =160;//1./f1->Integral(x_min,x_max);
  cout<<"stala unormowania: "<<c<<endl;
  f1->SetParameter(0,160);
  
  TH1D *h2 = new TH1D("h2","Szukany rozklad",num_bins,x_min,x_max);
  
  
  Int_t N = 10000;
  while ( N > 0 ){
	N--;
	Double_t ksi = gRandom->Uniform(0.,1.);
	Double_t value = 1.-ksi;
	//cout<<"value"<<value<<endl;
	if (1./TMath::Power(value,0.2))
	  h2->Fill(2./TMath::Power(value,0.2)); // 2/(1-x)^(1/5)
  }
  cout<<"wylosowane"<<endl;    
  
  h2->Scale(1./(bin_width*h2->Integral()));
  h2->GetXaxis()->SetTitle("x");
  h2->GetYaxis()->SetTitle("g(x)");
  h2->GetXaxis()->SetRangeUser(1,5);
  h2->SetFillColor(kGreen);
  h2->SetFillStyle(3003);
  h2->Draw();
  f1->Draw("same");
  
  cout<<"3xWariancja: "<<3.*TMath::Sqrt(f1->Variance(x_min, x_max))<<endl;
  
  TLegend *leg1 = new TLegend(0.5,0.4,0.9,0.75);
  //leg1->SetHeader("Matching histogram and teoretical density of probability");
  leg1->AddEntry(h2,"Histogram","f");
  leg1->AddEntry(f1,"Teoria","l");
  leg1->Draw("same");
  
  
  
}