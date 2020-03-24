CFLAG=-I.
OBJ=build/shellmemory.o build/interpreter.o build/pcb.o build/ram.o build/cpu.o build/statusCode.o build/shell.o build/kernel.o build/memorymanager.o

mykrenel: $(OBJ)
	gcc -o mykernel $(OBJ)
	
build/%.o: %.c
	gcc -c $^ -o $@ $(CFLAG)


clear:
	rm $(OBJ) build/mysh
