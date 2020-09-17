#CFLAGS = -lineinfo

optimized:
        nvcc $(CFLAGS) -o matrix_sums matrix_sums.cu

unoptimized:
        nvcc $(CFLAGS) -o matrix_sums_solution matrix_sums_solution.cu

clean:
        rm -f matrix_sums matrix_sums_solution
