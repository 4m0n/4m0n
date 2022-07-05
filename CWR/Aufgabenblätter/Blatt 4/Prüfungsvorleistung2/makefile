# makefile-constants
BINARY  := 2dintegral
HEADER  := ../../../Funktionen/my_numerics
ARGS    :=
ARGS_PY :=

# Structure:
#-----------------------
# TARGET: DEPENDENCIES
#	COMMAND-LIST
#-----------------------
# Usage:
#-----------------------
# make TARGET


# Default Target because it's the 1st one
$(BINARY): $(BINARY).c $(HEADER).o $(HEADER).h
	gcc -o $(BINARY) $(BINARY).c $(HEADER).o -O3 -Wall -lm -lgsl -lgslcblas -l lapacke

# Headerfile compilation
$(HEADER).o: $(HEADER).c $(HEADER).h
	gcc -c $(HEADER).c -o $(HEADER).o -O3 -Wall -lm -lgsl -lgslcblas -l lapacke

# Default-Compile Target for every other .c file; remember to add those as
# additional dependencies to the $(BINARY) target !
.o: .c
	gcc -c $< -O3 -Wall -lm -lgsl -lgslcblas -l lapacke


# running and plotting with args
run: $(BINARY)
	./$(BINARY) $(ARGS)
plot1:
	python3 plot1.py $(ARGS_PY)
plot2:
	python3 plot2.py $(ARGS_PY)

# make everything
all: clean $(BINARY) run

# removing unneccessary / temporary files
clean:
	rm  -f $(BINARY)
	rm  -f $(HEADER).o
	rm  -f *.o
	rm  -f *.csv *.dat *.txt
