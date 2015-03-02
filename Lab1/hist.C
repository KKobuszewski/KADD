#include <TCanvas.h>
#include <TH1F.h>
#include <TAxis.h>
#include <TF1.h>


void hist() {
   
   TCanvas *c1 = new TCanvas("c1","Simple histogram example",200,10,700,500);
   c1->SetGrid();

   TH1F* hRandom = new TH1F("hRandom","Random distribution",100,-5,5);
   hRandom->FillRandom("gaus",1e5);

   hRandom->GetXaxis()->SetTitle("N");
   hRandom->GetYaxis()->SetTitle("dN");
   hRandom->Draw();

   TF1* fGaus = new TF1("fGaus","gaus",-5,5);
   hRandom->Fit(fGaus);


}