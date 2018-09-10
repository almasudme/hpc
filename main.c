#include<stdio.h>
#include "integral.h"


int main(){
  double c = Trap(0.0,1.0,10000);
   printf("%f",c);
  return 0;
 } 