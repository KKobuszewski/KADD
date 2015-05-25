


void lab7_2(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(2,2);
  
  
  // A)
  
  c1->cd(1);
  Double_t xmin = -8.;
  Double_t xmax = 8.;
  
  //c1->SetLogy();
  
  TH1D* h1 = new TH1D("h1","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  //TF1* gauss;
  
  for (int ii=0; ii< 100000; ii++){
      Double_t suma = 0.;
      suma = (8*gRandom->Uniform()-5)+(8*gRandom->Uniform()-3);
      h1->Fill(suma);
  }
  h1->Sumw2();
  h1->Fit("gaus");
  h1->Draw();
  //TF1 f1 = h1->GetFunction("gaus");
  cout<<"Nie dziala"<<endl;
  
  
  
  // B)
  
  c1->cd(2);
  Double_t xmin = -10.;
  Double_t xmax = 10.;
  
  //c1->SetLogy();
  
  TH1D* h2 = new TH1D("h2","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  //TF1* gauss;
  
  for (int ii=0; ii< 100000; ii++){
      Double_t suma = 0.;
      suma = (gRandom->Gaus(-2, TMath::Sqrt(1) ))  +  (gRandom->Gaus(1, TMath::Sqrt(4) ));
      h2->Fill(suma);
  }
  h2->Sumw2();
  h2->Fit("gaus");
  h2->Draw();
  //TF1 f2 = h2->GetFunction("gaus");
  
  
  
  
  
  // C)
  
  c1->cd(3);
  Double_t xmin = -20.;
  Double_t xmax = 20.;
  
  //c1->SetLogy();
  
  TH1D* h3 = new TH1D("h3","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  //TF1* gauss;
  
  for (int ii=0; ii< 100000; ii++){
      Double_t suma = 0.;
      suma = (gRandom->Gaus(0., TMath::Sqrt(9./4.) ))  +  (20*gRandom->Uniform()-10);
      h3->Fill(suma);
  }
  h3->Sumw2();
  h3->Fit("gaus");
  h3->Draw();
  //TF1 f2 = h2->GetFunction("gaus");
  
  
  // D)
  
  c1->cd(4);
  Double_t xmin = 0.;
  Double_t xmax = 10.;
  
  //c1->SetLogy();
  
  TH1D* h4 = new TH1D("h4","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  //TF1* gauss;
  
  for (int ii=0; ii< 100000; ii++){
      Double_t suma = 0.;
      for (int jj=0; jj<10; jj++){
	suma += gRandom->Uniform();
      }
      h4->Fill(suma);
  }
  h4->Sumw2();
  h4->Fit("gaus");
  TF1 func;
  func = h4->GetFunction("gaus");
  
  h4->Draw();
  func.Draw("same");
  
  //cout<<"Chisq/ndf: "<<func.GetChisquare()/func.GetNDF()<<endl;
}