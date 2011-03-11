/*
 *  Player.h
 *  BullShit
 *
 *  Created by Ujjwal Thaakar on 09/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import <iostream>
#import <string>

using namespace std;

class Player {
private:
	virtual void youWon(void);
	virtual void youLost(void);
	
protected:
	string name, bet;
	bool betsubmitted;
	
public:
	virtual string getBet(void);
	virtual string makeMove(void);
	virtual void youMightLose(void);
	virtual void youMightWin(void);
	string getName(void);
};
