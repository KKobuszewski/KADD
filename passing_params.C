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

int passing_params(Double_t iloscKul,Double_t iloscPoz, Double_t prob)
{
  TCanvas *c1 = new TCanvas("c1","Program 8",200,10,700,500);
  c1->SetGrid();
//   Double_t iloscKul=0.;
//   Double_t iloscPoz=0.;
//   Double_t prob=2.;
//   cout<<"Podaj ilosc kul"<<endl;
//   cin>>iloscKul;
//   cout<<"Podaj ilosc poziomow"<<endl;
//   cin>>iloscPoz;
//   while ((prob >= 1.) || (prob <= 0.)){
//     cout<<"Podaj ilosc prawdopodobienstwo ruchu w prawo"<<endl;
//     cin>>prob;
//   }
  
  TH1D* hist = new TH1D("hist","Histogram",(iloscPoz),-iloscPoz,iloscPoz);
  TRandom3 *generator= new TRandom3();
  for(int j=0;j<iloscKul;j++)
    
  {Double_t zmienna=0;
    for(int i=0;i<iloscPoz;i++)
  {	
      Double_t x=generator->Uniform(0,1);
    //  cout<<x<<endl;
      if(x<=prob)
      {
	zmienna++;
      }
      else
	zmienna--;
     
  }
   hist->Fill(zmienna);
  }
 
  hist->Draw();
  
 
      
 
  return 0;
  
}