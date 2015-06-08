

void lab8_1(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(3,1);
  
  
  Double_t xmin = 0.;
  Double_t xmax = 0.25;
  
  
  TFile* pions = new TFile("pions.root","UPDATE");
  
  TH1D* h1;
  TH1D* h2;
  TH1D* h3;
  TH1D* h4;
  
  // getting histograms from .root file
  h1 = (TH1D*) pions->Get("nump");
  h2 = (TH1D*) pions->Get("numn");
  h3 = (TH1D*) pions->Get("denp");
  h4 = (TH1D*) pions->Get("denn");
  
  pions->Close();
  
  c1->cd(1);
  TH1D* numerator;
  numerator = (TH1D*) h1->Clone("numerator");
  numerator->Add(h2);
  
  numerator->SetTitle("Licznik");
  numerator->SetMarkerStyle(4);
  numerator->SetMarkerColor(kRed);
  numerator->GetXaxis()->SetTitle("k*");
  numerator->GetYaxis()->SetTitle("zliczenia");
  numerator->GetXaxis()->SetRangeUser(0.,0.15);
  numerator->Draw();
  
  TLegend *leg1 = new TLegend(0.8,0.9,0.8,0.9);
  leg1->AddEntry(numerator,"nump+numn","l");
  leg1->Draw("same");
  
  
  c1->cd(2);
  
  TH1D* denominator;
  denominator = (TH1D*) h3->Clone("denominator");
  denominator->Add(h4);
  
  denominator->SetTitle("Mianownik");
  denominator->SetMarkerStyle(4);
  denominator->SetMarkerColor(kBlue);
  denominator->GetXaxis()->SetTitle("k*");
  denominator->GetYaxis()->SetTitle("zliczenia");
  denominator->GetXaxis()->SetRangeUser(0.,0.15);
  denominator->Draw();
  
  TLegend *leg2 = new TLegend(0.8,0.9,0.8,0.9);
  leg2->AddEntry(denominator,"denp+denn","l");
  leg2->Draw("same");
  
  c1->cd(3);
  
  
  TH1D* corr;
  corr = (TH1D*) numerator->Clone("corr");
  corr = corr->Divide(denominator);
  
  // function to fit
  TF1* fit_func = new TF1("fit","1+[0]*exp(-[1]*[1]*x*x/(0.197327*0.197327))",xmin,xmin);
  fit_func->SetParameter(0,1-corr->GetMaximum());
  fit_func->SetParameter(1,1);
  
  corr->SetTitle();
  corr->SetMarkerStyle(4);
  corr->SetMarkerColor(kGreen);
  corr->GetXaxis()->SetTitle("k*");
  corr->GetYaxis()->SetTitle("CE(k*)");
  corr->GetXaxis()->SetRangeUser(0.,0.15);
  corr->Draw();
  
  corr->Fit("fit","","",0,0.1);
  
  TLegend *leg3 = new TLegend(0.8,0.9,0.8,0.8);
  leg3->AddEntry(corr,"funkcja korelacji","l");
  leg3->AddEntry(corr->GetFunction("fit"),"dopasowanie","l");
  leg3->Draw("same");
  
  
  // save to .root file
  TFile* newfile = new TFile("pions2.root","recreate");
  numerator->Write();
  denominator->Write();
  corr->Write();
  newfile->Close();
  
  c1->SaveAs("plik.pdf");
  
}