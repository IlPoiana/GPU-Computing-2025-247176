FLAGS=-g -lm -fopenmp
OBJ=./obj/
LIB=../lib.h

all:dir COO CSR heap_comparison stack_comparison 
dir:
	mkdir -p $(OBJ)
COO:
	gcc $(LIB) coo.c -o $(OBJ)coo $(FLAGS) -O3
COO_flags: dir COO
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo1 $(FLAGS) -O1
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo2 $(FLAGS) -O2
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo3 $(FLAGS) -O3
COO_1:
	gcc $(LIB) coo_rnd_1.c -o $(OBJ)coo $(FLAGS)
COO_1flags: dir COO_1
	gcc $(LIB) coo_rnd_1.c -o $(OBJ)coo1 $(FLAGS) -O1
	gcc $(LIB) coo_rnd_1.c -o $(OBJ)coo2 $(FLAGS) -O2
	gcc $(LIB) coo_rnd_1.c -o $(OBJ)coo3 $(FLAGS) -O3
CSR:
	gcc $(LIB) csr_rnd.c -o $(OBJ)csr $(FLAGS)
import_test: import_test.c
	gcc $(LIB) import_test.c -o $(OBJ)import_test $(FLAGS) -O3
heap_comparison:
	gcc $(LIB) heap_comparison.c -o $(OBJ)comparison $(FLAGS)
	gcc $(LIB) heap_comparison.c -o $(OBJ)comparison1 $(FLAGS) -O1
	gcc $(LIB) heap_comparison.c -o $(OBJ)comparison2 $(FLAGS) -O2
	gcc $(LIB) heap_comparison.c -o $(OBJ)comparison3 $(FLAGS) -O3
stack_comparison:
	gcc $(LIB) stack_comparison.c -o $(OBJ)comparison $(FLAGS)
	gcc $(LIB) stack_comparison.c -o $(OBJ)comparison1 $(FLAGS) -O1
	gcc $(LIB) stack_comparison.c -o $(OBJ)comparison2 $(FLAGS) -O2
	gcc $(LIB) stack_comparison.c -o $(OBJ)comparison3 $(FLAGS) -O3
	clean_all: clean clean_out clean_cache 
clean: 
	rm -r ./obj/*
clean_out:
	rm *.err && rm *.out
clean_cache:
	rm ./cachegrind.*