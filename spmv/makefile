FLAGS=-g -lm
OBJ=./obj/
LIB=../lib.h

all:dir COO CSR comparison
COO:
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo $(FLAGS)
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
comparison:
	gcc $(LIB) comparison.c -o $(OBJ)comparison $(FLAGS)
	gcc $(LIB) comparison.c -o $(OBJ)comparison1 $(FLAGS) -O1
	gcc $(LIB) comparison.c -o $(OBJ)comparison2 $(FLAGS) -O2
	gcc $(LIB) comparison.c -o $(OBJ)comparison3 $(FLAGS) -O3