C=gcc
CFLAGS=-Wall

%.o: %.c %.h
	$(C) -o $@ -c $< $(CFLAGS)

main: main.o
	$(C) -o $@.zizi $^

pile: PileLR.o
	$(C) -o $@.zizi $^
	./pile.zizi

arbre: arbre.o
	$(C) -o $@.zizi $^
	./arbre.zizi

run: main clean
	./main.zizi

clean : 
	rm -f *.o