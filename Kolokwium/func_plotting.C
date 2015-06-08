#include <TF1.h>
#include <math.h>

#define M_PI 3.14159265358979312

void func_plotting(){
  TF1* f1 = new TF1("f2","[0]*sin(x)/x",-5*M_PI,5*M_PI);
  f1->SetParameter(0,1);
  f1->SetParameter(1,1);
  f1->Draw();
}