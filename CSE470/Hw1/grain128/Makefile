all: main

out: 
	gcc  ecrypt.c grain128.c tests.c -o test
	
main: out
	./test
	
clean: 
	rm *.o output
