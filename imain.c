#include<stdio.h>
#include "integral.h"
#include <mpi.h>

int main(void){
  // double c = Trap(0.0,1.0,10000);
  //  printf("%f",c);
  // return 0;

  int my_rank, comm_sz, n=1024,local_n;
  double a = 0.0, b = 1.0 ,h, local_a, local_b;
  double local_int, total_int;
  int source;

  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

  h = (b-a)/n;
  local_n = n/comm_sz;
  printf("%d",local_n);

  local_a = a+my_rank*local_n*h;
  local_b = local_a + local_n*h;
  local_int = Trap(local_a,local_b,local_n);

  if (my_rank != 0){
    MPI_Send(&local_int, 1, MPI_DOUBLE, 0,0,MPI_COMM_WORLD);
    printf("%d\t",my_rank);
  } else {
    total_int = local_int;
    for (source =1;source < comm_sz; source++){
      MPI_Recv(&local_int,1,MPI_DOUBLE,source,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      total_int += local_int;
    }
  }

  if (my_rank == 0){
    printf("With n = %d trapezoids, our estimate\n",n);
    printf("of the integral form %f to %f = %.15e\n",a,b,total_int);
  }
  MPI_Finalize();
  return 0;
 } 