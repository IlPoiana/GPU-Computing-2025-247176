FLAGS=-g -lm
OBJ=./obj/
LIB=../lib.h

all:dir COO CSR 
COO:
	gcc $(LIB) coo_rnd.c -o $(OBJ)coo $(FLAGS)
CSR:
	gcc $(LIB) csr_rnd.c -o $(OBJ)csr $(FLAGS)
dir:
	mkdir -p $(OBJ)
clean: 
	rm -r ./obj/*