FLAGS=-g -lm
OBJ=./obj/
LIB=../lib.h

all:dir COO CSR heap_comparison stack_comparison 
COO:
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo $(FLAGS)
COO_flags: dir COO
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo1 $(FLAGS) -O1
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo2 $(FLAGS) -O2
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo3 $(FLAGS) -O3
CSR:
	gcc $(LIB) csr_rnd.c -o $(OBJ)csr $(FLAGS)
dir:
	mkdir -p $(OBJ)
clean_all: clean clean_out clean_cache 
clean: 
	rm -r ./obj/*
clean_out:
	rm -r ./out/*
clean_cache:
	rm ./cachegrind.*
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