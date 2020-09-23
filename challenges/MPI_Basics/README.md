# What is MPI? 

The **M**essage **P**assing **I**nterface (MIP) is a set of library functions, methods, and specifications that can be called call distribute a code's procssing work between nodes or processors on the same node.  It does this by passing messages between the processors. It is governed by a set of community driven standards and there are several implementations of MPI. 

MPI can be used in conjunction with threading and accelerators. For example you might use MPI pass work between compute nodes and then use threads or accelerators to divide work among the different processing elements on the node. 

This challenge will explore an MPI hello-world and two kinds of MPI communication patterns, collective and point to point communication. We will use C code, and pass its work with MPI between CPU cores on the same node. 

A good refence for learning more about MPI is [MPI: A Message-Passing Interface Standard Version 3.1]( https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). 

# MPI Terminology  
 
**Communicator**  An object that represents a group of processes than can communicate with each other. 
When a program uses MPI, all the processes are grouped in a communicator. You can picture a communicator as an envelope that groups process together, and allows them to communicate. Every communication is linked to a communicator, that allows the  communication to reach different processes. 
Ref https://www.codingame.com/playgrounds/349/introduction-to-mpi/mpi_comm_world-size-and-ranks

Communications can be either of two forms: 
* Point-to-Point : Two processes in the same communicator are going to communicate.
* Collective : All the processes in a communicator are going to communicate together.

**Rank** Within a communicator each process is given a unique integer ID, Ranks start at 0 and are incremented contiguously

**Size** The total number of ranks in a communicator

# MPI Functions 

MPI consists of hundreds of functions but most users will only use a handful of them. 
All functions are prefixed with MPI_ .
All C functions return integer error MPI_SUCCESS if no error. 

There are two functions that sanwich all MPI calls. 

The top bun of the MPI sandwich, MPI_Init, initializes the MPI environemnt 
```
int MPI_Init( int *argc, char ***argv )
```
argc is a pointer to the number of arguments
argv is a pointer to the argument vector

The MPI_Init function must be called before any other MPI calls. 

The bottom bun of the MPI sandwich, MPI_Finalize cleans up the MPI enviromnt. 
```
int MPI_Finalize( void )
```
Any MPI functions called after MPI_Finalize will not be recognized. 












