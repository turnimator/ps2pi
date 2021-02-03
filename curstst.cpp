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

struct space_invader {
	char x;
	char y;
	char c = '#';
} a[20];

ps2pi_t ps2;
int maxlines, maxcols;
int x, y;

int points = 0;

void print_invaders(){
	for(int i = 0; i < 20; i++){
		mvaddch(a[i].y,a[i].x,a[i].c);
	}
	refresh();
}

bool isHit(int x, int y)
{
	for (int i = 0; i < 20; i++) {
		if (a[i].x == y && a[i].y == y) {
			a[i].c = ' ';
			points += 100;
			return true;
		}
	}
	return false;
}

void create_invaders()
{
	for(int i=0; i<20;i++){
		a[i].x=i*2;
		a[i].y=1;
		a[i].c = '#';
	}
}

void erase_invaders(){
	for(int i = 0; i < 20; i++){
		mvaddch(a[i].y,a[i].x, ' ');
	}
	refresh();
}

void move_invaders(){
	erase_invaders();
	for(int i=0; i<20;i++){
		if (random()%100==0){
			a[i].y++;
		}
	}
	print_invaders();
}

// TODO Print the space invaders on screen and move them around
char help[] = "MODE:change X:shoot LEFT-JOY:move START:restart SELECT:end";
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
	create_invaders();
	
	refresh();
	x = maxcols / 2;
	y = maxlines / 2;
	curs_set(0);
	while (!ps2.isSelectPressed()) {
		move_invaders();
		
		ps2.readPS2();
		mvprintw(1, 1, "Score: %06d ", points);
		mvaddch(y,x,' ');
		refresh();
		if (ps2.getMode() == DIGITALMODE) {
			mvprintw(0, 0, "DIGITAL %s  ", help);
			if (ps2.isPadLeftPressed()) {
				if (x > 0) {
					x--;
				}
			}
			if (ps2.isPadRightPressed()) {
				if (x < maxcols) {
					x++;
				}
			}
			if (ps2.isPadDownPressed()) {
				if (y < maxlines) {
					y++;
				}
			}
			if (ps2.isPadUpPressed()) {
				if (y > 0) {
					y--;
				}
			}
		} else if (ps2.getMode() == ANALOGMODE) {
			mvprintw(0, 0, "ANALOG %s  ", help);
			x = ((ps2.getLeftX() * maxcols) / 256);
			y = ((ps2.getLeftY() * maxlines) / 256);
		}
		if (ps2.isStartPressed()){
			create_invaders();
		}
		if (ps2.isXPressed()) {
			for (int i = y; i > 0; i--) {
				mvaddch(i, x, '*');
				refresh();
				delay(2);
				mvaddch(i, x, '|');
				refresh();
				delay(2);
				mvaddch(i, x, ' ');
				refresh();
				if (isHit(x, i)) {
					mvprintw(i, x, "***");
					refresh();
					mvprintw(i, x, " * ");
					refresh();
				}
			}
		} else {
			mvaddch(y, x, 'X');
			refresh();
			mvaddch(y, x, '-');
			refresh();
			mvaddch(y, x, ' ');
			refresh();
		}
		mvaddch(y,x,'^');
		
		refresh();
		refresh();
	}
	endwin();
	return 0;
}
