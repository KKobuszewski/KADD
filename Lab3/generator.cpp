#include <iostream>
#include <fstream>
#include <stdint.h>
#include <math.h>

int main(){
  uint64_t x = 1;//Seed
  uint64_t a = 427619669081;
  uint64_t c = 0;
  uint64_t m = pow(10,12)-11;
  uint64_t n = 100000;
  
    std::fstream plik;
    plik.open( "MAPLE.txt", std::ios::in | std::ios::out );
    if( plik.good() == true )
    {	
      for (int ii = 0; ii < n+1; ii++){
	  x = (a*x + c)%m;
	  long double double_x = (long double) x;
	  plik<<(double_x/m)<<std::endl;
      }
      plik.close();
    }
    return( 0 );
}