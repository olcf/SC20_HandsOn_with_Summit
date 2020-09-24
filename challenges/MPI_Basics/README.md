# What is MPI? 

The **M**essage **P**assing **I**nterface (MIP) is a set of library functions, methods, and specifications that can be called to distribute a code's processing work between nodes or processors on the same node.  It does this by passing messages between the processors. It is governed by a set of community driven standards and there are several implementations of MPI. 

MPI can be used in conjunction with threading and accelerators. For example, you might use MPI pass work between compute nodes and then use threads or accelerators to divide work among the different processing elements on the node. 

This challenge will explore an MPI hello-world and two kinds of MPI communication patterns. We will use C code and pass its work with MPI between CPU cores on the same node. 

A good refence for learning more about MPI is [MPI: A Message-Passing Interface Standard Version 3.1]( https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). 

# MPI Terminology  
 
**Communicator**   An object that represents a group of processes than can communicate with each other. 

When a program uses MPI, all the processes are grouped in a communicator. You can picture a communicator as an envelope that groups process together and allows them to communicate. The first thing MPI does when it is initialized , is set up the communicator. 


**Rank** Within a communicator each process is given a unique integer ID. Ranks start at 0 and are incremented contiguously.

**Size** The total number of ranks in a communicator.

# MPI Functions and Hello-world

MPI consists of hundreds of functions but most users will only use a handful of them. 
We'll start by looking at the functions needed for an MPI Hello-world program. 

Below is an outline for the program that discuses it functions. For this challenge, you will review this outline and then enter the needed functions in your own copy of mpi-hello.c 


**Hello-world Outline**

* First initialize  MPI. 
  
  This is done with a function:

  ```
  MPI_Init(&argc, &argv);
  ```
  When the MPI_Init function is called, all of MPI’s global and internal variables are constructed.    A communicator is setup to contain all of the processes that were spawned, and unique ranks are assigned to each process. The arguments  argc and argv are empty in this case. Do not focus on them for now. 

* Next get the number (size) of processes from the communicator. 
  
  This is done with another MPI function: 
  
  ```
  MPI_Comm_size(MPI_COMM_WORLD, &size); 
  ```
  In this case, the communicator is named MPI_COMM_WORLD. This function returns the size of the communicator which us equal to the number of ranks. 
 
* Next get the rank number of each process from the communicator. 
  
  This is also done with an MPI function: 
  ```
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  ```
  Ranks are IDs used for sending and receiving messages for each process. 

* Print "Hello" from each rank distributed on each processor. This is just C code. 


* Finalize MPI. 
  Yet another MPI function. 
  ```
  MPI_Finalize();
  ```
  This function cleans up MPI and release the communicator. No MPI functions will be recognized below this function. 



Use the outline to help you enter the four needed MPI functions after each comment in the mpi-hello.c program from the repository. 

To do this, make sure you are in the SC20_HandsOn_with_Summit/challenges/MPI_basics folder and then open this open mpi_hello.c with your favorite editor.  

The file will look like this: 

```
#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size;
    // Initialize MPI (Put the MPI initialization functions here)
    
    
    //Get the number of ranks (size) from the Communicator (Put the MPI size function here) 
 
  
   
   //Get the rank for each process from the communicator. (Put the MPI rank function here)
  

    printf("Hello from rank %d of %d total \n", rank, size);
    
    
    //Clean up and finalize the MPI environment (Put the MPI finalization function here) 

    return 0;
}
```

To compile mpi-hello.c 

```
make

````

To run the code 

```
bsub submit.lsf 

```

If you had an error go back and check your code. Then recompile it and try again. 
If it succeeded you should recive a greetting from each of the 42 cpu codes on the node. When you open the output file. 


Communications can be either of two forms: 
* Point-to-Point : Two processes in the same communicator are going to communicate.
* Collective : All the processes in a communicator are going to communicate together.
