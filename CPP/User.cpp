/*
 *  User.cpp
 *  BullShit
 *
 *  Created by Ujjwal Thaakar on 09/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import "User.h"
#import "main.h"
#import "Player.h"

string User::getBet() {
	if (!betsubmitted) {
		do {
			getline(cin, bet, '\n');
			if (bet.length() != 4) {
				cout << endl << "Bet should be only 4 digits long - no longer - no shorter !";
			}
		} while (!validate(bet));
		betsubmitted = true;
	}
	
	return bet;
}

string User::makeMove() {
	do {
		cin >> move;
	} while (move.length() != numLength);
	return move;
}

string User::getName() {
	cout << endl(cout) << "Whats's your name hobbit ?" << endl;
	return Player::getName();
}

void User::youLost(void) {
	cout << endl(cout) << name << " accepts the defeat";
}

void User::youMightLose(void) {
	static bool lost = false;
	if (!lost) {
		cout << endl(cout) << name << ": Give me another chance...wait a sec";
	} else {
		youLost();
	}
}

string User::getName(void){
	return name;
}
