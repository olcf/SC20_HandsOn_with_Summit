# What is MPI? 

The **M**essage **P**assing **I**nterface (MIP) is a set of library functions, methods, and specifications that can be called to distribute a code's processing work between nodes or processors on the same node.  It does this by passing messages between the processors. It is governed by a set of community driven standards and there are several implementations of MPI. 

MPI can be used in conjunction with threading and accelerators. For example, you might use MPI pass work between compute nodes and then use threads or accelerators to divide work among the different processing elements on the node. 

This challenge will explore an MPI hello-world and two kinds of MPI communication patterns. We will use C code and pass its work with MPI between CPU cores on the same node. 

A good refence for learning more about MPI is [MPI: A Message-Passing Interface Standard Version 3.1]( https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report.pdf). 

# MPI Terminology  
 
**Communicator**   An object that represents a group of processes than can communicate with each other. 

**Rank** Within a communicator each process is given a unique integer ID. Ranks start at 0 and are incremented contiguously. Ranks can be mapped to hardware processing elements like CPU cores. 

**Size** The total number of ranks in a communicator.

**MPI Region** The part of the code that will be executed in parallel using one MPI communicator. It will always be sandwiched between  MPI_Init and MPI_Finalize function calls. 

<br>
<center>
<img src="images/MPI_burger.png" width=100" heigth="100">
</center>
<br>
The first thing MPI does when it is initialized, is set up the communicator. You can think of a communicator as a package that holds all the needed organizational information for its MPI region in the code. Inside the communicator each process is given a rank. The size of the communicator is equal to its total number of ranks. All MPI function calls within the same MPI region will get each process’s rank from the communicator.




<br>
<center>
<img src="images/comm.png" style="width:40%">
</center>
<br>


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

    /*----------------*/
    /* Initialize MPI */
    /*----------------*/

     MPI_Init(&argc, &argv);

    /*------------------------------------------------------*/
    /* Get the number of ranks (size) from the Communicator */

    /*------------------------------------------------------*/

     MPI_Comm_size(MPI_COMM_WORLD, &size);


    /*------------------------------------------------------*/
    /* Get the Rank ID for each process                     */
    /* Fix the code here.                                   */
    /*------------------------------------------------------*/




    /*------------------------------------------------------*/
    /* Print hello from each rank                           */
    /*------------------------------------------------------*/

     printf("Hello from rank %d of %d total \n", rank, size);

    /*------------------------------------------------------*/
    /* Clean up and finalize the MPI environment            */
    /*------------------------------------------------------*/

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

Point to Point communication is one way you can finely control how you divide work between processors. Point to Point routines involve two and only two processes. One process explicitly initiates a send operation and one process explicitly initiates a receive operation.



In the code that you will work with for this part of the challenge, Process 0 will send a message "Hello!" to process 1. 
The two new MPI functions we will use to accomplish this will be MPI_Send and MPI_Recv. We will also need the MPI_Comm_rank function that you just learned about to get the ranks of the processes from the communicator. 

Below is the MPI_Send function. It is used to send a message to a process. 

```
int MPI_Send(void *buf, int count,
             MPI_Datatype MPI_Datatype datatype, int dest,
             int tag, MPI_Comm comm)

```
In this function: 
* buf -Initial integer address of send buffer. The message you want to send will be packed-up into this buffer. 

* count- Number of elements to send. For example, if you are going to send a message that is 6 characters long, it will have a count of 6 elements. 

* datatype - This is the MPI datatype of each element in the send buffer. There are built-in data types for all intrinsic C types
MPI_INT, MPI_FLOAT, MPI_DOUBLE, MPI_CHAR … . If you wanted to send "hello!" from process 0 to process 1, you would used a datatype of MPI_CHAR. 


* Dest- Rank of destination. This is the ID of where the message will go. 

* Tag -Integer tag used by receiver to identify message. 

* Comm- Communicator 

This functions retruns after send buffer is ready to reuse. 

Here is the MPI Receive function. 

