all: assembler

asm_parser.o: asm_parser.c
	clang -c asm_parser.c

assembler: assembler.c asm_parser.o
	clang assembler.c asm_parser.o -o assembler

clean:
	rm -rf *.o

clobber: clean
	rm -rf assembler