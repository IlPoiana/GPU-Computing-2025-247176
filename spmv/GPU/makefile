FLAGS= -diag-suppress 177

all: COO_rnd

COO_rnd: coo_rnd.cu
	nvcc -o coo_rnd coo_rnd.cu $(FLAGS)

clean_all: 
	rm *.out && rm *.err
