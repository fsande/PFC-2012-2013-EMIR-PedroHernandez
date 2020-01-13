CO       = -o
CC       = g++
CCOMPILE = -c
CDEBUG   = -g
CSTATIC  = -static 
COPC     = -ansi -pedantic
COPTIM   = -O3
COPT     = `allegro-config --libs` 
COPP     = `pkg-config --cflags --libs glibmm-2.4 giomm-2.4`
Doxy     = doxygen
PUNTO    = main.o element.o csu.o

XML.DIR  = ../ejemplos/xml

EMIR: main.o element.o csu.o
	$(CC) $(CO) mapEditor $(PUNTO) $(COPTIM) $(COPT) $(COPP)
#	$(Doxy) Doxyfile

main.o: main.C
	clear
	$(CC) $(CCOMPILE) main.C $(COPP)

element.o: element.C
	$(CC) $(CCOMPILE) element.C

csu.o: element.h csu.C
	$(CC) $(CCOMPILE) csu.C

clean:
	rm -f *.o *~ *.gch ejecutable
	clear

gg:
	$(CC) $(CO) ../ejemplos/garzon ../ejemplos/garzon.cpp $(COPT)
run:
	./ejecutable ../ejemplos/xml/garzon.xml

