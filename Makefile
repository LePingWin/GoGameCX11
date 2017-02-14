VPATH = IHM/ Engine/ ListLib/ Tab1DLib/
CC=gcc
SRC=$(wildcard IHM/*.c Engine/*.c ListLib/*.c Tab1DLib/*.c)
OBJ=$(notdir $(patsubst %.c,%.o,$(SRC)))
PROG=affichage

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $@ $^ -lX11

%.o: %.c %.h
	$(CC) -c $<

clean:
	rm $(PROG) *.o
