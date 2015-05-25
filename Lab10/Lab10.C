#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

void Lab10(){
  
  TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);

   c1->SetFillColor(255);
   c1->SetGrid();
   //c1->GetFrame()->SetFillColor(21);
   //c1->GetFrame()->SetBorderSize(12);

   const Int_t n = 10;
   Double_t x[n]  = {-0.9,-0.7,-0.5,-0.3,-0.1,0.1,0.3,0.5,0.7,0.9};
   Double_t y[n]  = {3.0,60.,89.,98.,99.,106.,142.,215.,334.,532.};
   Double_t ex[n] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};
   Double_t ey[n] = {1.,4.,3.,7.,3.,8.,2.,3.,7.,9.};
   TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetTitle("Linear Least Square Polynomial Fit");
   gr->SetMarkerColor(4);
   gr->SetMarkerSize(0);
   gr->Draw("AP");
   
   //c1->Update();
   
   Double_t res[n];   
   TF1* func_arr[n];
   TLegend *legend = new TLegend(0.1,0.4,0.6,0.9);
   
   TString* formula = new TString("[");
   for (int ii = 0; ii<n; ii++) {
     
     // Strings specified for each TF1 object
     formula->Append(TString::Itoa(ii,10));
     formula->Append("]*x^");
     formula->Append(TString::Itoa(ii,10));
     TString* func_num = new TString("func");
     func_num->Append(TString::Itoa(ii,10));
     cout<<formula->Data()<<endl;
     
     Double_t *a_vec = new Double_t[ii+1];
     Double_t *a_sig_vec = new Double_t[ii+1];
     res[ii] = linear_lsq_polynomial_fit(ii,n,x,y,ey,a_vec,a_sig_vec);
     
     func_arr[ii] = new TF1(func_num->Data(),formula->Data(),-1.,1.);
     //cout<<endl<<"function allocated!"<<endl;
     for (int jj = 0; jj <= ii; jj++){
       //cout<<"a"<<jj<<"="<<a_vec[jj]<<", "<<endl;
       func_arr[ii]->SetParameter(jj,a_vec[jj]);
     }
     func_arr[ii]->SetLineColor(ii+1);
     if (ii == n-1)
       func_arr[ii]->SetLineColor(1);
     func_arr[ii]->Draw("same");
     legend->AddEntry(func_arr[ii],(TString::Itoa(ii,10)).Append("-th order polynomial"),"l");
     
     cout<<ii<<"-th order residual error:"<<res[ii]<<endl;
     
     if (ii !=(n-1))
       formula->Append("+[");
   }
   
   cout<<endl<<endl<<endl<<"M-function values for fitted polynomials:"<<endl<<endl;
   for (int ii = 0; ii<n; ii++) {
     //if (ii > 0)
     //  res[ii]-=res[ii-1];
     cout<<ii<<"-th order residual error:"<<res[ii]<<endl;
   }
   cout<<endl<<endl<<endl;
   legend->Draw("same");
}

