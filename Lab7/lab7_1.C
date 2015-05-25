

void lab7_1(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,700,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  //c1->Divide(2,1);
  
  Double_t xmin = 0.;
  Double_t xmax = 2.;
  
  c1->SetLogy();
  
  TH1D* h1;
  TF1 f1;
  //TF1* gauss;
  int counter = 2;
  Double_t chi2 = 100,;
  Double_t ndf = 1;
  while(chi2 > ndf){
    
    xmax = (Double_t) counter;
    h1 = new TH1D("h1","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
    for (int ii=0; ii< 100000; ii++){
      Double_t suma = 0.;
      for (int jj = 0; jj<counter; jj++){
	suma += gRandom->Uniform();
      }
      h1->Fill(suma);
    }
    /*if (counter>2)
      h1->Draw("same");
    else
      h1->Draw();*/
    h1->Sumw2();
    
    //gauss = new TF1("gauss",fitf,xmin,xmax,3);
    //gauss->SetParameters(h1->GetMaximum(),h1->GetMean(),h1->GetRMS());
    //gauss->SetParNames("Constant","Mean_value","Sigma");
    h1->Fit("gaus");
    f1 = h1->GetFunction("gaus");
    
    h1->GetXaxis()->SetTitle("x");
    h1->GetYaxis()->SetTitle("ilosc zliczen w histogramie");
    h1->Draw();
    //f1->Draw("same");
    
    chi2 = f1->GetChisquare();
    ndf = f1->GetNDF();
    counter++;
    
    c1->Modified();
    c1->Update();
 }
 
 cout<<counter<<"razy"<<endl;
}

Double_t fitf(Double_t *v, Double_t *par) {
      Double_t arg = 0;
      if (par[2] != 0) arg = (v[0] - par[1])/par[2];

      Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
      return fitval;
}