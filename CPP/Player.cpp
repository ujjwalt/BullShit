/*
 *  Player.cpp
 *  BullShit
 *
 *  Created by Ujjwal Thaakar on 09/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import "Player.h"

string Player::getName() {
	if (name.empty()) {
		getline(cin, name, '\n');
	}
	return name;
}

string Player::getBet() {
	cout << endl << "BET was not sET - I was a poET and didn;t even know IT !";
	return NULL;
}

string Player::makeMove() {
	cout << endl << "Make move my foot - lets Salsa";
	return NULL;
}

void youLost(void) {
	cout << endl(cout) << "Happens to the best of us !";
}

void youMightLose(void) {
	cout << endl(cout) << "Winning and Losing is a part of life !";
}

void youMightWin(void) {
	youMightLose();
}
