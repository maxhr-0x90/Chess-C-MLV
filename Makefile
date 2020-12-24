CC=gcc
CFLAGS=-W -Wall -std=c89 -pedantic -O3 -g
CGRAPH=`pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
ENDFLAGS=`pkg-config --libs-only-l MLV`
TARGET=module_graphic.o module_verif.o init-module.o module_menu.o module_jeu.o module_save.o module_math.o module_timer.o module_editor.o main.o
main : $(TARGET)
	$(CC) $(CFLAGS) $(CGRAPH) $(TARGET) $(ENDFLAGS) -o main

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

module_math.o : module_math.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_math.c

module_timer.o : module_timer.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_timer.c

module_editor.o : module_editor.c assets.h
	$(CC) $(CFLAGS) $(CGRAPH) -c $(ENDFLAGS) module_editor.c

clean :
	rm -rf *.o
