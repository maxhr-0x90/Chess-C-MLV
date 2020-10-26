CC=gcc
CFLAGS=-W -std=c89 -pedantic -O3
CGRAPH=`pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
ENDFLAGS=`pkg-config --libs-only-l MLV`

main : mod_graphic.o mod_verif.o init-module.o main.o
	$(CC) $(CFLAGS) $(CGRAPH) mod_graphic.o mod_verif.o init-module.o main.o $(ENDFLAGS) -o main

main.o : main.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) main.c

mod_graphic.o : mod_graphic.c
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) mod_graphic.c

mod_verif.o : mod_verif.c
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) mod_verif.c

init-module.o : init-module.c
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) init-module.c

clean :
	rm -f *.o
