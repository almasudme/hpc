#include "integral.h"


double Trap(double left ,double right,int trap_count  ) {
  double estimate, x;
  int i;
  double base_len = (right -left)/trap_count;
  estimate = (func(left) + func(right))/2.0;
  for (i=1;i<=trap_count;i++) {
      x = left + i*base_len;
      estimate += func(x);
  }
  estimate = estimate*base_len;
  return estimate;
 }


