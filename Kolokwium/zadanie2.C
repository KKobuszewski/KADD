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

int zadanie2()
{
  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
  c1->SetGrid();
  double x,y;

  
  TH1D* hist = new TH1D("hist","Histogram",100,0,2);
  TH1D* hist2 = new TH1D("hist2","Histogram",100,0,2);
  TRandom3 *generator= new TRandom3();
  for(int ii=0;ii<1000000;ii++)
  {
    x=generator->Uniform(0,2);
    
    if((TMath::Exp(-x/4))<1)
    {
      hist->Fill(x);
    }
    else
    { hist2->Fill(x);
    }
      
  }
  hist2->SetMarkerColor(kYellow);

  
  
  hist->Draw();
  hist2->Draw("Same");
 
 
 
 
 
  return 0;
  
}