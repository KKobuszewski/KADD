

  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,700,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  //c1->Divide(2,1);
  
  
# SKALA LOGARYTMICZNA
  
  c1->SetLogy();
  
  
# OPIS OSI, TYTUŁ
  
  TF1 *f = new TF1("f","[0]*TMath::Exp(x)", xmin, xmax);
  f->SetParameter(0,1);
  Double_t c = 1./f->Integral(xmin,xmax); // stala unormowania
  f->FixParameter(0,c);
  f->SetTitle("Rozklad prawdopodobienstwa");
  f->GetXaxis()->SetTitle("x");
  f->GetYaxis()->SetTitle("p(x)");
  f->Draw();
  
  
# LEGENDA
  
  TLegend *leg3 = new TLegend(0.8,0.9,0.5,0.7);
  leg3->AddEntry(histogram,"Pomiary","l");
  leg3->AddEntry(fit_func,"dopasowanie Poisson","l");
  leg3->AddEntry(gauss,"dopasowanie Gauss","l");
  leg3->Draw("same");
  
  
# FORMATOWANIE LINII, MARKERÓW
  
  f->SetMarkerStyle(20);
  f->SetMarkerSize(0.5);
  f->SetLineColor(kGreen);
  
  
# SŁUPKI BŁĘDÓW
  
  histogram->Sumw2();