#include <TMath.h>
#include <TH1D.h>
#include <TF1.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <iostream>


void Lab9_1(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  //c1->Divide(3,1);
  
  
  const Int_t n = 40;
  
  
  
  Double_t k[] = {22.,  23.,  24.,  25.,  26.,  27.,  28.,  29.,  30.,  31.,  32.,
		  33.,  34.,  35.,  36.,  37.,  38.,  39.,  40.,  41.,  42.,  43.,
		  44.,  45.,  46.,  47.,  48.,  49.,  50.,  51.,  52.,  53.,  54.,
		  55.,  56.,  57.,  58.,  59.,  60.,  61.};
  Double_t nk[] = {1.,    4.,    6.,    8.,    8.,   18.,   23.,   25.,   22.,
		  54.,   69.,   77.,   99.,   94.,   89.,  110.,  105.,  125.,
		  110.,   81.,   72.,   71.,   58.,   46.,   29.,   28.,   18.,
		  18.,    9.,   11.,    4.,    3.,    2.,    0.,    0.,    0.,
		  2.,    0.,    0.,    1.};
  Double_t unk[n];
  Double_t xmin = k[0];
  Double_t xmax = k[n-1];
  
  TH1D* histogram = new TH1D("Poisson","dane doswiadczalne",n,xmin,xmax);
  
  Double_t num_data = 0;
  for (int ii=0; ii< n; ii++) {
    num_data += nk[ii];
    unk[ii] = TMath::Sqrt(nk[ii])/1500;
    histogram->SetBinContent(ii,nk[ii]);
    //gauss->SetBinContent(ii,nk[ii]/1500.);
    //nk[ii] /= 1500;
  }
  cout<<endl<<"ilosc pomiarow: "<<num_data<<endl;
  
  Double_t mean_data = 0;
  for (int ii = 0; ii < n; ii++) {
    mean_data += k[ii]*nk[ii];
  }
  mean_data /= num_data;
  cout<<"estymator wartosci oczekiwanej: "<<mean_data<<endl<<endl;
   
  
  histogram->Sumw2();
  histogram->Scale(1./num_data);
  histogram->Draw();
  histogram->GetXaxis()->SetTitle("k (liczba zliczen w pomiarze)");
  histogram->GetYaxis()->SetTitle("P(k)");
  
  // DOPASOWANIE POISSON
  TF1* fit_func = new TF1("fit","TMath::Power([0],x)*TMath::Exp(-[0])/TMath::Gamma(x+1)",xmin,xmin);
  fit_func->SetParameter(0,mean_data);
  
  histogram->Fit(fit_func);
  fit_func->SetTitle("dopasowanie Poisson");
  
  cout<<"POISSON"<<endl;
  
  Double_t chi_pearson = 0;
  for (int ii=0; ii< n; ii++) {
    chi_pearson += (nk[ii] - num_data*fit_func->Eval(k[ii]))*(nk[ii] - num_data*fit_func->Eval(k[ii]))/(num_data*fit_func->Eval(k[ii]));
    
  }
  
  cout<<"lambda "<<fit_func->GetParameter(0)<<endl;
  cout<<"NDF: "<<n-2<<endl;
  cout<<"Chi2: "<<chi_pearson<<endl;
  cout<<"Chi2(99%): "<<TMath::ChisquareQuantile(0.99,n-2)<<endl;
  
  if (chi_pearson < TMath::ChisquareQuantile(0.99,n-2)) {
    cout<<"NIE MA POWODOW DO ODRZUCENIA HIPOTEZY"<<endl;
  }
  
  
  // DOPASOWANIE GAUSS
  histogram->Fit("gaus","+");
  //TF1* gauss = new TF1("gauss","TMath::Gauss(x,37.76599,5.29973)");
  TF1* gauss;
  gauss = histogram->GetFunction("gaus");
  gauss->SetLineColor(kGreen);
  
  
  
  
  cout<<endl<<"GAUSS"<<endl;
  
  
  for (int ii=0; ii< n; ii++) {
    chi_pearson += (nk[ii] - num_data*gauss->Eval(k[ii]))*(nk[ii] - num_data*gauss->Eval(k[ii]))/(num_data*gauss->Eval(k[ii]));
    
  }
  
  cout<<"mean "<<gauss->GetParameter(1)<<endl;
  cout<<"NDF: "<<gauss->GetNDF()<<endl;
  cout<<"Chi2: "<<chi_pearson<<endl;
  cout<<"Chi2(99%): "<<TMath::ChisquareQuantile(0.99,n-2)<<endl;
  
  if (chi_pearson < TMath::ChisquareQuantile(0.99,n-2)) {
    cout<<"NIE MA POWODOW DO ODRZUCENIA HIPOTEZY"<<endl;
  }
  
  TLegend *leg3 = new TLegend(0.8,0.9,0.5,0.7);
  leg3->AddEntry(histogram,"Pomiary","l");
  leg3->AddEntry(fit_func,"dopasowanie Poisson","l");
  leg3->AddEntry(gauss,"dopasowanie Gauss","l");
  leg3->Draw("same");
  
  
  
  
  
  //cout<<"Chi2 gauss: "<<f1->GetChisquare()<<" ndf: "<<f1->GetNDF()<<endl;
  
}