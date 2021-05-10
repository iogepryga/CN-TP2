SRC=$(wildcard *.c)
PROG=$(SRC:.c=)
OBJ=$(SRC:.c=.o)

all : $(PROG)

$(PROG) : $(OBJ)
	gcc -g -O0 -Wall -o $@ $@.o

%.o : %.c
	gcc -g -O0 -Wall -c $<
	
clean :
	rm -f *.o $(PROG)
