CC=gcc -g 
Iarg= -I ../

all: test.exe Banker.exe

test.exe:test.c array.c
	$(CC) $(Iarg) $^ -o $@


Banker.exe:Banker.c array.c
	$(CC)  $^ -o $@ $(Iarg)

array.c:array.h
