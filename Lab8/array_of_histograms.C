#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <TMath.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TH1.h>


using namespace std;


int array_of_histograms()
{
  double ilosc_binow=1000;
  double chi;
  double l=0.5;
  
  const Int_t max_ndf = 20;
  Int_t ndf = max_ndf;
  
  TCanvas *c1 = new TCanvas("c1","Program 9",200,10,700,500);
  c1->Divide(2,0);
  c1->SetGrid();
  
  
  c1->cd(1);
  
  TH1D* histogramy[max_ndf];
  
  
  for (int ii = 1; ii <= max_ndf; ii++){
    TString hist = new TString::TString("hist");
    hist.Append(TString::Itoa(ii,10));
    histogramy[ii-1] = new TH1D(hist,"Histogram",ilosc_binow,0,20);
    cout<<hist<<endl;
  }
  
  while(ndf>0){
    
    for(int i=1;i<=1000;i++)
    {
	
	chi=(double)i*20/1000;
	histogramy[ndf-1]->SetBinContent(i,( (1/(TMath::Gamma(l)*TMath::Power(2,0.5*ndf))))*TMath::Power(chi,0.5*ndf-1)*TMath::Exp(-0.5*chi) );
	cout<< hist->GetBinContent(i) << endl;
	
    }
    ndf--;
    cout<<"wypelniono histogramy"<<endl;
  }

  histogramy[0]->Draw();
  histogramy[0]->GetXaxis()->SetTitle("chi2");
  histogramy[0]->GetYaxis()->SetTitle("gest. prawdopodobienstwa");
  
  for (int ii = 1; ii < max_ndf; ii++)
    histogramy[ii]->Draw("Same");
  
  c1->cd(2);
  TH1D** dystrybuanty = new TH1D("hist","Histogram",ilosc_binow,0,20)[max_ndf];
  
  for(int x=1;x<=1000;x++)
  {
      double Integ=hist->Integral(0,x);
      hDist->SetBinContent(x,Integ);
    
  }
  for(int x=1;x<=1000;x++)
  {
      double Integ=hist->Integral(0,x);
      hDist->SetBinContent(x,Integ);
       double Integ=hist1->Integral(0,x);
      hDist1->SetBinContent(x,Integ);
       double Integ=hist2->Integral(0,x);
      hDist2->SetBinContent(x,Integ);
       double Integ=hist3->Integral(0,x);
      hDist3->SetBinContent(x,Integ);
       double Integ=hist4->Integral(0,x);
      hDist4->SetBinContent(x,Integ);
       double Integ=hist5->Integral(0,x);
      hDist5->SetBinContent(x,Integ);
       double Integ=hist6->Integral(0,x);
      hDist6->SetBinContent(x,Integ);
       double Integ=hist7->Integral(0,x);
      hDist7->SetBinContent(x,Integ);
       double Integ=hist8->Integral(0,x);
      hDist8->SetBinContent(x,Integ);
       double Integ=hist9->Integral(0,x);
      hDist9->SetBinContent(x,Integ);
      
    
  }
  

 
  
	 
  
  hDist->Draw();
  hDist1->Draw("Same");
  hDist2->Draw("Same");
  hDist3->Draw("Same");
  hDist4->Draw("Same");
  hDist5->Draw("Same");
  hDist6->Draw("Same");
  hDist7->Draw("Same");
  hDist8->Draw("Same");
  hDist9->Draw("Same");
  
  return 0;
  
}