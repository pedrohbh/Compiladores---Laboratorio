
all: flex gcc
	@echo "Done."

flex: scanner.l
	flex scanner.l

gcc: scanner.c calc.c
	gcc -Wall -o calc scanner.c calc.c

clean:
	@rm -f *.o scanner.c calc
