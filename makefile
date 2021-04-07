CFLAGS = -g -Wall -Werror
IFLAGS = -Iinclude
OPATH = obj/
CPATH = src/
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11
DEFINE = -D_GNU_SOURCE 

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

ifeq (TEXTE,$(MODE))

main : main.o io.o libjeu.a 
	gcc $(DEFINE) $(CFLAGS) -o main $(OPATH)main.o $(OPATH)io.o -L./lib/ -ljeu $(LDFLAGS)
	mkdir -p bin/
	mv $@ bin/

main.o : main.c
io.o : io.c io.h jeu.h grille.h
jeu.o : jeu.c jeu.h grille.h
grille.o : grille.c grille.h

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	ranlib libjeu.a
	mkdir -p lib/
	mv libjeu.a lib/

%.o :
	gcc $(DEFINE) $(CFLAGS) $(CPPFLAGS) -c $< $(IFLAGS)
	mkdir -p obj/
	mv $@ $(OPATH)


else

main : main.o iocairo.o libjeu.a 
	gcc $(DEFINE) $(CFLAGS) -o main $(OPATH)main.o $(OPATH)iocairo.o -L./lib/ -ljeu $(LDFLAGS)
	mkdir -p bin/
	mv $@ bin/

main.o : main.c
iocairo.o : iocairo.c iocairo.h jeu.h grille.h
jeu.o : jeu.c jeu.h grille.h
grille.o : grille.c grille.h

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	ranlib libjeu.a
	mkdir -p lib/
	mv libjeu.a lib/

%.o :
	gcc $(DEFINE) $(CFLAGS) $(CPPFLAGS) -c $< $(IFLAGS)
	mkdir -p obj/
	mv $@ $(OPATH)
endif


	

clean : 
	rm -f lib/* obj/* bin/* *.tar.xz -r doc 

dist:
	tar -c -J src/*.c include/*.h makefile grilles/* Doxyfile README.md -f Doniczka_quentin_jeu_de_la_vie_5.3.1.tar.xz

doc :
	doxygen Doxyfile
# dist: src/*.c include/*.h makefile doxyfile
# 	tar cfJ jeu_de_la_vie_1.tar.xz src/*.c include/*.h makefile Doxyfile