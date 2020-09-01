# Job Step Viewer and Summit Tour

When running programs on a workstation, most of the time you can simply execute `./a.out` and wait for the results. On most HPC clusters, you must use a "batch scheduler" to request one or more compute nodes to run on and a "job launcher" to execute your program on the compute node(s) you were allocated. You submit jobs on Summit with IBM's [`jsrun` job launcher](../jsrun_Job_Launcher).

The [Job Step Viewer](https://jobstepviewer.olcf.ornl.gov/) provides a graphical view of an application's runtime layout on Summit. It allows users to preview and quickly iterate with multiple jsrun options to understand and optimize job launch. It is a convenient tool that allows you to visualize and verify you are configuring your `jsrun` options in the way you expect.

We recommend attempting this Challenge in conjunction with the [`jsrun` Job Launcher](../jsrun_Job_Launcher) challenge. You should go through the first example or two to get an understanding of how the `jsrun` command works, then re-run the examples, integrating the Job Step Viewer into your submission script. Then you can continue to use the Viewer as you go through the remaining examples and visualize your submissions as you go.

## Job Step Viewer Usage

First, request an allocation of nodes on Summit:

```c
$ bsub -P TRN001 -W 10 -nnodes 1 -J testing_job_step_viewer -U StudentsSC19 -Is $SHELL
```

Once your node is allocated, load the `job-step-viewer` module:

```c
$ module load job-step-viewer
```

Run a `jsrun` command by itself, or with an executable, such as the `Hello_jsrun` from the [`jsrun` Challenge](../jsrun_Job_Launcher):

```c
$ export OMP_NUM_THREADS=2
$ jsrun -n6 -c7 -g1 -a1
```

A URL will be printed after a few seconds. Copy this URL to your browser and load it.

<br>
<center>
<img src="images/jsviewer_1.png" style="width:80%">
</center>
<br>

## Summit Tour

This initial view shows a top-down view of the physical Summit layout in the machine room and your allocated node(s) highlighted in green and/or red. Each cabinet of the machine is laid out and labeled on a Row [a-h], Cabinet [01-36,50] coordinate system. Each node has a hostname that contains this cooridinate plus the node number (there are 18 nodes per cabinet). 

Rather than imagine what this looks like in real life, OLCF has created a [3D virtual tour](https://my.matterport.com/show/?m=iBfbj7ET4LT) of the Summit machine room, for you to see for yourself.

For example, if you are allocated the node `h24n09`, the hostname indicates your node is in Row H, Cabinet 24 and is the 9th node from the bottom. This cabinet is physically 24 cabinets down from the [start of row G](https://my.matterport.com/show/?m=iBfbj7ET4LT&sr=-.4,-1.13&ss=110). That link should take you directly to the start of Row G and H. Row G starts at Cabinet 1 and Row H starts at 9, and so number 24 is 16 cabinets down from the start (as you can see, the entryway phsyically precludes row H from starting all the way to the left). Navigate down the aisle between G and H and find [cabinet 24](https://my.matterport.com/show/?m=iBfbj7ET4LT&sr=3.07,.2&ss=183). You can't see the nodes with the cabinet door closed here, but you can find a [representative cabinet](https://my.matterport.com/show/?m=iBfbj7ET4LT&sr=-.31,.18&ss=82) with the back door open and the [insides of a node](https://my.matterport.com/show/?m=iBfbj7ET4LT&sr=-2.53,.12&ss=11).

The sideways 'H' shaped gap in the middle of the Job Step Viewer layout are cabinets containing system infrastructure such as [interconnect gear](https://my.matterport.com/show/?m=iBfbj7ET4LT&sr=-.51,.9&ss=86), rather than compute nodes. Spend a few moments exploring the rest of the OLCF facility, finding and learning about other points of interest such as the File System, Operations Control Room, and Energy Plant, or to find the node you were allocated in the above example.

### Node Layout

Nodes in your allocation will be highlighted in either green or red. Green nodes indicate the node is being used by the `jsrun` launch. Nodes highlighted in red are allocated to your job, but not being used by this invocation of `jsrun`. For example, if you _allocate_ two nodes with `bsub` but only _launch_ your job on one core or GPU with `jsrun`, one of the allocated nodes will be sitting idle and will show as red on the top-down view. This is a valuable tool to use while you are setting up jobs on Summit to verify you are launching them as you intend.

Clicking on one of the nodes in your allocation will bring up a diagram that should look familiar if you have gone through a couple of the [`jsrun` Challenge](../jsrun_Job_Launcher) examples. We recommend going through that Challenge to understand the layout of your launched job across the nodes and how to interpet this view, if you haven't already done so.

<br>
<center>
<img src="images/jsviewer_2.png" style="width:80%">
</center>
<br>

## Continuing the challenge

Using the Job Step Viewer is a great way to visualize the [`jsrun` Challenge](../jsrun_Job_Launcher) challenge examples. Given the example above, how can you integrate the viewer into these `jsrun` examples? The URL is printed to standard out, and if you provide an executable, it will then be ran as normal. The URL that is printed out will be available for a period of time after the job completes, so you do not necessarily need to view it in real time as the job is running.
