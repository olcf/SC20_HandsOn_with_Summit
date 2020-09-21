# GPU Kernel Profiling Using Nsight Compute

NVIDIA provides a couple of useful profiling tools on Summit to profile CUDA
performance. Nsight Systems and Nsight
Compute. Typically, you first use Nsight Systems to profile your whole program to identify
any bottlenecks. You use Nsight Compute to profile the kernels in more detail. We will be
focusing on Nsight Systems in this challenge to time the CUDA kernels. You can read more
about the use of both tools on Summit
[here](https://docs.olcf.ornl.gov/systems/summit_user_guide.html#profiling-gpu-code-with-nvidia-developer-tools).

In this challenge, you will be profiling two different CUDA programs
`matrix_sums_unoptimized.cu` and `matrix_sums_optimized.cu`. Each file has two CUDA
kernels, one that sums the rows of a matrix, and one that
sums the columns of the matrix. The matrix itself is represented as one long array in [row
major order](http://icarus.cs.weber.edu/~dab/cs1410/textbook/7.Arrays/row_major.html). We
will be profiling two different versions of the code. In `matrix_sums_unoptimized.cu`, the
`row_sums` and `column_sums` kernels uses one thread per row (or one thread per column) to
sum the whole row/column. In `matrix_sums_optimized.cu`, the `row_sums` kernel is changed so that
it does a [parallel sweep reduction](parallel_reduction.pdf) to sum each row, using one
threadblock per row (with 256 threads per block). The `column_sums` kernel remains the
same.

## Step 1: Compile the unoptimized code

First, you'll need to make sure your programming environment is set up correctly for
compiling the code. You need to make sure CUDA, gcc and the profiling tools are present
in the environment.

```
$ module load gcc
$ module load cuda
$ module load nsight-systems
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

If you look inside the batch script, you will see that the program is being run with the
Nsight System profiler `nsys profile`. This starts the profiler and attaches it to the
program. Check the output file `profiling_output_unoptimized.<jobid>` and you will see the
basic profiling output in plain text for the `row_sums` and `column_sums` kernels (scroll
down to get past the loading text). Look at the CUDA Kernel Statistics section. Notice the
difference in their duration? The column sum is a lot faster than the row sum. Why is
that? `column_sums` is faster because of _coalesced memory access_. The threads next to each
other in `column_sums` are all accessing data that are next to each other, in the array
that stores the matrix. Since the data are close to each other, the multiple memory
accesses are coalesced into a single memory access which is more efficient. For
`row_sums`, the threads are accessing data that are not close to each other so memory
access cannot be coalesced. See the Further Reading section for more resources.

## Step 3: Compile the optimized code

There is a way to make the `row_sums` as fast as the `column_sums`, by using [parallel
sweep reduction](parallel_reduction.pdf). Look at the code in `matrix_sums_optimized.cu`
and compare the `row_sums` kernel to the one in the `matrix_sums_unoptimized.cu` code.

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

This also runs the Nsight Systems profiler, same as before. Open the output file
`profiling_output_optimizes.<jobid>` and check the duration. You can see that the
duration for the `row_sums` is nearly equal to the `column_sums` kernel. What causes this?
This is also because of memory coalescing and taking advantage of more parallelism
compared to the previous code.


## Bonus Points

Can you rewrite the `column_sums` kernel in `sums_optimized.cu` to also use parallel sweep
reduction like `row_sums` does? Does that make a difference in that kernel's performance
compared to `row_sums` and compared to the old `column_sums`?


# Further information

## Profiling GUI Tools

The profiler also creates a `.qdrep` file. This can be opened in the Nsight Systems GUI
tool (you will need to download and install it on your desktop, and download the `.qdrep`
file to your local machine via `scp`) to provide a visualization of the program's run. You
can find more instructions on how to get and use the GUI tool in the [Summit
docs](https://docs.olcf.ornl.gov/systems/summit_user_guide.html#optimizing-and-profiling).

## Useful resources

- Coffeebeforearch's video on coalescing in GPUs: https://www.youtube.com/watch?v=_qSP455IekE
- The OLCF CUDA training series: https://www.olcf.ornl.gov/cuda-training-series/
