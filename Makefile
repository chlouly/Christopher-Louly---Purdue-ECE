RNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

SRCS = hw12.c stack.c calc.c
OBJS = $(SRCS:%.c=%.o)
EXEC = hw12
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

all: $(EXEC)

$(EXEC): $(OBJS)
	$(GCC) $(OBJS) -o $(EXEC)

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 
	
clean: 
	rm -f $(EXEC) *.o output?
