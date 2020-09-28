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

# MPI Functions and Hello_World

MPI consists of hundreds of functions but most users will only use a handful of them. 
We'll start by looking at the functions needed for an MPI Hello-world program. 

Below is an outline for the program that discuses its functions. For this challenge, you will review this outline and then try to use it to find the missing MPI function in your copy of mpi_hello.c 


**Hello_world Outline**

* First initialize  MPI. 
  
  This is done with a function:

  ```
  MPI_Init(&argc, &argv);
  ```
  When the MPI_Init function is called, all of MPI’s global and internal variables are constructed.  A communicator is setup to contain all of the processes that were spawned, and unique ranks are assigned to each process. The arguments argc and argv are empty in this case. Do not focus on them for now. 

* Next get the number (size) of processes from the communicator. 
  
  This is done with another MPI function: 
  
  ```
  MPI_Comm_size(MPI_COMM_WORLD, &size); 
  ```
  In this case, the communicator is named MPI_COMM_WORLD. This function returns the size of the communicator which us equal to the number of ranks. 
 
* Next get the rank ID of each process from the communicator. 
  
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
  This function cleans up MPI and releases the communicator. No MPI functions will be recognized below this function. 



Use the outline to help find and enter the missing MPI function in mpi-hello.c. To do this, make sure you are in the SC20_HandsOn_with_Summit/challenges/MPI_basics folder and then open mpi_hello.c with your favorite editor.  

The file will look like this: 

```bash
#include "stdio.h"
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size;

    // Initialize MPI

     MPI_Init(&argc, &argv);

    //Get the number of ranks (size) from the Communicator  

     MPI_Comm_size(MPI_COMM_WORLD, &size);


    //Print hello from each rank 

     printf("Hello from rank %d of %d total \n", rank, size);

    //Clean up and finalize the MPI environment

     MPI_Finalize();
    return 0;
}

```

Once you think you have updated the file to include the missing function, compile the code. 

To compile mpi_hello.c 

```
make
````

To run the code 

```
bsub submit_hello.lsf 
```

If it succeeded, you should see the following output in the mpi_hello. output file: 

```
Hello from rank 3 of 4 total
Hello from rank 1 of 4 total
Hello from rank 0 of 4 total

```
If you had an error go back and check your code. Then recompile it and try again. 



# Point to Point MPI Communication 

We’ll dive a little deeper into understanding MPI functions as we explore Point to Point communication. 

Point to Point routines involve two and only two processes. One process explicitly initiates send operation and one process explicitly initiates receive operation.
For example Process 0 sends the message "Hello!" to process 1. 

Below is the MPI_Send function. It is used to send a message to a process. 

```
int MPI_Send(void *buf, int count,
             MPI_Datatype MPI_Datatype datatype, int dest,
             int tag, MPI_Comm comm)

```
In this function: 
* buf -Initial integer address of send buffer. The message you want to send will be packed-up into this buffer. 

* count- Number of elements to send. For example, if you are going to send a message that is 6 charaters long, it will have a count of 6 elements. 

* datatype - This is the MPI datatype of each element in the send buffer. There are built-in data types for all intrinsic C types
MPI_INT, MPI_FLOAT, MPI_DOUBLE, MPI_CHAR … . If you wanted to send "Hello!" from procsess 0 to process 1, you would used a datatype of MPI_CHAR. 


* Dest- Rank of destination. This is the ID of where the message will go. 

* Tag -Integer tag used by receiver to identify message. 

* Comm- Communicator 



Here is the MPI Recieve function. 

```
int MPI_Recv(void *buf, int count,
             MPI_Datatype datatype, int source,
             int tag, MPI_Comm comm, MPI_Status status
```

In this case the functions arguments mean: 

* buf- Initial address of receive buffer
* count Maximum number of elements that can be received
* datatype - MPI_Datatype of each element in receive buffer
* source- Rank of source
* tag Integer tag used to identify message
* comm- Communicator
* status- Struct containing information on received message 




Several send/receive flavors available:
* Blocking/non-blocking
* Buffered/non-buffered
* Combined send-receive

# MPI Communication Patterns
MPI Communications can be either of two forms: 
* Point-to-Point : Two processes in the same communicator are going to communicate.
* Collective : All the processes in a communicator are going to communicate together.
