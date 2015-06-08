#include <stdio.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>

using namespace std;
  
int zadanie3()
{
 

   TCanvas *c1 = new TCanvas("c1","Zadanie 3 Kolos",200,10,700,500);
   c1->SetGrid();
   double alpha;
   double tabx[]={-1.5,-0.5,0.5,1.5,2.5,3.5,4.5,5.5,6.5,7.5};
   double taby[]={54.,164.,164.,69.,22.,14.,8.,0.1,3.,2.};
   double tabuy[]={7.3,12.8,12.8,8.3,4.7,3.7,2.8,0.01,1.7,1.4};
   double wspolczynniki[10];
   double wspsigma[10];
   TGraphErrors* grErr = new TGraphErrors(10,tabx,taby,0,tabuy);
	grErr->SetTitle("Dane");
	grErr->SetLineColor(kBlack);
	grErr->SetMarkerColor(kBlack);
	grErr->SetMarkerSize(2);
	grErr->Draw("ap");
	
	dopasuj(7,10,tabx,taby,tabuy,wspolczynniki,wspsigma);
	TF1 *f3=new TF1("f","[0]+x*[1]+x^2*[2]+x^3*[3]+x^4*[4]+x^5*[5]+x^6*[6]+x^7*[7]",-2,8);
	f3->SetParameter(0,wspolczynniki[0]);
	f3->SetParameter(1,wspolczynniki[1]);
	f3->SetParameter(2,wspolczynniki[2]);
	f3->SetParameter(3,wspolczynniki[3]);
	f3->SetParameter(4,wspolczynniki[4]);
	f3->SetParameter(5,wspolczynniki[5]);
	f3->SetParameter(6,wspolczynniki[6]);
	f3->SetParameter(7,wspolczynniki[7]);
	f3->SetLineColor(kBlack);
	f3->Draw("Same");
	dopasuj(6,10,tabx,taby,tabuy,wspolczynniki,wspsigma);
	TF1 *f=new TF1("f","[0]+x*[1]+x^2*[2]+x^3*[3]+x^4*[4]+x^5*[5]+x^6*[6]",-2,8);
	f->SetParameter(0,wspolczynniki[0]);
	f->SetParameter(1,wspolczynniki[1]);
	f->SetParameter(2,wspolczynniki[2]);
	f->SetParameter(3,wspolczynniki[3]);
	f->SetParameter(4,wspolczynniki[4]);
	f->SetParameter(5,wspolczynniki[5]);
	f->SetParameter(6,wspolczynniki[6]);
	f->SetLineColor(kBlue);
	f->Draw("Same");
	dopasuj(5,10,tabx,taby,tabuy,wspolczynniki,wspsigma);
	TF1 *f2=new TF1("f","[0]+x*[1]+x^2*[2]+x^3*[3]+x^4*[4]+x^5*[5]",-2,8);
	f2->SetParameter(0,wspolczynniki[0]);
	f2->SetParameter(1,wspolczynniki[1]);
	f2->SetParameter(2,wspolczynniki[2]);
	f2->SetParameter(3,wspolczynniki[3]);
	f2->SetParameter(4,wspolczynniki[4]);
	f2->SetParameter(5,wspolczynniki[5]);
	f3->SetLineColor(kYellow);
	f2->Draw("Same");
	
	//zwraca mi NDF -1 
	
	
	TFitResultPtr fitRes=grErr->Fit(f3,"S");
	double ndf;
	ndf=f3->GetNDF();
	double chi2;
	chi2=fitRes->Chi2();
	alpha=0.1; //poziom istotnosci
	cout<<"Wielomian 7 stopnia!"<<endl;
	cout<<"chi2 = "<<chi2<<endl;
	cout<<"ndf = "<<ndf<<endl;
	double test,teo;
	test=chi2;
	teo=TMath::ChisquareQuantile(alpha,ndf);
	if (test<teo) 	{cout<<"brak podstaw do odrzucenia hipotezy"<<test<<"<"<<teo<<endl;}
	else {cout<<"sa podstawy do odrzucenia hipotezy"<<test<<">"<<teo<<endl;}
	
	TFitResultPtr fitRes2=grErr->Fit(f,"S");
	double ndf;
	ndf=f->GetNDF();
	double chi2;
	chi2=fitRes2->Chi2();
	alpha=0.1; //poziom istotnosci
	cout<<"Wielomian 6 stopnia!"<<endl;
	cout<<"chi2 = "<<chi2<<endl;
	cout<<"ndf = "<<ndf<<endl;
	double test,teo;
	test=chi2;
	teo=TMath::ChisquareQuantile(alpha,ndf);
	if (test<teo) 	{cout<<"brak podstaw do odrzucenia hipotezy"<<test<<"<"<<teo<<endl;}
	else {cout<<"sa podstawy do odrzucenia hipotezy"<<test<<">"<<teo<<endl;}
	
	TFitResultPtr fitRes3=grErr->Fit(f2,"S");
	double ndf;
	ndf=f2->GetNDF();
	double chi2;
	chi2=fitRes3->Chi2();
	alpha=0.1; //poziom istotnosci
	cout<<"Wielomian 5 stopnia!"<<endl;
	cout<<"chi2 = "<<chi2<<endl;
	cout<<"ndf = "<<ndf<<endl;
	double test,teo;
	test=chi2;
	teo=TMath::ChisquareQuantile(alpha,ndf);
	if (test<teo) 	{cout<<"brak podstaw do odrzucenia hipotezy"<<test<<"<"<<teo<<endl;}
	else {cout<<"sa podstawy do odrzucenia hipotezy"<<test<<">"<<teo<<endl;}
	
	

	
	
	
	
	
	
  return 0;
  
}