```
int MPI_Recv(void *buf, int count,
             MPI_Datatype datatype, int source,
             int tag, MPI_Comm comm, MPI_Status status
```

In this case the function's arguments mean: 

* buf- Initial address of receive buffer
* count Maximum number of elements that can be received
* datatype - MPI_Datatype of each element in receive buffer
* source- Rank of source
* tag Integer tag used to identify message
* comm- Communicator
* status- Struct containing information on received message 

This functions retruns after receive buffer is ready to reuse. 


Here is the code ptp.c, where process 0 will send the message "hello!" to process 1. However, the receive function has three missing arguments labeled A, B. and C. 
Your challenge is to use the arguments in the send function and the function definitions above to fill in the missing arguments. 

Some of the questions to help you:
Why does the MPI_Send function say that the message has 6 elements?
Why datatype is "hello!" ? 
Where is the message going? 

```
#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
  int rank, ntag = 100;
  char message[14];
  MPI_Status status;

  /*----------------*/
  /* Initialize MPI */
  /*----------------*/

  MPI_Init(&argc, &argv);

  /*------------------------------------------------------*/
  /* Get my rank in the MPI_COMM_WORLD communicator group */
  /*------------------------------------------------------*/

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  /*---------------------------------------*/
  /* Process 0 sends a message to process 1*/
  /*---------------------------------------*/

  if (rank == 0) {
    strcpy(message, "hello!");
    MPI_Send(&message, 6, MPI_CHAR, 1, ntag, MPI_COMM_WORLD);
  }

  /*----------------------------------------------*/
  /* Process 1 receives a message from process 0  */
  /* and outputs the result                       */
  /* Use the send function and the definition     */
  /* of MPI_Recv to fill in A,B and C below       */
  /*----------------------------------------------*/
  
  if (rank == 1 ) {
    MPI_Recv(&message, A?, B?, C?, ntag, MPI_COMM_WORLD, &status);
    printf("Process %d : %s\n", rank, message);
  }

  /*--------------*/
  /* Finalize MPI */
  /*--------------*/

  MPI_Finalize();

}
```

To conquer the challenge: 
1. Determine the missing arguments. 

2. Go to SC20_HandsOn_with_Summit/challenges/MPI_basics/ptp/. 
```
cd SC20_HandsOn_with_Summit/challenges/MPI_basics/ptp/

````
3. Edit the Receive function in ptp.c with your A, B and C arguments. 



4.Complle ptp.c 

```
Make

```

5. Submit the job. 

```
submit_ptp.lsf

```

If your code ran correctly, you will see:

```
Process 1 : hello!
```


 If you want to know more about point to point communication, including how to aviod dead-locking your processes, see: [https://www.sciencedirect.com/topics/computer-science/point-to-point-communication](https://www.sciencedirect.com/topics/computer-science/point-to-point-communication) 


# MPI Collectives 

The last type of MPI communication we will introduce is Collective Communication, which involves all the processes in a communicator.
In fact, all processes in communicator must participate. 
Collective Communication serves several purposes:
* Synchronization
* Data movement
* Reductions

Several routines originate or terminate at a single process known as the “root”.

For this introduction we'll look at the broadcast, where the root process sends data to all the other processes. One of the main uses of broadcasting is to send configuration parameters, like initial conditions, to all processes in a parallel program. 

Here is the broadcast function:

```
int MPI_Bcast(void *buf, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
```
The function arguments are: 
* buf - Initial address of send buffer
* count - Number of elements to send
* datatype - Datatype of each element in send buffer
* root - Rank of node that will broadcast buf 
* comm - Communicator


```bash
#include “stdio.h”
#include “mpi.h”

int main(int argc, char **argv)
{
    int rank, root, bcast_data;
    root = 0;
    if(rank == root)
           bcast_data = 10; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Bcast(&bcast_data, 1, MPI_INT, root, MPI_COMM_WORLD);
    
    printf("Rank %d has bcast_data = %d\n", rank, bcast_data);
  
    MPI_Finalize();
    return 0;
}
```





