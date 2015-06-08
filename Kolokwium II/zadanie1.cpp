#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <TMath.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TH1.h>
#include <TF1.h>

using namespace std;


int zadanie1()
{
   TCanvas *c1 = new TCanvas("c1","Zadanie 1 Kolos",200,10,700,500);
   c1->Divide(2,0);
   c1->SetGrid();
   c1->cd(1);
   TF1 *poisson1 = new TF1("poisson1","[0]*TMath::Poisson(x,[1])",0,10);
   poisson1->SetParameter(0,1);
   poisson1->SetParameter(1,0.1);
   poisson1->SetLineColor(kBlack);
   TF1 *poisson2 = new TF1("poisson2","[0]*TMath::Poisson(x,[1])",0,10);
   poisson2->SetParameter(0,1);
   poisson2->SetParameter(1,0.5);
   poisson2->SetLineColor(kBlue);
   TF1 *poisson3 = new TF1("poisson3","[0]*TMath::Poisson(x,[1])",0,10);
   poisson3->SetParameter(0,1);
   poisson3->SetParameter(1,1);
   poisson3->SetLineColor(kYellow);
   TF1 *poisson4 = new TF1("poisson4","[0]*TMath::Poisson(x,[1])",0,10);
   poisson4->SetParameter(0,1);
   poisson4->SetParameter(1,2);
   poisson4->SetLineColor(kGreen);
   TF1 *poisson5 = new TF1("poisson5","[0]*TMath::Poisson(x,[1])",0,10);
   poisson5->SetParameter(0,1);
   poisson5->SetParameter(1,3);
   poisson5->SetLineColor(kRed);
   
   poisson1->Draw();
   poisson2->Draw("Same");
   poisson3->Draw("Same");
   poisson4->Draw("Same");
   poisson5->Draw("Same");
   
   
   
   c1->cd(2);
 
  TH1D* hist1 = new TH1D("hist","Histogram",100,0,10);
   for(int i=0;i<1000000;i++)
   {
     
     double g=poisson1->GetRandom(0,10)+poisson2->GetRandom(0,10)+poisson3->GetRandom(0,10)+poisson4->GetRandom(0,10)+poisson5->GetRandom(0,10);
     hist->Fill(g);
   }
  
   
     Double_t b=hist->GetMean();
   cout<<"Wartosc srednia: "<<b<<endl;
  
   Double_t c = hist->GetRMS();
   cout<<"Odchylenie standardowe: "<<c<<endl;
 
   hist->Draw();
  
  return 0;
  
}