double dopasuj(int stopien,int ilosc_pomiarow,double *tj,double *yj,double *sigmaj,double *wspolczynniki, double *wspsigma)
{
  TMatrixD A(ilosc_pomiarow,stopien+1);
  int potega=1;
  for(int i=0;i<ilosc_pomiarow;i++)
    A(i,0)=1;
  for(int j=1;j<stopien+1;j++)
  {	
    for(int i=0;i<ilosc_pomiarow;i++)
    {
     A(i,j)=TMath::Power(tj[i],potega);
     
    }
    potega++;
  }


    
   
   
  TMatrixD c(ilosc_pomiarow,1);
  for(int i=0;i<ilosc_pomiarow;i++)
  {
    c(i,0)=yj[i];
    
  }
   
  
   TMatrixD G_y(ilosc_pomiarow,ilosc_pomiarow);
  
   for(int i=0;i<ilosc_pomiarow;i++)
   {
     G_y(i,i)=(1/TMath::Power(sigmaj[i],2));
   }
  .. G_y.Print();
   
   TMatrixD H(ilosc_pomiarow,ilosc_pomiarow);
  
   for(int i=0;i<ilosc_pomiarow;i++)
   {
     H(i,i)=(1/sigmaj[i]);
   }
   
  TMatrixD pom_A(H,TMatrix::kMult,A);
   TMatrixD pom_c(H,TMatrix::kMult,c);
   
   TMatrixD pom_A_T(TMatrix::kTransposed,pom_A);
   TMatrixD A_T_A(pom_A_T,TMatrix::kMult,pom_A);
   TMatrixD odwrocona = A_T_A.Invert();
   TMatrixD A_T_c(pom_A_T,TMatrix::kMult,pom_c);
   TMatrixD wynik(odwrocona,TMatrix::kMult,A_T_c); 
    
   
   
   
   for(int i=0;i<stopien+1;i++)
   {
     
	wspolczynniki[i]=wynik(i,0);
   }
  
   wynik.Print();

  
  
  
  return 5;
}




