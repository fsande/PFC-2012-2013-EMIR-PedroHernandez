CO       = -o
CC       = g++
CCOMPILE = -c
CDEBUG   = -g
CSTATIC  = -static 
COPC     = -ansi -pedantic
COPTIM   = -O3
COPT     = `allegro-config --libs` 
COPP     = -I/usr/include/libxml++-2.6/ `pkg-config libxml++-2.6 --cflags --libs` `pkg-config --cflags --libs glibmm-2.4 giomm-2.4`
EXE      = csuoptimizer
Doxy     = doxygen
PUNTO    = main.o parser.o element.o dbscan.o csu.o 

XML.DIR  = ../ejemplos/xml

EMIR: main.o parser.o element.o dbscan.o csu.o 
	$(CC) $(COPTIM) $(CO) $(EXE) $(PUNTO) $(COPT) $(COPP)

main.o: parser.h main.C
	clear
	$(CC) $(COPTIM) $(CCOMPILE) main.C $(COPP)

parser.o: element.h parser.C
	$(CC) $(COPTIM) $(CCOMPILE) parser.C $(COPP)

element.o: element.C
	$(CC) $(COPTIM) $(CCOMPILE) element.C

dbscan.o: dbscan.h dbscan.C
	$(CC) $(COPTIM) $(CCOMPILE) dbscan.C

csu.o: element.h csu.C
	$(CC) $(COPTIM) $(CCOMPILE) csu.C

clean:
	rm -f *.o *~ *.gch 
	clear

doxy:
	$(Doxy) Doxyfile

