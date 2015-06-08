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

int zadanie3()
{
  const double E = 2.71828182845904523536;

  TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
  c1->SetGrid();
  
  double x,y,zmienna=0,zmienna2=0,d=0,u=0,d1;
  TF1 *funkcja = new TF1("funkcja1","0.5*TMath::Cos(TMath::Pi()*x)/(TMath::Pi()*x+1)+0.5",0,2);
  TF1 *funkcja1 = new TF1("funckja2","TMath::Exp(-x/[0])",0,2);
  funkcja1->SetParameter(0,4); 
  
  TH2D* hist = new TH2D("hist","Histogram",100,0,2,100,0,1);
  TH2D* hist2 = new TH2D("hist2","Histogram",100,0,2,100,0,1);
  TRandom3 *generator= new TRandom3();
  for(int ii=0;ii<1000000 ;ii++)
  {
    x=generator->Uniform(-4,-4/sqrt(E));
    y=-4*log(-x/4);

    u=generator->Uniform(0,1);
    if(u<((0.5*TMath::Cos(TMath::Pi()*y)/(TMath::Pi()*y+1)+0.5)/(TMath::Exp(-y/4))))
    {
      hist->Fill(y,u*(TMath::Exp(-y/4)));
      zmienna++;
    }
    else
    { hist2->Fill(y,u*(TMath::Exp(-y/4)));
   zmienna2++;
    }
      
  }
  hist2->SetMarkerColor(kBlue);
  d1=((zmienna)/(zmienna2+zmienna))*funkcja1->Integral(0,2);
  
  
  d=funkcja->Integral(0,2);
  cout<<d<<endl<<d1;
  
  hist->Draw();
 hist2->Draw("Same");
 
 
 
 
 
  return 0;
  
}