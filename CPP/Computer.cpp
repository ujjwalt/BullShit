/*
 *  Computer.cpp
 *  BullShit
 *
 *  Created by Ujjwal Thaakar on 09/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#include "Computer.h"
#import "main.h"

Computer::Computer() {
	count++;
	if (count == 1) {
		names = new string[10];
	}
	if (count < 10) {
		name = names[count];
	} else {
		name = names[random()%count];
		char c[2];
		c[0] = count+'0';
		c[1] = '\0';
		string a(c);
		name.append(a);
	}

}

string Computer::getBet() {
	if (!betsubmitted) {
		randnum(bet);
		betsubmitted = true;
	}
	return bet;
}

string Computer::makeMove(void) {
	
}
void Computer::youLost(void) {
	
}

void Computer::youMightLose(void) {
	
}

string Computer::getName(void) {
	
}
