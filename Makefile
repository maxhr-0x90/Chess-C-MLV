CC=gcc
CFLAGS=-W -std=c89 -pedantic -O3
CGRAPH=`pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
ENDFLAGS=`pkg-config --libs-only-l MLV`

main : module_graphic.o module_verif.o init-module.o main.o
	$(CC) $(CFLAGS) $(CGRAPH) module_graphic.o module_verif.o init-module.o main.o $(ENDFLAGS) -o main

main.o : main.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) main.c

module_graphic.o : module_graphic.c
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_graphic.c

module_verif.o : module_verif.c
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_verif.c

init-module.o : init-module.c
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) init-module.c

clean :
	rm -f *.o
