
# DOPASOWANIE DO PREDEFINIOWANYCH FUNCKJI
  
  // DOPASOWANIE POISSON
  TF1* fit_func = new TF1("fit","TMath::Power([0],x)*TMath::Exp(-[0])/TMath::Gamma(x+1)",xmin,xmin);
  fit_func->SetParameter(0,mean_data);
  
  histogram->Fit(fit_func);
  fit_func->SetTitle("dopasowanie Poisson");
  
  // DOPASOWANIE GAUSS - DRUGA FUNKCJA
  histogram->Fit("gaus","+");
  //TF1* gauss = new TF1("gauss","TMath::Gauss(x,37.76599,5.29973)");
  TF1* gauss;
  gauss = histogram->GetFunction("gaus");
  gauss->SetLineColor(kGreen);
  

# TEST PEARSONA
  
  // fit_func musi byc TF1 lub TF2
  Double_t chi_pearson = 0;
  for (int ii=0; ii< n; ii++) {
    chi_pearson += (nk[ii] - num_data*fit_func->Eval(k[ii]))*(nk[ii] - num_data*fit_func->Eval(k[ii]))/(num_data*fit_func->Eval(k[ii]));
  }
  
  //poziom istotnosci
  alpha = 0.01;
  chi_critic = TMath::ChisquareQuantile(1-alpha,<ndf>); // uzupelnic ndf
  
  cout<<"Ndf: "<<ndf<<endl;
  cout<<"Chi2: "<<chi_pearson<<endl;
  cout<<"Chi2("<<100*alpha<<"%): "<<chi_critic<<endl;
  
  if (chi_pearson < chi_critic) {
    cout<<"NIE MA POWODOW DO ODRZUCENIA HIPOTEZY"<<endl;
  }
  
  
# WIELOMIANOWE
  TGraphErrors* grErr = new TGraphErrors(10,tabx,taby,0,tabuy);
  grErr->SetTitle("Dane");
  grErr->SetLineColor(kBlack);
  grErr->SetMarkerColor(kBlack);
  grErr->SetMarkerSize(2);
  grErr->Draw("ap");
  
  // UWAGA POTRZEBA TU WSKAZNIKA!!!
  TF1* fity[4];
  
  for (int ii = 1; ii < 5; ii++){
    char buf[5];
    snprintf(buf, sizeof(buf), "%s%i", "pol",ii);
    cout<<buf<<endl;
    grErr->Fit(buf,"+");
    fity[ii-1] = grErr->GetFunction(buf); // ZWRACA WSKAZNIK !!!
    fity[ii-1]->SetLineColor(ii+1);
    fity[ii-1]->Draw("same");
    
  }
  