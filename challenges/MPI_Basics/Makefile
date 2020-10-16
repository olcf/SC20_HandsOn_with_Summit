CUCOMP = mpicc
CFLAGS =

run: mpi_hello.o
	$(CUCOMP) $(CFLAGS) mpi_hello.o -o run

mpi_hello.o: mpi_hello.c
	$(CUCOMP) $(CFLAGS) -c mpi_hello.c

.PHONY: clean cleanall

clean:
	rm -f run *.o

cleanall:
	rm -f run *.o mpi_hello*
