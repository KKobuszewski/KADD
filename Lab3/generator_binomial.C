#include <stdio.h>
//#include <random>
#include <TLine.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TF1.h>
#include <TGraph.h>

/* Period parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = 
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void) 
{ 
    unsigned long a=genrand_int32()>>5, b=genrand_int32()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 
/* These real versions are due to Isaku Wada, 2002/01/09 added */

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
     if (p > genrand_res53())
       k++;
   }
   return k;
}

int generator_binomial()
{
   Int_t m=100,n=10000;
   Double_t p = 0.5;
   
   Double_t* random_numbers = new Double_t[n+1];
   //Double_t* binomial_numbers = new Double_t[n+1];
   //Int_t random_numbers[n+1];
   int ii = 0;
   
   //std::default_random_engine generator;
   //std::binomial_distribution<int> distribution(m,0.5);
   
   //printf("\n%d\n",random_numbers[0]);
   do {
     
     //printf("%d\n",random_numbers[ii]);
     random_numbers[ii] = (Double_t) binomial((unsigned long) m, p);
     //binomial_numbers[ii] = distibution(generator);
     //printf("%d\n",random_numbers[ii]);
     ii++;
   } while(ii<=n);
   
   //Creating canvas
   TCanvas *c1 = new TCanvas("c1","Program 4",200,10,700,500);
   c1->Divide(1,2);
   
   //Declaring functions
   TH2F* sepctral_distrib = new TH2F("sepctral_distrib","Rozklad widmowy generowanych liczb losowych",1000,0,m,1000,0,m);
   //TH2F* sepctral_distrib2 = new TH2F("sepctral_distrib2","Rozklad widmowy generowanych liczb losowych",1000,0,m,1000,0,m);
   TH1F* distrib = new TH1F("distrib","Rozklad prawdopobienstwa generowanych liczb losowych",1000,0,m);
   //TH1F* distrib2 = new TH1F("distrib2","Rozklad prawdopobienstwa generowanych liczb losowych",1000,0,m);
   
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
	//distrib2->Fill(binomial_numbers[jj]);
	//sepctral_distrib2->Fill(binomial_numbers[jj],binomial_numbers[jj+1]);
	//random_numbers[ii] to Xn, random_numbers[ii+1] to Xn+1
   }
   distrib->Scale(1./distrib->Integral());
   
   //Drawing distibution
   c1->cd(1);
   c1_1->SetGrid();
   binomial->GetXaxis()->SetTitle("X_n");
   binomial->GetYaxis()->SetTitle("Ilosc zliczen");
   binomial->Draw();
   //distrib2->SetFillColor(kRed);
   //distrib2->Draw("same");
   distrib->Draw("same");
   
   //Drawing spectrum
   c1->cd(2);
   c1_2->SetGrid();
   //spectral_distrib2->Draw();
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