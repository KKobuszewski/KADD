#include <stdio.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>

using namespace std;
  
int zadanie2()
{
 

   TCanvas *c1 = new TCanvas("c1","Zadanie 2 Kolos",200,10,700,500);
   c1->SetGrid();
   double tabx[]={-1.5,-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5};
   double taby[]={54.,164.,164.,69.,22.,14.,8.,0.1,3.,2.};
   double tabuy[]={7.3,12.8,12.8,8.3,4.7,3.7,2.8,0.01,1.7,1.4};
   TGraphErrors* grErr = new TGraphErrors(10,tabx,taby,0,tabuy);
	grErr->SetTitle("Dane");
	grErr->SetLineColor(kBlack);
	grErr->SetMarkerColor(kBlack);
	grErr->SetMarkerSize(2);
	grErr->Draw("ap");
	
	
	TF1 *funkcja1 = new TF1("funckja01","gaus",-2,8);
	funkcja1->SetParameter(0,1);
	funkcja1->SetParameter(1,1); 
	funkcja1->SetParameter(2,1);
	
	TF1 *funkcja2 = new TF1("funckja02","[0]*TMath::Student(x,[1])",-2,8);
	funkcja1->SetParameter(0,1);
	funkcja2->SetParameter(1,1); 
	TFitResultPtr fitRes=grErr->Fit(funkcja1,"S");
	
	TFitResultPtr fitRes2=grErr->Fit(funkcja2,"S+");
	cout<<"--------------------------"<<endl<<"Gaus"<<endl;
	cout<<"Chi-kwadrat:"<<fitRes->Chi2()<<endl;
	cout<<"Liczba stopni swobody "<<funkcja1->GetNDF()<<endl; 
	cout<<"--------------------------"<<endl<<"Student"<<endl;
	cout<<"Chi-kwadrat:"<<fitRes2->Chi2()<<endl;
	cout<<"Liczba stopni swobody "<<funkcja2->GetNDF()<<endl; 
	
	
	
  return 0;
  
}






