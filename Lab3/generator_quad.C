#include <stdio.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>
#include <math.h>


using namespace std;

static unsigned long long x1 = 1;
static unsigned long long x2 = 0xffffffa;

unsigned long long random1_uint64(){
    /*
     * This random number generator should
     */
    // http://en.wikipedia.org/wiki/Linear_congruential_generator
    //MMIX
    unsigned long long a = 6364136223846793005;
    unsigned long long c = 1442695040888963407;
    unsigned long long m = pow(2,64);
    x1 = (a*x2 + c)%m;
    //printf("%lu\n", x1);
    return x1;  /*64-bit result */
}

unsigned long long random2_uint64(){
    /*
     * This random number generator should
     */
    // http://en.wikipedia.org/wiki/Linear_congruential_generator
    //Newlib
    unsigned long long a = 6364136223846793005;
    unsigned long long c = 1;
    unsigned long long m = pow(2,64);
    x2 = (a*x1 + c)%m;
    //printf("%lu\n", x2);
    return x2;  /* 32-bit result */
}

/* generates a random number on [0,1) as a double */
double random_res53(){
    unsigned long a=random1_uint64()>>5, b=random2_uint64()>>6;
    return(a*67108864.+b)*(1./9007199254740992.); 
}


int generator_quad()
{
   Int_t m=1,n=1000000;
    
      
   Double_t* random_numbers = new Double_t[n+1];
   //Int_t random_numbers[n+1];
   int ii = 0;
   
   //printf("\n%d\n",random_numbers[0]);
   do {
     
     //printf("%d\n",random_numbers[ii]);
     random_numbers[ii] = random_res53();
     printf("%d\n",random_numbers[ii]);
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
   //distrib->GetYaxis()->SetRangeUser(0.0,0.002);
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