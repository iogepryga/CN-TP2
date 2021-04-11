SRC=$(wildcard *.c)
PROG=$(SRC:.c=)
OBJ=$(SRC:.c=.o)

all : $(PROG)

$(PROG) : $(OBJ)
	gcc -g -Wall -o $@ $@.o

%.o : %.c
	gcc -g -Wall -c $<
	
clean :
	rm -f *.o $(PROG)
