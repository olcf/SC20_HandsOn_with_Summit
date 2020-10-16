CUCOMP = mpicc
CFLAGS =

run: mpi_bcast.o
	$(CUCOMP) $(CFLAGS) mpi_bcast.o -o run

mpi_hello.o: mpi_bcast.c
	$(CUCOMP) $(CFLAGS) -c mpi_bcast.c

.PHONY: clean cleanall

clean:
	rm -f run *.o

cleanall:
	rm -f run *.o bcast.*
