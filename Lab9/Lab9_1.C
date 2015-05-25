

void Lab9_1(){
  gStyle->SetOptFit(1111);
  TCanvas *c1 = new TCanvas("c1","f(x)",200,10,1200,700);//Pamietac o wskazniku
  c1->SetFillColor(255);
  //c1->Divide(3,1);
  
  Int_t n = 9;
  
  Double_t k[] = {0,1,2,3,4,5,6,7,8};
  Double_t nk[] = {47,69,84,76,49,16,11,3,0};
  Double_t xmin = k[0];
  Double_t xmax = k[n-1];
  
  Double_t num_data = 0;
  for (int ii=0; ii< n; ii++) {
    num_data += nk[ii];
  }
  cout<<"ilosc pomiarow: "<<num_data<<endl;
  
  Double_t mean_data = 0;
  for (int ii = 0; ii < n; ii++) {
    mean_data += k[ii]*nk[ii];
  }
  mean_data /= num_data;
  cout<<"estymator wartosci oczekiwanej: "<<mean_data<<endl;
  
  TGraph* points = new TGraph(n,k,nk);
  points->Draw("A*");
  //points->SetMarekerSize(100);
  
  TF1* fit_func = new TF1("fit","[0]*TMath::Power([1],x)*TMath::Exp(-[1])/TMath::Gamma(x+1)",xmin,xmin);
  fit_func->SetParameter(0,1);
  fit_func->SetParameter(1,mean_data);
  
  points->Fit("fit");
  //fit_func->Draw("same");
  
  cout<<"lambda "<<fit_func->GetParameter(1)<<endl;
  cout<<"Stala unormowania: "<<1./fit_func->GetParameter(0)<<endl;
  fit_func->SetParameter(0,1);
  
  Double_t chi_pearson = 0;
  for (int ii=0; ii< n; ii++) {
    chi_pearson += (nk[ii] - num_data*fit_func->Eval(k[ii]))*(nk[ii] - num_data*fit_func->Eval(k[ii]))/(num_data*fit_func(k[ii]));
    
  }
  
  TLegend *leg3 = new TLegend(0.8,0.9,0.7,0.8);
  leg3->AddEntry(points,"Pomiary","l");
  leg3->AddEntry(fit_func,"dopasowanie Poisson","l");
  leg3->Draw("same");
  
  cout<<"Chi2: "<<chi_pearson<<endl;
  cout<<"Chi2(99%): "<<TMath::ChisquareQuantile(0.99,n-2)<<endl;
  
  if (chi_pearson < TMath::ChisquareQuantile(0.99,n-2)) {
    cout<<"NIE MA POWODOW DO ODRZUCENIA HIPOTEZY"<<endl;
  }
  
}