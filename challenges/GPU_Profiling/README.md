# GPU Kernel Profiling Using Nsight Compute

NVIDIA provides a couple of useful profiling tools on Summit to profile CUDA
performance. Nsight Systems (TODO: write briefly about Nsight systems) and Nsight
Compute. We will be focusing on Nsight Compute in this challenge. You can read more about
both tools here (TODO: add link to more info).

In this challenge, we will be profiling two different CUDA programs `sums_unoptimized.cu`
and `sums_optimized.cu`. Each file has two CUDA kernels (TODO: do we need to explain what
kernels are, or refer to earlier challenges/material that talk about kernels), one that
sums the rows of a matrix, and one that sums the columns of the matrix. The matrix itself
is represented as one long array. We will be profiling two different versions of the
code. In `sums_unoptimized.cu`, the `row_sum` and `column_sum` kernels uses one thread per
row (or one thread per column) to sum the whole row/column. In `sums_optimized.cu`, the
`row_sum` kernel is changed so that it does a parallel sweep reduction of the whole
row. The `column_sum` kernel remains the same.

## Step 1: Compile the unoptimized code

First, you'll need to make sure your programming environment is set up correctly for this
program. You only need to make sure CUDA and gcc and the profiling tools are present in
the environment.

```
$ module load gcc
$ module load cuda
$ module load nsight-compute
```

Then we compile the `sums_unoptimized.cu` code with (TODO: add makefile)

```
$ make unoptimized
```

This will create a binary called `sums_unoptimized` in the directory, that is doing the
one thread per row addition.

## Step 2: Run the program

Once you've succesfully compiled, try running it.

```
$ bsub submit_unoptimized.lsf
```

If you look inside the submit.lsf file, you will see that the program is being run with
the Nsight Compute profiler `nv-nsight-cu-cli`. This starts the profiler and attaches it
to the program. Check the output file and you will see the basic profiling output for the
row sum and column kernels. Notice the difference in their duration? The column sum is a
lot faster than the row sum. Why is that?

## Step 3: Compile the optimized code

There is a way to make the row sum as fast as the column sum, by a method called parallel
sweep reduction (TODO: maybe add a link to the description of parallel sweep or describe
it here). Look at the code in `sums_optimized.cu`, specifically at the `row_sum` kernel
and compare it to the `row_sum` in the `sums_unoptimized.cu` code. 

Compile the code in `sums_optimized.cu`

```
make optimized
```

This will create a binary called `sums_optimized` in the directory, that is doing parallel
sweep reduction of the sum addition.

## Step 4: Profile the optimized code

Once you've successfully compiled, run the batch script:

```
$ bsub submit_optimized.lsf
```

This also runs the Nsight Compute profiler, same as before. Open the output file and check
the duration. How is it different from the unoptimized code? How are other properties
differing between the two codes?

## Step 5: Open profiling data in GUI tool

The profiling information on the terminal is limited. NVIDIA also provides a GUI tool that
provides additional data visualizations of your profiling information (TODO: insert
instructions to install Nsight Compute here). In order for you to view the profiling
information with additional graphs, you will need to modify the batch scripts. 

Open the batch script and change the jsrun line to include additional flags to the
`nv-nsight-cu-cli`

```
TODO: show example with the flags to be added
```

This will generate some (TODO: what do the profiling data file names look like)
files. Copy them to your laptop with scp (TODO: do we need to add instructions for
SCP?). Open Nsight Compute on your laptop and open the downloaded file. This 

(TODO: does the GUI provide any additional insights or just any additional things that we
can point to on this code?)


(TODO: add instructions on how to change the makefile to add the -lineinfo (?) flag to
associate SASS with the source for line by line breakdown of where things may be
bottlenecking in the kernel source)


## Bonus Points

Can you rewrite the `column_sum` in `sums_optimized.cu` to also use parallel sweep
reduction? Does that make a difference in that kernel's performance compared to `row_sum`
and compared to the old `column_sum`?



