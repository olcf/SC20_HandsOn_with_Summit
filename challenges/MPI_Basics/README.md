# What is MPI? 

The **M**essage **P**assing **I**nterface (MIP) is a set of library functions, methods, and specifications that can be called to distribute a code's procssing work between nodes or processors on the same node.  It does this by passing messages between the processors. It is governed by a set of community driven standards and there are several implementations of MPI. 

MPI can be used in conjunction with threading and accelerators. For example you might use MPI pass work between compute nodes and then use threads or accelerators to divide work among the different processing elements on the node. 

This challenge will explore an MPI hello-world and two kinds of MPI communication patterns, collective and point to point communication. We will use C code, and pass its work with MPI between CPU cores on the same node. 

A good refence for learning more about MPI is [MPI: A Message-Passing Interface Standard Version 3.1]( https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). 

# MPI Terminology  
 
**Communicator**  An object that represents a group of processes than can communicate with each other. 
When a program uses MPI, all the processes are grouped in a communicator. You can picture a communicator as an envelope that groups process together, and allows them to communicate. Every communication is linked to a communicator, that allows the  communication to reach different processes. The first thing MPI does when it is initized, is set up the communicator so that all the other MPI function used will be able to refrence the variables needed to direct the communication from the communicator. 
Ref https://www.codingame.com/playgrounds/349/introduction-to-mpi/mpi_comm_world-size-and-ranks


**Rank** Within a communicator each process is given a unique integer ID, Ranks start at 0 and are incremented contiguously

**Size** The total number of ranks in a communicator

# MPI Functions 

MPI consists of hundreds of functions but most users will only use a handful of them. 
We'll start by looking at the fuctions needed for an MPI Hello world program.

All functions are prefixed with MPI_ .
All C functions return integer error MPI_SUCCESS if no error. 

We will start with the basic outline of an MPI_hello world and then have you fill in the needed MPI fucntions 

**Hello-world Outline**
First Initize MPI. In this step all of MPI’s global and internal variables are set up and contained in a communicator. All MPI regions start with this function.  

It looks like this for C code:
```
MPI_Init(&argc, &argv);
```
argc and argv are empty arguments in this case.

Next  Get the nubmer (size) of processes from the communicator. In this case, the communicator is named MPI_COMM_WORLD.

```
MPI_Comm_size(MPI_COMM_WORLD, &size); 
```

Get the rank nubmer of each process from  communicator 
```


Do some work. In this case the work will be pritning "Hello" from the ranks distributed on each processor. 


Finalize MPI. This function cleans up MPI and release the communicator. No MPI fucntions will be recognized below this function. 

```
 MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 ```

Now it is your turn to turn this outline into a program that will Iniaize MPI, get the rank for each process from the MPI_COMM_WORLD commnicator, and then say "hello" from the ranks that have been distributed on each processor. 

To do this Open mpi_hello.c and enter the needed funtions after each comment in the program. The file will look like this: 

```
#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size;
    // Initialize MPI
    
    //Get the number of ranks from the Communicator which in this case is called MPI_COMM_WORLD
 
   //Get the rank for each process from the communicator. 
  

    printf("Hello from rank %d of %d total \n", rank, size);
    
    
    //Clean up and finalize the MPI environment 

    return 0;
}
```





Communications can be either of two forms: 
* Point-to-Point : Two processes in the same communicator are going to communicate.
* Collective : All the processes in a communicator are going to communicate together.









