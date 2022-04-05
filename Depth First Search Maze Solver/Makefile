RNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS = hw11.c list.c solver.c maze.c mazehelper.c
OBJS = $(SRCS:%.c=%.o)
EXEC = hw11
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

hw11: $(OBJS)
	$(GCC) $(OBJS) -o hw11

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

TEST: 1 2 3
	
1: hw11
	./hw11 inputs/maze1 out1

2: hw11
	./hw11 inputs/maze2 out2

3: hw11
	./hw11 inputs/maze3 out3

memory: hw11
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/maze1 out1
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/maze2 out2
	$(VALGRIND) --log-file=log1 ./$(EXEC) inputs/maze3 out3

clean: 
	rm -f hw10 *.o output?

