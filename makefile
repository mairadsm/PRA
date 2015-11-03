all: Trabalho.exe

Trabalho.exe: Trabalho.o CuTest.o btree.o
	gcc -o Trabalho.exe $^

%.o: %.c
	gcc -c $*.c -o $*.o

clean:
	rm Trabalho.o Trabalho.exe
