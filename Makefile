
all: sample curstst

sample : sample.cpp ps2pi.cpp
	cc sample.cpp ps2pi.cpp -o sample -lcurses -lwiringPi

curstst : curstst.cpp ps2pi.cpp
	cc curstst.cpp ps2pi.cpp -o curstst -lcurses -lwiringPi
	
