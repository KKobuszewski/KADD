//_____________________macro fitexample.C___________________________
Double_t fitf(Double_t *v, Double_t *par)
{
   Double_t arg = 0;
   if (par[2] != 0) arg = (v[0] - par[1])/par[2];
 
   Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
   return fitval;
}
 
void fitexample()
{
   TFile *f = new TFile("hsimple.root");
 
   TH1F *hpx = (TH1F*)f->Get("hpx");
 
   //create a function with 3 parameters in the range [-3,3]
   TF1 *func = new TF1("fit",fitf,-3,3,3);
   func->SetParameters(500,hpx->GetMean(),hpx->GetRMS());
   func->SetParNames("Constant","Mean_value","Sigma");
   hpx->Fit("fit");
}