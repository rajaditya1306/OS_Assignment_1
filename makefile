output: assignment_1.asm
	yasm -f elf64 assignment_1.asm -o out.o
	gcc -no-pie out.o -o output
	./output