#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TAxis.h>
#include <TFrame.h>

#define M_PI 3.14159265358979323846

void generate_data(Double_t* x, Double_t* y, const Int_t n, void (*function) (Double_t*, Double_t*, Int_t));
void Sin(Double_t*, Double_t*, Int_t);
void Cos(Double_t*, Double_t*, Int_t);

void pointers_to_func() {
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);
   
   c1->SetFillColor(42);
   c1->SetGrid();
   
   const Int_t n = 100;
   Double_t* x1 = new Double_t[n];
   Double_t* y1 = new Double_t[n];
   //Double_t* x2 = new Double_t[n];
   //Double_t* y2 = new Double_t[n];
   
   generate_data(x1,y1,n,Cos);
   //generate_data(x2,y2,n,Cos);
   
   TGraph *gr = new TGraph(n,x1,y1);
   //TAxis *Xaxis = gr->GetXaxis();
   
   //Xaxis->setLimits(0.,3.15);
   
   gr->SetLineColor(2);
   gr->SetLineWidth(5);
   gr->SetMarkerColor(kGreen);
   gr->SetMarkerStyle(kCircle);
   gr->SetTitle("a simple graph");
   gr->GetXaxis()->SetTitle("X title");
   gr->GetYaxis()->SetTitle("Y title");
   gr->GetXaxis()->SetLimits(0.,2*M_PI);
   gr->Draw("ACP");
   //A - TWORZY OBIEKT ZEBY NARYSOWAC
   // L - linea C - continous
   // P - points
   
   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(20);
   c1->Modified();
}


void generate_data(Double_t* x, Double_t* y, const Int_t n, void (*function) (Double_t*, Double_t*, Int_t))
{
   //Function wrapper
   function(x,y,n);
}

void Sin(Double_t* x, Double_t* y, const Int_t n){
   printf("*** Function sin ***\n");
   for (Int_t i=0;i<n;i++) {
     x[i] = i*2*M_PI/(n-1);
     y[i] = 10*sin(x[i]);
     printf(" i %i %f %f \n",i,x[i],y[i]);
   }
}

void Cos(Double_t* x, Double_t* y, const Int_t n){
   printf("*** Function cos ***\n");
   for (Int_t i=0;i<n;i++) {
     x[i] = i*2*M_PI/(n-1);
     y[i] = 10*cos(x[i]);
     printf(" i %i %f %f \n",i,x[i],y[i]);
   }   
}