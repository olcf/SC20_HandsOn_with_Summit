#CFLAGS = -lineinfo

optimized:
	nvcc $(CFLAGS) -o matrix_sums_optimized matrix_sums_optimized.cu

unoptimized:
	nvcc $(CFLAGS) -o matrix_sums_unoptimized matrix_sums_unoptimized.cu

clean:
	rm -f matrix_sums_optimized matrix_sums_unoptimized
