/*
 * untitled.c
 * 
 * Copyright 2021  <pi@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <wiringPi.h>
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include "ps2pi.h"

struct space_invader{
	char x;
	char y;
} a[20];

ps2pi_t ps2;
int maxlines, maxcols;
int x, y;

int main(int argc, char **argv)
{
	
	if (wiringPiSetupPhys() == -1) {
		perror("Unable to start wiringPi");
		return 1;
    }
    
    ps2.begin(11, 3, 5, 13);

	initscr();
	maxlines = LINES - 1;
    maxcols = COLS - 1;
    
	
	refresh();
	x = maxcols / 2;
	y = maxlines / 2;
	
	printw("BANGBANG");
	
	
	while (!ps2.isSelectPressed()){
		ps2.readPS2();
		mvaddch(1,1, ps2.isValid()?'*':'?');
		
		
		if (ps2.getLeftX() < 0x80){
			if (x > 0){
				x--;
			}
		}
		if (ps2.getLeftX() > 0x80){
			if (x < maxcols){
				x++;
			}
		}
		if (ps2.getLeftY() > 0x80){
			if (y < maxlines){
				y++;
			}
		}
		if (ps2.getLeftY() < 0x80){
			if (y > 0){
				y--;
			}
		}
		if (ps2.isXPressed()){
			for(int i = y; i >0; i--){
				mvaddch(i,x,'*');
				refresh();
				delay(2);
				mvaddch(i,x,'|');
				refresh();
				delay(2);
				mvaddch(i,x,' ');
				refresh();
				
			}
		} else {
			mvaddch(y,x,'X');
			refresh();
			mvaddch(y,x,'-');
			refresh();
			mvaddch(y,x,' ');
			refresh();
		}
		refresh();
	}
	endwin();
	return 0;
}

