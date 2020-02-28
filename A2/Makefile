CFLAG=-I.
OBJ=shellmemory.o interpreter.o pcb.o ram.o cpu.o statusCode.o shell.o kernel.o

mykrenel: $(OBJ)
	gcc -o mykernel $(OBJ)
	
build/%.o: %.c
	gcc -c $^ -o $@ $(CFLAG)
