
#include <float.h>

void Zadanie1(){
  
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,700,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  
  c1->Divide(2,1);
  
  Double_t x_min = -20;
  Double_t x_max = 20;
  TF1* f1 = new TF1("f1","[0]*(x*x*exp(-0.5*x*x)/TMath::Sqrt(2*TMath::Pi()))",x_min,x_max);
  f1->SetParameter(0,1);
  Double_t C = 1./f1->Integral(x_min,x_max);
  cout<<"Stala unormowania C: "<<C<<"\n";
  f1->SetParameter(0,C);
  
  
  
  Int_t num_bins = 500;
  TH1D *h1 = new TH1D("h1","h1 bins integral",num_bins,x_min,x_max);
  for (int ii = 0; ii < num_bins; ii++)
    h1->SetBinContent(ii,f1->Integral(x_min,(-x_min+x_max)/num_bins*ii)*(x_max-x_min)/num_bins);
  
  c1->cd(1);
  c1_1->SetGrid();
  f1->SetTitle("rozklad gestosci prawdopoodobienstwa");
  f1->GetXaxis()->SetTitle("x");
  f1->GetYaxis()->SetTitle("p(x)");
  f1->Draw();
  
  c1->cd(2);
  h1->Draw();
  c1_2->SetGrid();
  h1->SetTitle("Dystrybuanta");
  h1->GetXaxis()->SetTitle("x");
  h1->GetYaxis()->SetTitle("F(x)");
  
  cout<<"Calki:"<<endl;
  
  
  TF1* f2 = new TF1("f2","[0]*(x*x*x*exp(-0.5*x*x)/TMath::Sqrt(2*TMath::Pi()))",-100.,100.); // E(X) = calka Stieltjesa XdF(X)
  TF1* f3 = new TF1("f3","[0]*(x*x*x*x*exp(-0.5*x*x)/TMath::Sqrt(2*TMath::Pi()))",-10.,10.); // E(X^2)
  f2->SetParameter(0,C);
  f3->SetParameter(0,C);
  
  cout<<"1. moment: "<<f2->Moment(1.,-100,100)<<endl;
  cout<<"1. moment: "<<f2->Integral(-100,100)<<endl;
  cout<<"2. moment: "<<f3->Moment(2.,-10,10)<<endl;
  cout<<"2. moment: "<<f3->Integral(-10,10)<<endl;
  
  Double_t calka = 0.;
  Double_t calka2 = 0.;
  Double_t dx = 0.01;
  Double_t x = x_min;
  while(x <= x_max ){
    
    calka += dx*f2->Eval(x);
    calka2 += dx*f3->Eval(x);
    x += dx;
    cout<<f3->Eval(x)<<endl;
    
  }
  
  cout<<endl;
  cout<<"calka1 "<<calka<<endl;
  cout<<"calka "<<calka2<<endl;
  cout<<endl;
  
  cout<<"Statystyka rozkladu\n";
  cout<<"Modalna\t\t\t:"<<f1->GetMaximumX()<<"\n";
  cout<<"Kwantyl dolny\t\t: "<<hist_value(num_bins,0.25,h1,x_min,x_max)<<"\n";
  cout<<"Mediana\t\t\t: "<<hist_value(num_bins,0.50,h1,x_min,x_max)<<"\n";
  cout<<"Kwantyl gorny\t\t: "<<hist_value(num_bins,0.75,h1,x_min,x_max)<<"\n";
  cout<<"Wartosc oczekiwana\t : "<<f1->Mean(x_min, x_max)<<"\n";
  cout<<"Wariancja\t\t : "<<f1->Variance(x_min, x_max)<<"\n";
  cout<<"Odchylenie standardowe\t : "<<sqrt(f1->Variance(x_min, x_max))<<"\n";
  
}


Double_t hist_value(Int_t num_bins, Double_t y, TH1D* h1,Double_t x_min, Double_t x_max){
  //This function returns bin for given value on hist
  int ii = 0;
  while((h1->GetBinContent(ii)<y) && (ii<num_bins)){
    ii++;
  }
  return Double_t(ii)*(x_max-x_min)/num_bins;
}