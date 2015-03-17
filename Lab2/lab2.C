

void lab2(){
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,700,500);//Pamietac o wskazniku
  c1->SetFillColor(255);
  
  c1->Divide(2,2);
  
  Double_t x_min = -3.;
  Double_t x_max = 3.;
  Double_t y_min = -3.;
  Double_t y_max = 9.;
  TF2* f1 = new TF2("f1","1/(2*TMath::Pi()*[0]*[1]*sqrt(1-[2]*[2]))*exp(-0.5*((x-[3])^2/([0]*[0])+(y-[4])^2/([1]*[1])-2*[2]*(x-[3])*(y-[4])/([0]*[1]))/(1-[2]*[2]))",x_min,x_max,y_min,y_max);
  f1->SetParameter(0,1);//sigmx
  f1->SetParameter(1,2);//sigmy
  f1->SetParameter(2,0);//rho
  f1->SetParameter(3,0);//mux
  f1->SetParameter(4,3);//muy
  //Double_t C = 1./f1->Integral(x_min,x_max);
  //cout<<"Stala unormowania C: "<<C<<"\n";
  //f1->SetParameter(0,C);
  
  //Int_t num_bins = 3000;
  //TH1D *h1 = new TH1D("h1","h1 bins integral",num_bins,x_min,x_max);
  //for (int ii = 0; ii < num_bins; ii++)
  //  h1->SetBinContent(ii,f1->Integral(x_min,(x_min,x_max)/num_bins*ii));
  
  c1->cd(1);
  f1->Draw("lego2");
  f1->SetTitle("Rozklad gestosci prawdopoodobienstwa");
  f1->GetXaxis()->SetTitle("x");
  f1->GetYaxis()->SetTitle("y");
  f1->GetZaxis()->SetTitle("p(x,y)");
  
  //Dystrybuanta
  TH2F* dystrybuanta = new TH2F("dystrybuanta","Dystrybuanta", 60, x_min, x_max, 120, y_min, y_max);
  TH2F* rozklad = new TH2F("rozklad","Rozklad", 60, x_min, x_max, 120, y_min, y_max);
  rozklad->FillRandom("f1",1e7);
  rozklad->Scale(1./rozklad->Integral());
    
  for(int ix = -30; ix<31; ix++){
   for(int iy = -30; iy<91; iy++){
     dystrybuanta->SetBinContent(ix+30,iy+30,rozklad->Integral(1,ix+30,1,iy+30));
   }
  }
    
  c1->cd(2);
  dystrybuanta->Draw("lego2");
  //dystrybuanta->DrawIntegal
  dystrybuanta->SetTitle("Dystrybuanta");
  dystrybuanta->GetXaxis()->SetTitle("x");
  dystrybuanta->GetYaxis()->SetTitle("y");
  dystrybuanta->GetZaxis()->SetTitle("F(x,y)");
  
  //Gestosc brzegowa X
  TH1D* marginalX = new TH1D("marginalX","Rozklad brzegowy X",60,x_min,x_max);
  for(int ix = 1; ix<61; ix++)
    marginalX->SetBinContent(ix, rozklad->Integral(ix,ix,1,120));
  
  c1->cd(3);
  marginalX->Draw();
  marginalX->SetTitle("Rozklad brzeegowy X");
  marginalX->GetXaxis()->SetTitle("x");
  marginalX->GetYaxis()->SetTitle("g(x)");
  
  //Gestosc brzegowa Y
  TH1D* marginalY = new TH1D("marginalY","Rozklad brzegowy Y",120,y_min,y_max);
  for(int iy = 1; iy<121; iy++)
    marginalY->SetBinContent(iy, rozklad->Integral(1,60,iy,iy));
  
  c1->cd(4);
  marginalY->Draw();
  marginalY->SetTitle("Rozklad brzeegowy Y");
  marginalY->GetXaxis()->SetTitle("y");
  marginalY->GetYaxis()->SetTitle("h(y)");
  
  //Parametry rozkladu
  Double_t varX = sqrt(f1->Variance2X(x_min,x_max,y_min,y_max));
  Double_t varY = sqrt(f1->Variance2Y(x_min,x_max,y_min,y_max));
  Double_t cov = sqrt(f1->Covariance2XY(x_min,x_max,y_min,y_max));
  
  //cout<<"Wartosc srednia: "<<f1->Mean()<<endl;
  cout<<"Wartosc srednia X: "<<f1->Mean2X(x_min,x_max,y_min,y_max)<<endl;
  cout<<"Wartosc srednia Y: "<<f1->Mean2Y(x_min,x_max,y_min,y_max)<<endl;
  cout<<"Wariancja X: "<<varX*varX<<endl;
  cout<<"Wariancja Y: "<<varY*varY<<endl;
  cout<<"Kowariancja: "<<cov<<endl;
  cout<<"Wspolczynnik korelacji: "<<cov/(varX*varY)<<endl;
  
}