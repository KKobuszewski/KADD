
void Lab6_3(){
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(2,1);
  
  Int_t N = 100000;
  Double_t xmin = 0.;
  Double_t xmax = 0.5*TMath::Pi();
  Double_t x0 = 0.25*TMath::Pi();
  
  
  
  Int_t accepted = 0;
  Int_t rejected = 0;
  
  c1->cd(1);
  
  
  // definicje funckji do metody von Neumanna
  TF1 *f = new TF1("f","[0]*TMath::Sin(x)", xmin, xmax);
  f->SetParameter(0,1);
  Double_t c = 1./f->Integral(xmin,xmax); // stala unormowania
  f->FixParameter(0,c);
  f->SetTitle("Rozklad prawdopodobienstwa");
  f->GetXaxis()->SetTitle("x");
  f->GetYaxis()->SetTitle("p(x)");
  f->Draw();
  
  TF1 *g = new TF1("g","[0]*(x-[1])+[2]",xmin,xmax);
  Double_t a = c*TMath::Cos(x0);
  Double_t b = c*(TMath::Sin(x0) - x0*TMath::Cos(x0));
  g->FixParameter(0,c*TMath::Cos(x0));
  g->FixParameter(1,x0);
  g->FixParameter(2,c*TMath::Sin(x0));
  g->SetLineColor(kGreen);
  g->Draw("same");
  
  
  cout<<"Styczna w punkcie: "<<x0<<endl;
  cout<<"Stala normawania: "<<c<<endl;
  cout<<"a: "<<a<<endl;
  cout<<"b: "<<b<<endl;
  cout<<"Calka z rozkladu: "<<f->Integral(xmin,xmax)<<endl;
  
  TH1D *distrib = new TH1D("distrib","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  TH2D *pts_accepted = new TH2D("pts_accepted","Zaakceptowane", 100, xmin, xmax, 100, 0., 1.);
  TH2D *pts_rejected = new TH2D("pts_rejected","Odrzucone", 100, xmin, xmax, 100, 0., 1.);
  
  for(int ii=0; ii<N; ii++){
    Double_t u = gRandom->Uniform(0.,1.);
    Double_t y = (0.5*a*TMath::Pi()*TMath::Pi() - b*TMath::Pi()) * gRandom->Uniform(0.,1.);
    Double_t x = (-b + TMath::Sqrt(b*b + 2*a*y))/a;
    if ( c*TMath::Sin(x)/(a*x+b) > u) {
      distrib->Fill(x);
      pts_accepted->Fill(x,u);
      accepted++;
    }
    else{
      pts_rejected->Fill(x,u);
      rejected++;
    }
  }
  distrib->Scale(1./distrib->Integral("width"));
  distrib->Draw("same");
  
  TLegend *leg1 = new TLegend(0.3,0.5,0.5,0.7);
  leg1->AddEntry(f,"f(x)","l");
  leg1->AddEntry(g,"g(x)","l");
  leg1->AddEntry(distrib,"Wylosowane","l");
  leg1->Draw("same");
  
  c1->cd(2);
  pts_accepted->SetTitle("Zaakceptowane/odrzucone");
  pts_accepted->GetXaxis()->SetTitle("x");
  pts_accepted->GetYaxis()->SetTitle("u");
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
  
  cout<<"Zaakceptowane: "<<accepted<<endl;
  cout<<"Odrzucone: "<<rejected<<endl;
  cout<<"Wydajnosc: "<<n<<endl;
  /*cout<<"Wartosc calki MC: "<<n*4/TMath::Pi()<<endl;*/
}