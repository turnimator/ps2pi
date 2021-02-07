
all: libps2pi.a messy clean

libps2pi.a: ps2pi.o
	ar rcs libps2pi.a ps2pi.o

ps2pi.o : ps2pi.cpp ps2pi.h
	cc -c ps2pi.cpp -o ps2pi.o
	
install: libps2pi.a
	cp -v ps2pi.h /usr/local/include
	cp -v libps2pi.a /usr/local/lib
	
clean: clean.cpp libps2pi.a
	cc  clean.cpp -o clean -lcurses -lwiringPi -lps2pi
	
messy : messy.cpp ps2pi.cpp
	cc messy.cpp ps2pi.cpp -o sample -lcurses -lwiringPi

curstst : curstst.cpp ps2pi.cpp
	cc curstst.cpp ps2pi.cpp -o curstst -lcurses -lwiringPi
	
