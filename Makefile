CC=gcc
CFLAGS=-W -Wall -std=c89 -pedantic -O3 -g
CGRAPH=`pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
ENDFLAGS=`pkg-config --libs-only-l MLV`

main : module_graphic.o module_verif.o init-module.o module_menu.o module_jeu.o module_save.o main.o
	$(CC) $(CFLAGS) $(CGRAPH) module_graphic.o module_verif.o init-module.o module_menu.o module_jeu.o module_save.o main.o $(ENDFLAGS) -o main

main.o : main.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) main.c

module_graphic.o : module_graphic.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_graphic.c

module_verif.o : module_verif.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_verif.c

init-module.o : init-module.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) init-module.c

module_menu.o : module_menu.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_menu.c

module_jeu.o : module_jeu.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_jeu.c

module_save.o : module_save.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_save.c

clean :
	rm -rf *.o main
