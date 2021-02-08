# ps2pi
## PS2 Controller Library for the Raspberry Pi
 
 This project is built from bits and pieces I've found on the Internet,
 including, but not limited to 
Bill Porter madsci1016/Arduino-PS2X
c-herring/PiPS2

For some reason, I couldn't get the PiPS2 library to work with my Chinese
knockoff PS2 controller, so I sat down and hacked it beyond recognition.
I've probably thrown a dozen babies out with the bath water, but now

IT WORKS FOR ME

To compile, you need the wiringPi library, and if you want to run the curstst program,
you'll need the curses library.
I've included two shell scripsts for your convenience.

## Usage
There's a messy way and a clean way.

### The messy way

   LOOP
      Read PS2 Controller
      See if this button is pressed
      See if that button is pressed
      Clutter up the code with more of these
   END LOOP
   
For an example, see the file messy.cpp

### The clean way

    Register all your functions as actions
    LOOP
        Read PS2 Controller and ispatch actions
    END
    
For an example, see the file clean.cpp

## setXAction(xaction, user_data)
Register a function void xaction(int pressure, void *user_data) to be called when the X button is pressed.
The pointer user_data can point to anything.


## TODO
See if I can get pressure mode and native mode to work.
Find a better way to ensure valid data
