
all: bison flex gcc
	@echo "Done."

bison: Parser.y
	bison Parser.y

flex: Scanner.l
	flex Scanner.l

gcc: lex.yy.c Parser.c
	gcc -Wall -o parser lex.yy.c Parser.c tables.o -ly

clean:
	@rm -f *.o *.output scanner.c parser.h parser.c parser
