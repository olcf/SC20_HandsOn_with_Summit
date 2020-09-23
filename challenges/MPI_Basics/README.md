# What is MPI? 

The **M**essage **P**assing **I**nterface (MIP) is a set of library functions, methods and specifications  that you can call to help you distribute workbetween nodes or processors on the same node.  It does this by passing messages between the processors that contain the work and data that your codes process. It is governed by a set of community driven standards and there are several implementation of it. 

It can be used in conjunction with threading see tutorial ____ and accelerators .For example you might use MPI pass work between compute nodes and then use threads or accelerators to divide work among the different processing elements on the node. 

In this challenge we will explore an MPI helloworld and two kinds of communication patterns , Collective and Point to Point Communication, that you can use with MPI and  C code

Since we have 16 nodes on Ascent we will use MPI to pass work between CPU cores on the same node. 

A good refence  for learming all the details is [MPI: A Message-Passing Interface Standard Version 3.1]( https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). 


# MPI Functions 

MPI consists of hundreds of functions but most users will only use a handful of them. 
All functions prefixed with MPI_ .
All  C functions return integer error MPI_SUCCESS if no error. 

we need a little terminology before we can jump in. 
 
**Communicator**  An object that represents a group of processes than can communicate with each other. 
When a program uses MPI, all the processes are grouped in a communicator. You can picture a communicator as an envelope that groups process together, and allows them to communicate. Every communication is linked to a communicator, that allows the  communication to reach different processes. 
Ref https://www.codingame.com/playgrounds/349/introduction-to-mpi/mpi_comm_world-size-and-ranks

Communications can be either of two forms: 
* Point-to-Point : Two processes in the same communicator are going to communicate.
* Collective : All the processes in a communicator are going to communicate together.

**Rank** Within a communicator each process is given a unique integer ID, Ranks start at 0 and are incremented contiguously

**Size** The total number of ranks in a communicator




