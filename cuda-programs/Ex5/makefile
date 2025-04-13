all: addition.cu dir
	nvcc -o ./obj/addition addition.cu  
dir: 
	mkdir -p ./obj/
	mkdir -p ./out/
clean:
	rm ./out/* && rm ./obj/*