all: bison flex gcc
	@echo "Feito."

bison: parser.y
	bison parser.y

flex: Scanner.l
	flex Scanner.l

gcc: scanner.c parser.c
	gcc -Wall -o parser scanner.c parser.c -ly -lm

clean:
	@rm -f *.o *.output Scanner.c parser.h parser.c parser
