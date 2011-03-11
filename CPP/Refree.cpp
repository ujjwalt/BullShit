/*
 *  Refree.cpp
 *  Cows&Bulls
 *
 *  Created by Ujjwal Thaakar on 01/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */
#import "Refree.h"
#import "Computer.h"
#import "User.h"
#import "main.h"

void Refree::startGame() {
		// Holds the last move made
	string move;
	
		// Check wether the game has started - if not then take in the type of Players
	if (!gameStarted) {
		string options;
		cout << endl(cout) << "Specify the Galdiators: PlayerType vs PlayerType\nReplace PlayerType by H/h for human and C/c for computer";
		do {
			cin >> options;
			if (options.length() != 6) {
				cout << endl(cout) << "Invalid options specified - try again...";
			}
		} while (options.length() != 6);
		
			// process the options
		for (int i = 0; i < 6; i += 5) {
			switch (tolower(options.at(i))) {
				case 'h':
					switch (i) {
						case 0:
							player1 = new User();
							player1->getName();
							break;
						case 5:
							player2 = new User();
							player2->getName();
							break;
					}
				case 'c':
					switch (i) {
						case 0:
							player1 = new Computer();
							player1->getName();
							break;
							
						case 5:
							player2 = new Computer();
							player2->getName();
							break;
					}
					break;
					
				default:
					cout << endl(cout) << "Invalid input format - exiting...";
					exit(0);
					break;
			}
		}
	}
	
	player1Bet = player1->getBet();
	player2Bet = player2->getBet();
	
	gameOver = false;
	
	int chance = 0, cows, bulls;
	while (!gameOver) {
		if (chance++ % 2 == 0) {
			move = player1->makeMove();
			analyse(move, player2Bet, cows, bulls);
			printTable(move, cows, bulls, player1);
		} else {
			chance--;
			move = player2->makeMove();
			analyse(move, player1Bet, cows, bulls);
			printTable(move, cows, bulls, player2);
		}
	}
}

void Refree::analyse(string input, string secret, int &cows, int &bulls) {
	cows = bulls = 0;
	for (int i = 0; i < secret.length(); i++) {
		for (int j = 0; j < input.length(); j++) {
			if (secret[i] == input[j]) {
				if (i == j) {
					bulls++;
					break;
				} else {
					cows++;	
					break;
				}
			}
		}
	}
}

void Refree::printTable(const string move, const int cows, const int bulls, const Player *p) {
	static bool finished;
	if (p == player2) {
		for (int i = 0; i , i < TABLE_DIFF; i++) {
			cout << ' ';
		}
		cout << move;
		for (int i = 0; i < 12; i++) {
			cout << ' ';
		}
		cout << "\t\t" << cows << ' ' << bulls;
	} else {
		cout << move;
		for (int i = 0; i < numLength+INITIAL_PAD; i++) {
			cout << ' ';
		}
		cout << "\t\t" << cows << ' ' << bulls;
	}
	
	if (bulls == numLength) {
		if (p == player1) {
			
			}
	}
}