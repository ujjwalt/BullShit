/*
 *  Refree.h
 *  Cows&Bulls
 *
 *  Created by Ujjwal Thaakar on 01/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import "main.h"
#import "Player.h"

extern const int numLength;

class Refree : public Player {
	char userNumber[numLength+1], computerNumber[numLength+1];
	bool gameOver;
public:
	void startGame();
	void analyse(char[numLength+1], char[numLength+1], int*, int*);
	void printTable(const char [numLength+1], const int, const int, const bool);
	bool validate(char a[numLength+1]);
};
