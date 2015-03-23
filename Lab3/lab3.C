

#include <stdio.h>


void lab3(){
    gStyle->SetOptStat(0);
    std::fstream plik;
    plik.open( "NumericalRecipes.txt", std::ios::in | std::ios::out );
    
    TH2D* widmo = new TH2D("widmo","Rozklad widmowy generatora",100,0.,1.,100,0.,1.);//histogram 2D na obszarze (0;1)x(0;1)
    
    //Zczytywanie danych i wypelnienie histogramu
    Double_t value = 0.;
    if (plik.good()){
      plik>>value;
      printf("%f\n",value);
      while ( !plik.eof() ){
	Double_t temp = value;
	plik>>value;
	printf("%f\n",value);
	widmo->Fill(temp,value);
      }
      plik.close();
    }
    
    
    TCanvas *c1 = new TCanvas("c1","f(x)",200,10,700,500);//Pamietac o wskazniku
    c1->SetFillColor(255);
  
    //c1->Divide(2,2);
    
    c1->SetGrid();
    widmo->GetXaxis()->SetTitle("X_{n}");
    widmo->GetYaxis()->SetTitle("X_{n+1}");
    widmo->Draw("colz");
}