
void Lab6(){
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(2,1);
  
  Int_t N = 100000;
  Double_t xmin = 0.;
  Double_t xmax = 2.;
  
  
  
  Int_t accepted = 0;
  Int_t rejected = 0;
  
  c1->cd(1);
  
  
  // definicje funckji do metody von Neumanna
  TF1 *f = new TF1("f","[0]*TMath::Exp(x)", xmin, xmax);
  f->SetParameter(0,1);
  Double_t c = 1./f->Integral(xmin,xmax); // stala unormowania
  f->FixParameter(0,c);
  f->SetTitle("Rozklad prawdopodobienstwa");
  f->GetXaxis()->SetTitle("x");
  f->GetYaxis()->SetTitle("p(x)");
  f->Draw();
  
  TF1 *g = new TF1("g","[0]*x+[1]",xmin,xmax);
  Double_t b = c*TMath::Exp(xmin);
  Double_t a = 0.5*c*(TMath::Exp(xmax) - TMath::Exp(xmin));
  g->FixParameter(0,a);
  g->FixParameter(1,b);
  g->SetLineColor(kGreen);
  g->Draw("same");
  
  
  
  cout<<"Stala normawania: "<<c<<endl;
  cout<<"a: "<<a<<endl;
  cout<<"b: "<<b<<endl;
  cout<<"Calka z rozkladu: "<<f->Integral(xmin,xmax)<<endl;
  
  TH1D *distrib = new TH1D("distrib","Histogram rozkladu prawdopodobienstwa",100,xmin,xmax);
  
  TH2D *pts_accepted = new TH2D("pts_accepted","Zaakceptowane", 100, xmin, xmax, 100, 0., 1.);
  TH2D *pts_rejected = new TH2D("pts_rejected","Odrzucone", 100, xmin, xmax, 100, 0., 1.);
  
  for(int ii=0; ii<N; ii++){
    Double_t u = gRandom->Uniform(0.,1.);
    Double_t y = 2.*(a+b)*gRandom->Uniform(0.,1.);
    Double_t x = (-b + TMath::Sqrt(b*b + 2*a*y))/a;
    if ( c*TMath::Exp(x)/(a*x+b) > u) {
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