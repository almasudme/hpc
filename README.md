# hpc
High Performance Computing or parallel computing examples

Plan is to articulate follwoing topics. 
1. How to install,compile and run mpi programs
2. implement mpi to integrate a function using trapezeum rule
3. improve algorithm to solve linear system of equation using Gallerkin Method
4. some enhanced feature of MPI

## Download and install Intel MPI

Please check the hardware, software and other development tools requirement for your need on intel's webpage.

For my system which has 16 GB RAM, and a 2.1GHz quad core Intel Core i-5. Install the following tools. form the corresponding website.
1. [Microsoft Visual Studio](https://visualstudio.microsoft.com/downloads/)2019 (Community Edition) . 
    We will only select Desktop development with C++ set of tools in our installation.
2. Intel OneAPI Base toolkit
3. Intel OneAPI HPC Toolkit 

We need to install both base and hpc toolkit from intel oneapi website . One has to have or create an account  be able to download . Selet appropriate OS, installer type etc. on the webpage. The appropriate download button will show up. Just click it.

The HPC toolkit provides a set of compiler and libraries.  DPC++/C++ compilers and the intel MPI Libraries are required for this tutorial others are optional. 

After download is complete the installations are straightforward. Just keep clicking next or appropriate options provided on the prompt.You can choose installation path on your system while installing. A default installation path could be in - "C:\Program Files (x86)\Intel\oneAPI". To be able to compile and run using any intel compilers we need to run follwoing command on our command prompt.
       
         "C:\Program Files (x86)\Intel\oneAPI\setvars.bat" intel64
         
   
This will set all environment variables and paths needed for compiling and running a program with MPI.
## MPI: Compile and Run your first program.
Let us write our first MPI program. Here is mphello.c Hello World program program using MPI.
       
#include &ltmpi.h&gt
#include &ltstdio&gt
/*mphello.c: Hello World program program using MPI.*/

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}
       
 
Note: It will help to go through the explanation of the above code in Dr. Wes Kendall's original website. 

To compile the program:
       
mpicc mphello.c -o mphello
   
This will create a mphello.obj and mphello.exe in your local directory. To run the program:
       
mpiexec mphello         
    
    output:
    Hello world from processor COMPUTER-USER, rank 1 out of 2 processors
    Hello world from processor COMPUTER-USER, rank 0 out of 2 processors
         
   

