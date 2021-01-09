compile:
	gcc *.c -o main

run:
	./main

clean:
	rm -f *.o main

valgrind:
	@make clean
	@gcc *.c -o main -g
	@valgrind --show-leak-kinds=all --leak-check=yes --track-origins=yes ./main

all:
	@make clean --no-print-directory
	@make compile --no-print-directory
	@make run --no-print-directory
