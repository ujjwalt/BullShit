/*
 *  Refree.h
 *  Cows&Bulls
 *
 *  Created by Ujjwal Thaakar on 01/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import <string>
#import "Player.h"

#define TABLE_DIFF (20)
#define INITIAL_PAD (10)

using namespace std;

class Refree {
	string player1Bet, player2Bet;
	bool gameOver, gameStarted;
	Player *player1, *player2;
	
	void setUpTable(void);
public:
	void startGame(void);
	void analyse(string input, string secret, int &cows, int &bulls);
	void printTable(const string move, const int cows, const int bulls, const Player *p);
};
