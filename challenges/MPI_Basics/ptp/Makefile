CUCOMP = mpicc
CFLAGS =

run: ptp.o
	$(CUCOMP) $(CFLAGS) ptp.o -o run

ptp.o: ptp.c
	$(CUCOMP) $(CFLAGS) -c ptp.c

.PHONY: clean cleanall

clean:
	rm -f run *.o

cleanall:
	rm -f run *.o ptp*
