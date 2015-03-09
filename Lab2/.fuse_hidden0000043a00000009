#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TFrame.h>
#include <TMath.h>
#include <TH2D.h>
#include <TH2F.h>
#include <>


void histogramy_2D() {
   
   TCanvas *c1 = new TCanvas("c1","Program 3",200,10,700,500);

   c1->Divide(2,2);
   c1->SetGrid();
   
   c1->cd(1);
   TF2* funkcja = new TF2("funkcja","(1/(2*TMath::Pi()*[0]*[1]*sqrt(1-[2]^2)))*exp((-1/(2*(1-[2]^2)))*(((x-[3])^2/([0]^2))+((y-[4])^2/([1]^2))-(2*[2])*((x-[3])*(y-[4]))/([0]*[1])))",-5,5,-5,5);
   funkcja->SetParameter(0,1);
   funkcja->SetParameter(1,2);
   funkcja->SetParameter(2,0.5);
   funkcja->SetParameter(3,1);
   funkcja->SetParameter(4,1);
   funkcja->GetXaxis()->SetTitle("X");
   funkcja->GetYaxis()->SetTitle("Y");
   funkcja->SetTitle("f(x,y)");
   funkcja->Draw("surf");
   
   cout<<funkcja->Integral(-5,5,-5,5)<<endl;
   
   c1->cd(2);
   
   
   //Dystrybuanta 2D
   TH2F* h2Dist=new TH2F("h3","histogram2",100,-5,5,100,-5,5);
   /*Pomocniczy histogram liczacy gestosc prawdopodobienstwa
   TH2F* h2 = new TH2F("h2","histogram",100,-5,5,100,-5,5);
   
   h2->FillRandom("funkcja",1e6);
   h2->Scale(1./h2->Integral());//Normowanie rozkladu gestosci
   */
   
   //https://root.cern.ch/drupal/content/function-integration
   //ROOT::Math::AdaptiveIntegratorMultiDim ig;
   //ig.SetFunction(funkcja);
   //ig.SetTolerance(0.001);
   //Double_t x_min[] = {-5,-5};
   
   //liczenie dystrybuanty
   for(int x=-50;x<50;x++)
   {
     for(int y=-50;y<50;y++)
     {
       Double_t x_max[] = {x/10,y/10};
       Double_t Integ = 1;//ig.Integral(x_min,x_max);
       h2Dist->SetBinContent(x,y,Integ);
     }
   }
   h2Dist->GetXaxis()->SetTitle("X");
   h2Dist->GetYaxis()->SetTitle("Y");
   h2Dist->SetTitle("Funkcja dystrybuanty F(x,y)");
   h2Dist->Draw("surf");
   
   
   
   c1->cd(3);
   TH1D* hProjX= h2->ProjectionX();
   hProjX->GetXaxis()->SetTitle("X");
   hProjX->GetYaxis()->SetTitle("Y");
   hProjX->SetTitle("Gestosc brzegowa g(x)");
   hProjX->Draw();
   
   c1->cd(4);
   TH1D* hProjY= h2->ProjectionY();
   hProjY->GetXaxis()->SetTitle("X");
   hProjY->GetYaxis()->SetTitle("Y");
   hProjY->SetTitle("Gestosc brzegowa h(y)");
   hProjY->Draw();
   
   Double_t a=funkcja->Mean(-5,5);
   cout<<"Wartosc srednia: "<<a<<endl;
   
   Double_t b=hProjX->GetMean();
   cout<<"Wartosc srednia: "<<b<<endl;
  
   Double_t c = funkcja->Variance2X(-5,5,-5,5,0.000001);
   cout<<"Wariancja: "<<sqrt(c)<<endl;
   
   Double_t d = funkcja->Variance2Y(-5,5,-5,5,0.000001);
   cout<<"Wariancja: "<<sqrt(d)<<endl;
   
   Double_t e = funkcja->Covariance2XY(-5,5,-5,5,0.000001);
   cout<<"Kowariancja: "<<sqrt(e)<<endl;

}
