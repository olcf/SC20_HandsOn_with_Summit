# GPU Kernel Profiling Using Nsight Compute

NVIDIA provides a couple of useful profiling tools on Summit to profile CUDA
performance. Nsight Systems (TODO: write briefly about Nsight systems) and Nsight
Compute. Typically, you first use Nsight Systems to profile your whole program to identify
any bottlenecks. If you identify that it is the kernels that are the bottleneck, you use
Nsight Compute to profile the kernels in more detail. We will be focusing on Nsight
Compute in this challenge. You can read more about the use of both tools on Summit
[here](https://docs.olcf.ornl.gov/systems/summit_user_guide.html#profiling-gpu-code-with-nvidia-developer-tools).

In this challenge, you will be profiling two different CUDA programs
`matrix_sums_unoptimized.cu` and `matrix_sums_optimized.cu`. Each file has two CUDA
kernels (TODO: do we need to explain what kernels are, or refer to earlier
challenges/material that talk about kernels), that sums the rows of a matrix, and one that
sums the columns of the matrix. The matrix itself is represented as one long array in [row
major order](http://icarus.cs.weber.edu/~dab/cs1410/textbook/7.Arrays/row_major.html). We
will be profiling two different versions of the code. In `matrix_sums_unoptimized.cu`, the
`row_sums` and `column_sums` kernels uses one thread per row (or one thread per column) to
sum the whole row/column. In `matrix_sums_optimized.cu`, the `row_sums` kernel is changed so that
it does a parallel sweep reduction (TODO: maybe add a brief info on parallel sweep
reduction with the diagrams from the cuda training slides) to sum each row, using one
threadblock per row (with 256 threads per block). The `column_sums` kernel remains the
same.

## Step 1: Compile the unoptimized code

First, you'll need to make sure your programming environment is set up correctly for
compiling the code. You need to make sure CUDA, gcc and the profiling tools are present
in the environment.

```
$ module load gcc
$ module load cuda
$ module load nsight-compute
```

Then you compile the `matrix_sums_unoptimized.cu` code with

```
$ make unoptimized
```

This will create a binary called `matrix_sums_unoptimized` in the directory, that is doing the
one thread per row addition.

## Step 2: Run the program

Once you've succesfully compiled, submit the batch script.

```
$ bsub submit_unoptimized.lsf
```

If you look inside the batch script, you will see that the program is being run with
the Nsight Compute profiler `nv-nsight-cu-cli`. This starts the profiler and attaches it
to the program. Check the output file and you will see the basic profiling output in plain
text for the `row_sums` and `column_sums` kernels. Notice the difference in their
duration? The column sum is a lot faster than the row sum. Why is that? What other things
do you notice are different between `row_sums` and `column_sums`. (TODO: do we need to add
an explanation here that it's slower because of uncoalesced memory access?)

## Step 3: Compile the optimized code

There is a way to make the `row_sums` as fast as the `column_sums`, by a method called
parallel sweep reduction (TODO: maybe add a link to the description of parallel sweep or
describe it here). Look at the code in `matrix_sums_optimized.cu` and compare the
`row_sums` kernel to the one in the `matrix_sums_unoptimized.cu` code.

Compile the code in `matrix_sums_optimized.cu` with

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
the duration. You can see that the duration for the `row_sums` is nearly equal to the
`column_sums` kernel. What causes this? (TODO: add an explanation of memory coalescing in
the `rows_sums` and `column_sums`)

## Step 5: Open profiling data in GUI tool

The profiling information on the terminal is limited. NVIDIA also provides a GUI tool that
provides additional data visualizations of your profiling information (TODO: insert
instructions to install Nsight Compute here). In order for you to view the profiling
information with additional graphs, you will need to modify the Makefile and
recompile. Open the Makefile and uncomment the line with `CFLAGS`, then run `make clean && make
unoptimized && make unoptimized`. This will compile the code with the `-lineinfo` flag which will come useful when looking at the profiling data with the Nsight Compute GUI tool.

Open the batch scripts and uncomment the jsrun line that includes the additional flags to
the `nv-nsight-cu-cli` (and comment out the other jsrun line). Submit the batch scripts again.

This time when the jobs are completed, in addition to the output files, you will see files
named `profiling_data_optimized.ncu-rep` and `profiling_data_unoptimized.ncu-rep`. These
are the profiling data files. Copy these files along with the source code to your laptop
with scp (TODO: do we need to add instructions for SCP?). Open Nsight Compute on your
laptop and open the downloaded file with File -> Open File. This will open a report with
multiple sections. Click on the Page dropdown and click on Details for the detailed report
with graphs and charts. You can switch between the `row_sums` and `column_sums` reports
from the Launch dropdown. Does the GUI report provide any additional insights? You can
find more information about the various sections of the profiling report
[here](https://docs.nvidia.com/nsight-compute/NsightCompute/index.html#profiler-report).

In the Source page (navigate to Source in the Page dropdown), if the Source column says
File Not Found, click on the Resolve Button and select the corresponding `.cu` file that
you downloaded.


## Bonus Points

Can you rewrite the `column_sums` kernel in `sums_optimized.cu` to also use parallel sweep
reduction like `row_sums` does? Does that make a difference in that kernel's performance
compared to `row_sums` and compared to the old `column_sums`?



