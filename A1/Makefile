mysh: shell.o shellmemory.o interpreter.o
	gcc -o mysh shell.o shellmemory.o interpreter.o
	
shell.o: shell.c shell.h
	gcc -c shell.c

shellmemory.o: shellmemory.c shellmemory.h
	gcc -c shellmemory.c

intepreter.o: interpreter.c interpreter.h
	gcc -c interpreter.c

clear:
	rn *.o mysh
