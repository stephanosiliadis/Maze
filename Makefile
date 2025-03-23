CC = gcc
CFLAGS = -g -O2 -Wall -pedantic -Wno-unused-result -lm

maze: main.c Maze.c Heap.c helpers.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean debug-maze profile-maze cpu-profile-maze

# Clean compiled files and analysis outputs
clean:
	rm -f maze valgrind.log massif.out massif.txt callgrind.out xtmemory.kcg.*

#  Memory Leak Debugging
# Use this to check for memory leaks, invalid accesses, and uninitialized memory
# Usage: make debug-maze
debug-maze: maze
	valgrind --leak-check=full --track-origins=yes --trace-children=yes \
	--show-leak-kinds=all --num-callers=20 --leak-resolution=high \
	--log-file=valgrind.log -- ./maze

#  Heap Profiling with Massif
# Use this to analyze heap memory usage over time and visualize it
# Usage: make profile-maze [VIS=massif|kcache] . the part in square brakets is [OPTIONAL] input
# - VIS=massif  → opens in massif-visualizer (default)
# - VIS=kcache  → opens in kcachegrind
profile-maze: maze
	valgrind --tool=massif --massif-out-file=massif.out --xtree-memory=full ./maze
	ms_print massif.out > massif.txt
	@echo "Heap profile saved to massif.out and massif.txt"
	@if [ "$(VIS)" = "kcache" ]; then \
		command -v kcachegrind >/dev/null && kcachegrind massif.out || echo "kcachegrind not found."; \
	elif [ "$(VIS)" = "massif" ] || [ -z "$(VIS)" ]; then \
		command -v massif-visualizer >/dev/null && massif-visualizer massif.out || echo "massif-visualizer not found."; \
	else \
		echo "Unknown VIS value: $(VIS). Use VIS=massif or VIS=kcache."; \
	fi

#  CPU Profiling with Callgrind
# Use this to identify performance bottlenecks and see which functions take the most CPU time
# Usage: make cpu-profile-maze
# View the output using kcachegrind (or qcachegrind)
cpu-profile-maze: maze
	valgrind --tool=callgrind --callgrind-out-file=callgrind.out ./maze
	@echo "CPU profile written to callgrind.out"
	@command -v kcachegrind >/dev/null && kcachegrind callgrind.out || \
	echo "kcachegrind not found. Please install it to visualize callgrind output."
