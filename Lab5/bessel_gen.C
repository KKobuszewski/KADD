#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <TMath>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>

using namespace std;

int bessel_gen()
{
  TCanvas *c1 = new TCanvas("c1","Program 6",200,10,700,500);
  c1->SetGrid();
  Double_t a=5;
  Double_t x,y,u;
  Int_t N = 100000; // ilosc losowan
  
  // Szukany rozklad prawdopodobienstwa  
  TF1 *bessel = new TF1("bessel","[0]*TMath::BesselI0(x)",0,a);
  bessel->SetParameter(0,1);
  Double_t g=bessel->Integral(0,a);
  cout<<"g: "<<g<<endl;
  bessel->SetParameter(0,1./g);
  bessel->Draw();
  bessel->SetTitle("Gestosc prawdopodobienstwa");
  bessel->GetXaxis()->SetTitle("x");
  bessel->GetYaxis()->SetTitle("y(x)");
  bessel->SetLineColor(kGreen);
  
  
  Double_t ymax=TMath::BesselI0(a)/g;
  Double_t ymin=TMath::BesselI0(0)/g;
  Double_t alpha = (ymax-ymin)/(a-0.);
  Double_t beta = ymin;
  
  // Funckja pomocnicza
  TF1 *prosta = new TF1("prosta","[0]*x+[1]",0,a);
  prosta->SetParameter(0,alpha);
  prosta->SetParameter(1,beta);
  prosta->Draw("same");
  
  cout<<"f(0): "<<ymin<<"\nf(a): "<<ymax<<endl;
  
  
  TH1D* hist = new TH1D("hist","Histogram",100,0,a);
  TRandom3 *generator= new TRandom3();
  for(int ii=0;ii<N;ii++)
  {
    x=generator->Uniform(0,a);
    //cout<<"x "<<x<<endl;
    y=generator->Uniform(0,ymax);
    //cout<<"y "<<y<<endl;
    
    if(y<(TMath::BesselI0(x)/g))
    {
      hist->Fill(x);
    }
  }
  hist->Scale(1/hist->Integral("width"));
  hist->Draw("same");
  TH1D* hist2 = new TH1D("hist2","Histogram2",100,0,a);
    
  for(int ii=0;ii<N;ii++)
  {
    x=generator->Uniform(0,0.5*alpha*a*a+beta*a);
    y=(sqrt(beta*beta+2*alpha*x)-beta)/alpha;
    u=generator->Uniform(0,1);
    
    if(u<(TMath::BesselI0(y)/(alpha*y+beta)))
    {
      hist2->Fill(y);
    }
  }
  hist2->SetLineColor(kRed);
  hist2->Scale(1/hist2->Integral(1,N,"width"));
  hist2->Draw("same");
  
  TLegend *leg = new TLegend(0.2,0.7,0.4,0.80);
      leg->SetFillStyle(0);
      leg->SetTextSize(0.04);
      leg->AddEntry(bessel,"Bessel","l");
      leg->AddEntry(prosta,"prosta","l");
      leg->AddEntry(hist,"Histogram","l");
      leg->AddEntry(hist2,"Histogram2","l");
      leg->Draw("same");
      
 
  return 0;
  
}