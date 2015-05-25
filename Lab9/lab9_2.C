

void lab9_2(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  c1->Divide(2,1);
  
  Double_t xmin = 0.;
  Double_t xmax = 20.;
  
  c1->cd(1);
  
  TF1* array_func[20];
  
  for (int ii = 0; ii < 20; ii++){
    array_func[ii] = new TF1("chi2","TMath::Power(0.5,0.5*[0])*TMath::Power(x,0.5*[0]-1)*TMath::Exp(-0.5*x)/TMath::Gamma(0.5*[0])",xmin,xmax);
    array_func[ii]->SetParameter(0,ii+1);
    array_func[ii]->SetLineColor(ii);
    
    if (ii == 0)
      array_func[ii]->Draw();
    else
      array_func[ii]->Draw("same");
    
  }
  
  TH1D* array_hist[20];
  /*
  c1->cd(2);
  for (int ii = 0; ii < 20; ii++){
    array_hist[ii] = new TH1D("hist","blabla",1000,xmin,xmax);
    
    for(int ix = -30; ix<31; ix++){
      for(int iy = -30; iy<91; iy++){
	array_hist[ii]->SetBinContent(ix+30,iy+30,rozklad->Integral(1,ix+30,1,iy+30));
      }
    }
    
    if (ii == 0)
      array_func[ii]->Draw();
    else
      array_func[ii]->Draw("same");
    
  }*/
}