FLAGS=-g -lm
OBJ=./obj/
LIB=lib.h

all: $(TARGET).c O0 O1 O2 O3 
	gcc $(LIB) $(TARGET).c -o $(OBJ)$(TARGET) $(FLAGS)
dir:
	mkdir -p $(OBJ)
O0: $(TARGET).c dir
	gcc $(LIB) $(TARGET).c -o $(OBJ)$(TARGET)0 $(FLAGS) -O0
	
O1: $(TARGET).c dir
	gcc $(TARGET).c -o $(OBJ)$(TARGET)1 $(FLAGS) -O1

O2: $(TARGET).c dir
	gcc $(TARGET).c -o $(OBJ)$(TARGET)2 $(FLAGS) -O2

O3: $(TARGET).c dir
	gcc $(TARGET).c -o $(OBJ)$(TARGET)3 $(FLAGS) -O3



clean: 
	rm -r ./obj/*