ADD=addition

# all: test.cu dir
# 	nvcc -o ./obj/test test.cu
all: $(ADD).cu dir
	nvcc -o ./obj/$(ADD) $(ADD).cu
dir: 
	mkdir -p ./obj/
	mkdir -p ./out/
clean:
	rm ./out/* && rm ./obj/*