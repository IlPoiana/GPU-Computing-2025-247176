FLAGS= -O3 
O2= -O2
all: COO_rnd COO

COO_rnd: coo_rnd.cu
	nvcc -o coo_rnd coo_rnd.cu $(FLAGS)
	nvcc -o coo_rnd coo_rnd.cu $(O2)
COO: coo.cu
	nvcc -o coo coo.cu $(FLAGS)
	nvcc -o coo2 coo.cu $(O2)
clean_all: 
	rm *.out && rm *.err