Double_t linear_lsq_polynomial_fit(
  Int_t r, /*Stopien wielomianu*/
  Int_t n, /*Ilosc pomiarow*/
  Double_t *t_vec, /*tablica wielkosci kontrolowanych w pomiarze*/
  Double_t *y_vec, /*tablica wielkosci zmierzonych*/
  Double_t *y_sig_vec, /*tablica niepewnosci wielkosci zmierzonych*/
  Double_t *a_vec, /*tablica niepewnosci wspolczynnikow - musi byc zaalokowana i miec rozmiar r+1!*/
  Double_t *a_sig_vec /*tablica niepewnosci wspolczynnikow - musi byc zaalokowana i miec rozmiar r+1!*/
  ) {
  /*
   * Int_t r - degree of polynomial to fit
   * Int_t n - length of data vector
   * Double_t *t_vec - vector of controlled parameters /Double_t array of length n/
   * Double_t *y_vec - vector of data to be fit (Double_t array of length n)
   * Double_t *y_sig_vec - vector of measurement uncertainties (standard deviations) /Double_t array of length n/
   * Double_t *a_vec - array to save fitted coefficients /Double_t array of length r+1/
   * Double_t *a_sig_vec - array to save fitted coefficients statistical uncernities /Double_t array of length r+1/
   */
  
  cout<<endl<<"***************************************************************************************************************"<<endl;
  cout<<endl<<"\t\t\t\tLINEAR LEAST SQUARE POLYNOMIAL FIT";
  cout<<endl<<"***************************************************************************************************************"<<endl;
  cout<<"Polynomial degree\tr:\t"<<r<<endl<<"Data vector lenght\tn:\t"<<n<<endl;
  cout<<endl<<"***************************************************************************************************************"<<endl;
  
  if (r>=n) {
    cout<<"To large r!"<<endl;
    return -1.;
  }
  
  // matrix of control parameter's coeffs
  TMatrixD A_mat(n,r+1);
  for (int ii=0; ii <= r; ii++){
    for (int jj=0; jj < n; jj++){
      A_mat(jj,ii) = TMath::Power(t_vec[jj],ii);
    }
  }  
  //A_mat.Print();
  
  // vector of results
  TMatrixD c_vec(n,1);
  for (int ii=0; ii<n; ii++){
    c_vec(ii,0) = y_vec[ii];
  }
  //c_vec.Print();
  
  
  // Matrices of stdev and variancy
  TMatrixD H_mat(n,n);
  for (int ii=0; ii<n; ii++){
    H_mat(ii,ii) = 1./y_sig_vec[ii];
  }
  TMatrixD Gy_mat = TMatrixD(H_mat,TMatrixD::kMult,H_mat);
  
  //H_mat.Print();
  //Gy_mat.Print();
  
  
  //  Calculating coefficients
  TMatrixD HA_mat = TMatrixD(H_mat, TMatrixD::kMult, A_mat);
  TMatrixD Hc_vec = TMatrixD(H_mat, TMatrixD::kMult, c_vec);
  
  //HA_mat.Print();
  //Hc_vec.Print();
  
  TMatrixD Cov_mat = TMatrixD(HA_mat,TMatrixD::kTransposeMult,HA_mat); // macierz kowariancji !!! Cx
  Cov_mat.Invert();
  TMatrixD HATHc_vec = TMatrixD(HA_mat,TMatrixD::kTransposeMult,Hc_vec);
  
  TMatrixD result_vec = TMatrixD(Cov_mat,TMatrixD::kMult,HATHc_vec);
  //a_vec = new Double_t[r+1];
  for (int ii=0; ii <= r; ii++){
    a_vec[ii] = result_vec(ii,0);
  }
  //result_vec.Print();
  
  //a_sig_vec = new Double_t[r+1];
  for (int ii=0; ii <= r; ii++){
    a_sig_vec[ii] = TMath::Sqrt(Cov_mat(ii,ii));
  }
  //HATHA_inv_mat.Print();
  
  // Corrected values vector
  TMatrixD eta_vec = TMatrixD(A_mat,TMatrixD::kMult,result_vec);
  //eta_vec.Print();  
  
  // Error vector 
  TMatrixD error_vec(n,1);
  error_vec = c_vec - eta_vec;
  Double_t residual_sum = 0.;
  residual_sum = (Double_t) TMatrixD(error_vec,TMatrixD::kTransposeMult,TMatrixD(Gy_mat,TMatrixD::kMult,error_vec)) (0,0);
  TMatrixD(error_vec,TMatrixD::kTransposeMult,TMatrixD(Gy_mat,TMatrixD::kMult,error_vec)).Print();
  
  cout<<"Fitted coefficients"<<endl;
  for (int jj = 0; jj <= r; jj++){
       cout<<"a"<<jj<<"="<<a_vec[jj]<<"+/-"<<a_sig_vec[jj]<<endl;
  }
  cout<<endl<<"Sum of squares of residuals: "<<residual_sum<<endl;
  
  cout<<endl<<"***************************************************************************************************************"<<endl;
  cout<<endl;
  return residual_sum;
}