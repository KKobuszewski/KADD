
void lab1(){
  
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,700,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  
  c1->Divide(2,1);
  
  Double_t x_min = 0.;
  Double_t x_max = 3.;
  TF1* f1 = new TF1("f1","[0]*(-exp(-4*x*x)+exp(-x*x))",x_min,x_max);
  f1->SetParameter(0,1);
  Double_t C = 1./f1->Integral(x_min,x_max);
  cout<<"Stala unormowania C: "<<C<<"\n";
  f1->SetParameter(0,C);
  
  Int_t num_bins = 3000;
  TH1D *h1 = new TH1D("h1","h1 bins integral",num_bins,x_min,x_max);
  for (int ii = 0; ii < num_bins; ii++)
    h1->SetBinContent(ii,f1->Integral(x_min,(x_min,x_max)/num_bins*ii));
  
  c1->cd(1);
  f1->Draw();
  c1_1->SetGrid();
  f1->SetTitle("rozklad gestosci prawdopoodobienstwa");
  f1->GetXaxis()->SetTitle("x");
  f1->GetYaxis()->SetTitle("p(x)");
  
  c1->cd(2);
  h1->Draw();
  c1_2->SetGrid();
  h1->SetTitle("Dystrybuanta");
  h1->GetXaxis()->SetTitle("x");
  h1->GetYaxis()->SetTitle("F(x)");
  
  cout<<"Statystyka rozkladu\n";
  cout<<"Modalna\t\t\t:"<<f1->GetMaximumX()<<"\n";
  cout<<"Kwantyl dolny\t\t: "<<hist_value(num_bins,0.25,h1,x_min,x_max)<<"\n";
  cout<<"Mediana\t\t\t: "<<hist_value(num_bins,0.50,h1,x_min,x_max)<<"\n";
  cout<<"Kwantyl gorny\t\t: "<<hist_value(num_bins,0.75,h1,x_min,x_max)<<"\n";
  cout<<"Wartosc oczekiwana\t : "<<f1->Mean(x_min, x_max)<<"\n";
  cout<<"Wariancja\t\t : "<<f1->Variance(x_min, x_max)<<"\n";
  cout<<"Odchylenie standardowe\t : "<<sqrt(f1->Variance(x_min, x_max))<<"\n";
  
}


Double_t hist_value(Int_t num_bins, Double_t y, TH1D* h1,Double_t x_min, Double_t x_max){
  //This function returns bin for given value on hist
  int ii = 0;
  while((h1->GetBinContent(ii)<y) && (ii<num_bins)){
    ii++;
  }
  return Double_t(ii)*(x_max-x_min)/num_bins;
}