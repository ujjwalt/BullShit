/*
 *  Computer.h
 *  BullShit
 *
 *  Created by Ujjwal Thaakar on 09/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import <string>
#import "Player.h"

using namespace std;

class Computer : public virtual Player {
	static string *names;
	static int count;
public:
	Computer(void);
	string getBet(void);
	string makeMove(void);
	void youLost(void);
	void youMightLose(void);
	string getName(void);
	
};