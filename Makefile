CFLAG=-I.

mysh: shell.o shellmemory.o interpreter.o
	gcc -o mysh shell.o shellmemory.o interpreter.o
	
shell.o: shell.c
	gcc -c $^ $(CFLAG)

shellmemory.o: shellmemory.c shellmemory.h
	gcc -c shellmemory.c

interpreter.o: interpreter.c interpreter.h
	gcc -c interpreter.c

clear:
	rn *.o mysh
