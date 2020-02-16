CFLAG=-I.
OBJ=build/shellmemory.o build/interpreter.o build/shell.o

mysh: $(OBJ)
	gcc -o build/mysh $(OBJ)
	
build/%.o: %.c
	gcc -c $^ -o $@ $(CFLAG)


clear:
	rm $(OBJ) build/mysh
