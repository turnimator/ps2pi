
all: libps2pi.a sample curstst dispatchtst

libps2pi.a: ps2pi.o
	ar rcs libps2pi.a ps2pi.o

ps2pi.o : ps2pi.cpp ps2pi.h
	cc -c ps2pi.cpp -o ps2pi.o
	
install: libps2pi.a
	cp -v ps2pi.h /usr/local/include
	cp -v libps2pi.a /usr/local/lib
	
dispatchtst: dispatchtst.cpp libps2pi.a
	cc  dispatchtst.cpp -o dispatchtst -lcurses -lwiringPi -lps2pi
	
sample : sample.cpp ps2pi.cpp
	cc sample.cpp ps2pi.cpp -o sample -lcurses -lwiringPi

curstst : curstst.cpp ps2pi.cpp
	cc curstst.cpp ps2pi.cpp -o curstst -lcurses -lwiringPi
	
