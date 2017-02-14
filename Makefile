VPATH = IHM/ Engine/ ListLib/ Tab1DLib/
CC=gcc
SRC=$(wildcard IHM/*.c Engine/*.c ListLib/*.c Tab1DLib/*.c)
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))
PROG=affichage

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -g -o $@ $^ -lX11 -lXtst -lXext

%.o: %.c %.h
	$(CC) -g -c $<

clean:
	rm $(PROG) *.o
