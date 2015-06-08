#include <stdio.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>


using namespace std;


int generator()
{
   long long x=2,m=pow(2,32),a=1664525,c=1013904223,n=100000;
   cout<<m<<endl; 
   /*cout<<"Podaj N"<<endl;
   cin>>n;
   cout<<"Podaj a"<<endl;
   cin>>a;
   cout<<"Podaj m"<<endl;
   cin>>m;*/
   
   /*FILE *wejscie;
   wejscie = fopen ("myfile.txt","w+");
   if (wejscie!=NULL)
   {
      for(int i=0;i<n;i++)  
      {  
	
	fprintf(wejscie,"%d\n",(a*x+c)%m);
	x=(a*x+c)%m;
	
      }
      fclose (wejscie);
   }
   
   FILE *wyjscie;
   wyjscie = fopen ("myfile.txt","r");
   Int_t g=0;
   fscanf(wyjscie,"%d",&g);*/
   
   long* random_numbers = new long[n+1];
   //Int_t random_numbers[n+1];
   int ii = 0;
   random_numbers[0] = x;
   //printf("\n%d\n",random_numbers[0]);
   do {
     ii++;
     //printf("%d\n",random_numbers[ii]);
     random_numbers[ii] = (a*random_numbers[ii-1] + c)%m);
     //printf("%d\n",random_numbers[ii]);
   } while(ii<n);
   
   //Creating canvas
   TCanvas *c1 = new TCanvas("c1","Program 4",200,10,700,500);
   c1->Divide(1,2);
   
   //Declaring functions
   TH2F* sepctral_distrib = new TH2F("sepctral_distrib","Rozklad widmowy generowanych liczb losowych",100,0,m,100,0,m);
   TH1F* distrib = new TH1F("distrib","Rozklad prawdopobienstwa generowanych liczb losowych",100,0,m);
   
   //Wypelanianie histogramów
   for(int jj=0;jj<n;jj++)  {  
	//printf(random_numbers[jj]);
	distrib->Fill(((Double_t)random_numbers[jj])/m);
	sepctral_distrib->Fill(((Double_t)random_numbers[jj])/m,((Double_t)random_numbers[jj+1])/m);
	//random_numbers[ii] to Xn, random_numbers[ii+1] to Xn+1
   }
   distrib->Scale(1./n);
   
   //Drawing distibution
   c1->cd(1);
   c1_1->SetGrid();
   distrib->GetXaxis()->SetTitle("X_n");
   distrib->GetYaxis()->SetTitle("Ilosc zliczen");
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