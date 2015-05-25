#include <stdio.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>

using namespace std;

int generator_logistic()
{
   Int_t m=1,n=100000;
   Double_t x = 0.33;
      
   Double_t* random_numbers = new Double_t[n+1];
   //Int_t random_numbers[n+1];
   int ii = 0;
   
   //printf("\n%d\n",random_numbers[0]);
   do {
     
     //printf("%d\n",random_numbers[ii]);
     x = 4*x*(1-x);
     random_numbers[ii] = x;
     //printf("%d\n",random_numbers[ii]);
     ii++;
   } while(ii<=n);
   
   //Creating canvas
   TCanvas *c1 = new TCanvas("c1","Program 4",200,10,700,500);
   c1->Divide(1,2);
   
   //Declaring functions
   TH2F* sepctral_distrib = new TH2F("sepctral_distrib","Rozklad widmowy generowanych liczb losowych",1000,0,m,1000,0,m);
   TH1F* distrib = new TH1F("distrib","Rozklad prawdopobienstwa generowanych liczb losowych",1000,0,m);
   
   //Wypelanianie histogramów
   for(int jj=0;jj<n;jj++)  {  
	//printf(random_numbers[jj]);
	distrib->Fill(random_numbers[jj]);
	sepctral_distrib->Fill(random_numbers[jj],random_numbers[jj+1]);
	//random_numbers[ii] to Xn, random_numbers[ii+1] to Xn+1
   }
   distrib->Scale(1./n);
   
   //Drawing distibution
   c1->cd(1);
   c1_1->SetGrid();
   distrib->GetXaxis()->SetTitle("X_n");
   distrib->GetYaxis()->SetTitle("Ilosc zliczen");
   printf("%d",distrib->GetBinContent(distrib->GetMaximumBin()));
   distrib->GetYaxis()->SetRangeUser(0.0,0.002);
   distrib->Draw();
   
   //Drawing spectrum
   c1->cd(2);
   c1_2->SetGrid();
   sepctral_distrib->GetXaxis()->SetTitle("X_n");
   sepctral_distrib->GetYaxis()->SetTitle("X_{n+1}");
   sepctral_distrib->Draw("colz");
   
   //fclose(wyjscie);
   return 0; 
}