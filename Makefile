
all: sample curstst

libps2pi.a: ps2pi.cpp
	cc -c ps2pi.cpp -o ps2pi.o
	ar rcs libps2pi.a ps2pi.o

install: libps2pi.a
	cp -v ps2pi.h /usr/local/include
	cp -v libps2pi.a /usr/local/lib
	
sample : sample.cpp ps2pi.cpp
	cc sample.cpp ps2pi.cpp -o sample -lcurses -lwiringPi

curstst : curstst.cpp ps2pi.cpp
	cc curstst.cpp ps2pi.cpp -o curstst -lcurses -lwiringPi
	
