all: first_cuda.cu dir
	nvcc -o ./obj/first first_cuda.cu  
dir: 
	mkdir -p ./obj/
clean:
	rm *.err && rm *.out