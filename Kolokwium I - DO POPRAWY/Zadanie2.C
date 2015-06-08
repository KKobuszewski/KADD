void Zadanie2(){
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(2,1);
  
  Int_t N = 100000;
  Double_t R = 1.;
  Double_t xmin = 0;
  Double_t xmax = R;
  Double_t ymin = 0.;
  Double_t ymax = R;
  Int_t accepted = 0;
  Int_t rejected = 0;
  
  c1->cd(1);
  TF1 *func = new TF1("func","TMath::Sqrt(1-x*x)", xmin, xmax);
  Double_t c = func->Integral(xmin,xmax);
  func->SetTitle("Rozklad prawdopodobienstwa");
  func->GetXaxis()->SetTitle("x");
  func->GetYaxis()->SetTitle("p(x)");
  func->Draw();
  
  
  TH1D *distrib = new TH1D("distrib","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  TH2D *pts_accepted = new TH2D("pts_accepted","Zaakceptowane", 100, xmin, xmax, 100, 0., R);
  TH2D *pts_rejected = new TH2D("pts_rejected","Odrzucone", 100, xmin, xmax, 100, 0., R);
  
  for(int ii=0; ii<N; ii++){
    Double_t u = gRandom->Uniform(0.,1.);
    Double_t x = gRandom->Uniform(0.,1.);
    if (u < (TMath::Sqrt(1-x*x))){
      distrib->Fill(x);
      pts_accepted->Fill(x,u*R);
      accepted++;
    }
    else{
      pts_rejected->Fill(x,u*R);
      rejected++;
    }
  }
  //distrib->Scale((Double_t) accepted/distrib->Integral());
  //distrib->Draw("same");
  
  TLegend *leg1 = new TLegend(0.3,0.5,0.5,0.7);
  leg1->AddEntry(func,"Teoretyczna","l");
  //leg1->AddEntry(distrib,"Wylosowane","l");
  leg1->Draw("same");
  
  c1->cd(2);
  pts_accepted->SetTitle("Calkowanie MC");
  pts_accepted->GetXaxis()->SetTitle("x");
  pts_accepted->GetYaxis()->SetTitle("y");
  pts_accepted->SetMarkerStyle(20);
  pts_accepted->SetMarkerSize(0.5);
  pts_accepted->Draw();
  
  pts_rejected->SetMarkerColor(kBlue);
  pts_rejected->SetMarkerStyle(20);
  pts_rejected->SetMarkerSize(0.5);
  pts_rejected->Draw("same");
  
  TLegend *leg2 = new TLegend(0.5,0.4,0.9,0.75);
  leg2->AddEntry(pts_accepted,"Zaakceptowane","l");
  leg2->AddEntry(pts_rejected,"Odrzucone","l");
  leg2->Draw("same");
  
  // wydajnosc
  Double_t n = ((Double_t) accepted)/((Double_t) N);
  
  cout<<"Ilosc zaakceptowanych liczb w metodzie von Neumanna dla funkcji przedstawiajacej cwiartke kola jest proporcjonalna do jej pola, a to przy promieniu R=1 0.25*Pi"<<endl;
  cout<<"Zaakceptowane: "<<accepted<<endl;
  cout<<"Odrzucone: "<<rejected<<endl;
  cout<<"Wydajnosc: "<<n<<endl;
  cout<<"Wartosc calki MC (Pi/4): "<<n<<endl;
  cout<<"Wartosc Pi MC: "<<n*4<<endl;
}