
all: bison flex gcc
	@echo "Done."

bison: parser.y
	bison parser.y

flex: scanner.l
	flex scanner.l

gcc: scanner.c parser.c ast.c code.c tables.c
	gcc -Wall -o tinyc scanner.c parser.c ast.c code.c tables.c

tm: tm.c
	gcc -Wall -o tmsim tm.c

clean:
	@rm -f *.o *.output scanner.c parser.h parser.c *.dot *.pdf tinyc tmsim
