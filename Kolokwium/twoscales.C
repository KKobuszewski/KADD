//example of macro illustrating how to superimpose two histograms
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"
   
void twoscales()
{
   //example of macro illustrating how to superimpose two histograms
   //with different scales in the "same" pad.
   // To see the output of this macro, click begin_html <a href="gif/twoscales.gif" >here</a> end_html
   //Author: Rene Brun
     
   TCanvas *c1 = new TCanvas("c1","hists with different scales",600,400);

   //create/fill draw h1
   gStyle->SetOptStat(kFALSE);
   
   Int_t num_bins = 90;
   TH1F *h1 = new TH1F("h1","my histogram",num_bins,-3,3);
   Int_t i;
   for (i=0;i<10000;i++) h1->Fill(gRandom->Gaus(0,1));
   h1->Draw();
   c1->Update();  
    
   //create hint1 filled with the bins integral of h1
   TH1F *hint1 = new TH1F("hint1","h1 bins integral",num_bins,-3,3);
   Float_t sum = 0;
   for (i=1;i<=num_bins;i++) {
      sum += h1->GetBinContent(i); 
      hint1->SetBinContent(i,sum);
   }

   //scale hint1 to the pad coordinates
   Float_t rightmax = 1.1*hint1->GetMaximum();
   Float_t scale = gPad->GetUymax()/rightmax;
   hint1->SetLineColor(kRed);
   hint1->Scale(scale);
   hint1->Draw("same");
   
   //draw an axis on the right side
   TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
         gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
   axis->SetLineColor(kRed);
   axis->SetLabelColor(kRed);
   axis->Draw();
}
