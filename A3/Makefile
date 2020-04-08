CFLAG=-I.
OBJ=shellmemory.o interpreter.o pcb.o ram.o cpu.o statusCode.o shell.o kernel.o memorymanager.o main.o

mykrenel: $(OBJ)
	gcc -o mykernel $(OBJ)	
build/%.o: %.c
	gcc -c $^ -o $@ $(CFLAG)


clear:
	rm $(OBJ) build/mysh
