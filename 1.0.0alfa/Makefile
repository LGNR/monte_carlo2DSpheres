# Monte Carlo Makefile    #
#			  #
#			  #


monte_carlo : main.o libmontecarlo.o libsalida.o buffer.o libinicializacion.o 
	cc -o monte_carlo main.o libmontecarlo.o libsalida.o buffer.o libinicializacion.o -lcpgplot -lm

main.o : libmontecarlo.o libsalida.o libinicializacion.o 
buffer.o :
libinicializacion.o : buffer.h
libmontecarlo.o : libinicializacion.h -lm
libsalida.o : 


clean:
	rm *.o
