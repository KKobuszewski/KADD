#include <stdio.h>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>
#include <TGraph.h>

static unsigned long x1 = 1;
static unsigned long x2 = 0xffffffa;

unsigned long random1_uint32(){
    /*
     * This random number generator should
     */
    // http://en.wikipedia.org/wiki/Linear_congruential_generator
    //MMIX
    unsigned long a = 1103515245;
    unsigned long c = 12345;
    unsigned long m = pow(2,32);
    x1 = (a*x1 + c)%m;
    //printf("%lu\n", x1);
    return x1;  /*64-bit result */
}

unsigned long random2_uint32(){
    /*
     * This random number generator should
     */
    // http://en.wikipedia.org/wiki/Linear_congruential_generator
    //Newlib
    unsigned long a = 1664525;
    unsigned long c = 1013904223;
    unsigned long m = pow(2,32);
    x2 = (a*x2 + c)%m;
    //printf("%lu\n", x2);
    return x2;  /* 32-bit result */
}

/* generates a random number on [0,1) as a double */
double random_res53(){
    unsigned long a=random1_uint32()>>5, b=random2_uint32()>>6;
    return(a*67108864.+b)*(1./9007199254740992.); 
}

unsigned long binomial(const unsigned long N,const double p){
   /*
     * PARAMS
     * unsigned long N   - number of evaluations (max possible value)
     * __float128 p - quad precision probability of succes
     * RETURN
     * unsigned long k   - number from binomial distribution
     */
   unsigned long k = 0;
   for (unsigned long ii=0; ii < N; ii++){
     if (p > random_res53())
       k++;
   }
   return k;
}

int binomial_double()
{
   Int_t m=100,n=10000;
   Double_t p = 0.5;
      
   Double_t* random_numbers = new Double_t[n+1];
   //Int_t random_numbers[n+1];
   int ii = 0;
   
   //printf("\n%d\n",random_numbers[0]);
   do {
     
     //printf("%d\n",random_numbers[ii]);
     random_numbers[ii] = (Double_t) binomial((unsigned long) m, p);
     //printf("%d\n",random_numbers[ii]);
     ii++;
   } while(ii<=n);
   
   //Creating canvas
   TCanvas *c1 = new TCanvas("c1","Program 4",200,10,700,500);
   c1->Divide(1,2);
   
   //Declaring functions
   TH2F* sepctral_distrib = new TH2F("sepctral_distrib","Rozklad widmowy generowanych liczb losowych",1000,0,m,1000,0,m);
   TH1F* distrib = new TH1F("distrib","Rozklad prawdopobienstwa generowanych liczb losowych",1000,0,m);
   
   Double_t *x = new Double_t[m];
   Double_t *y = new Double_t[m];
   for (int ll=0; ll<m; ll++){
      x[ll] = (Double_t) ll;
      y[ll] = TMath::Binomial(m, ll)*TMath::Power(p,ll)*TMath::Power(1-p,m-ll-1);
   }
   TGraph *binomial = new TGraph(m,x,y);
   
      
   //Wypelanianie histogramów
   for(int jj=0;jj<n;jj++)  {  
	//printf(random_numbers[jj]);
	distrib->Fill(random_numbers[jj]);
	sepctral_distrib->Fill(random_numbers[jj],random_numbers[jj+1]);
	//random_numbers[ii] to Xn, random_numbers[ii+1] to Xn+1
   }
   distrib->Scale(1./distrib->Integral());
   
   //Drawing distibution
   c1->cd(1);
   c1_1->SetGrid();
   binomial->GetXaxis()->SetTitle("X_n");
   binomial->GetYaxis()->SetTitle("Ilosc zliczen");
   binomial->Draw();
   distrib->Draw("same");
   
   //Drawing spectrum
   c1->cd(2);
   c1_2->SetGrid();
   sepctral_distrib->GetXaxis()->SetTitle("X_n");
   sepctral_distrib->GetYaxis()->SetTitle("X_{n+1}");
   sepctral_distrib->Draw("colz");
   
   //fclose(wyjscie);
   return 0; 
}

# ifndef __CINT__
int main() {
  // compilation command: g++ -o binomial generator_binomial.C `root-config --cflags --glibs` -lquadmath -Wall
  generator_binomial();
  return 0;
}
# endif