#include <cstdlib>
#include <stdio.h>

void lab9_2(){
  
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(2,1);
  
  Double_t xmin = 0.;
  Double_t xmax = 40.;
  const int n = 10;
  
  // RYSOWANIE ROZKLADU GESTOSCI PRAWDOPODOBIENSTWA
  c1->cd(1);
  
  TF1* array_func[n];
  
  for (int ii = 0; ii < n; ii++){
    
    char buf[8];
    snprintf(buf, sizeof(buf), "%s%i", "chi2_",ii);
    cout<<buf<<endl;
    
    array_func[ii] = new TF1(buf,"TMath::Power(0.5,0.5*[0])*TMath::Power(x,0.5*[0]-1)*TMath::Exp(-0.5*x)/TMath::Gamma(0.5*[0])",xmin,xmax);
    array_func[ii]->SetParameter(0,ii+1);
    array_func[ii]->SetLineColor(ii+1);
    
    if (ii == 0)
      array_func[ii]->Draw();
    else
      array_func[ii]->Draw("same");
    
  }
  
  // RYSOWANIE DYSTRYBUANTY
  c1->cd(2);
  
  const int num_bins = 1000;
  const Double_t dx = (xmin-xmax)/((Double_t) num_bins);
  
  TF1* array_hist[n];
  TH1D* array_hist2[n];
  
  TH1D* rozklad = new TH1D("rozklad","Rozklad", num_bins, xmin, xmax);
  
  for (int ii = 0; ii < n; ii++){
    char buf[20];
    char name_chi[8];
    snprintf(buf, sizeof(buf), "%s%i", "dist_chi2_",ii);
    snprintf(name_chi, sizeof(name_chi), "%s%i", "chi2_",ii);
    cout<<ii<<". "<<buf<<endl;
    
    array_hist[ii] = new TF1(buf,"TMath::Gamma(0.5*[0],0.5*x)",xmin,xmax);
    array_hist[ii]->SetParameter(0,ii+1);
    array_hist[ii]->SetLineColor(ii);
    
    rozklad->FillRandom(name_chi,1e7);
    rozklad->Scale(1./rozklad->Integral());
    
    array_hist2[ii] = new TH1D(buf,buf, num_bins, xmin, xmax);
    for (int jj = 0; jj < num_bins; jj++) {
      array_hist2[ii]->SetBinContent( jj,rozklad->Integral(0,jj) );
    }
    array_hist2[ii]->SetLineColor(ii+1);
    
    if (ii == 0) {
      array_hist2[ii]->Draw();
      array_hist2[ii]->GetYaxis()->SetRangeUser(0.,1.);
    }
    else
      array_hist2[ii]->Draw("same");
    
    rozklad->Reset();
  }
}