CC = gcc
CFLAGS = -g -O2 -Wall -pedantic -Wno-unused-result -lm

maze: main.c Maze.c Heap.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean debug-maze

clean:
	rm -f maze valgrind.log
	
debug-maze: maze
	valgrind --leak-check=full --track-origins=yes --trace-children=yes --show-leak-kinds=all --log-file=valgrind.log -- ./maze
