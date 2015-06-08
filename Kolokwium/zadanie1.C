#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TFrame.h>
#include <TMath.h>

void zadanie1() {
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();
   c1->Divide(2,2);
  
   double d=0;
   
   c1->cd(1);
   TF2* funkcja = new TF2("funkcja","[0]*TMath::Cos(0.5*x-0.5)*TMath::Sin(y)",0,TMath::Pi(),0,TMath::Pi());
   funkcja->SetParameter(0,1); 
   d=funkcja->Integral(0,TMath::Pi(),0,TMath::Pi());
   funkcja->SetParameter(0,1/d); // 1)  
   funkcja->GetXaxis()->SetTitle("X");
   funkcja->GetYaxis()->SetTitle("Y");
   funkcja->SetTitle("f(x,y)");
   funkcja->Draw("surf"); // 2)
   
 
   c1->cd(2);
   TH2D* h2 = new TH2D("h2","histogram",100,0,TMath::Pi(),100,0,TMath::Pi());
   TH2D* h2Dist=new TH2D("h3","histogram2",100,0,TMath::Pi(),100,0,TMath::Pi());
   h2->FillRandom("funkcja",1e6);
   h2->Scale(1/h2->Integral());
   for(int x=1;x<100;x++)
   {
     for(int y=1;y<100;y++)
     {
       double Integ=h2->Integral(1,x,1,y);
       h2Dist->SetBinContent(x,y,Integ);
     }
   }
   h2Dist->GetXaxis()->SetTitle("X");
   h2Dist->GetYaxis()->SetTitle("Y");
   h2Dist->SetTitle("Funkcja dystrybuanty F(x,y)");
   h2Dist->Draw("surf");
   
   c1->cd(3);
   TH1D* hProjX= h2->ProjectionX();
   hProjX->GetXaxis()->SetTitle("X");
   hProjX->GetYaxis()->SetTitle("Y");
   hProjX->SetTitle("Gestosc brzegowa g(x)");
   hProjX->Draw();
   
   c1->cd(4);
   TH1D* hProjY= h2->ProjectionY();
   hProjY->GetXaxis()->SetTitle("X");
   hProjY->GetYaxis()->SetTitle("Y");
   hProjY->SetTitle("Gestosc brzegowa h(y)");
   hProjY->Draw();
   
    5 DO DOKOnCZENIA
   Double_t a=funkcja->Mean(0,TMath::Pi());
   cout<<"Wartosc srednia: "<<a<<endl;
   
   Double_t b=hProjX->GetMean();
   cout<<"Wartosc srednia: "<<b<<endl;
  
   Double_t c = funkcja->Variance2X(0,TMath::Pi(),0,TMath::Pi(),0.000001);
   cout<<"Wariancja: "<<sqrt(c)<<endl;
   
   Double_t d = funkcja->Variance2Y(0,TMath::Pi(),0,TMath::Pi(),0.000001);
   cout<<"Wariancja: "<<sqrt(d)<<endl;
   
   Double_t e = funkcja->Covariance2XY(0,TMath::Pi(),0,TMath::Pi(),0.000001);
   cout<<"Kowariancja: "<<sqrt(e)<<endl;
   
   
}
