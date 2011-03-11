/*
 *  User.h
 *  BullShit
 *
 *  Created by Ujjwal Thaakar on 09/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#import "Player.h"

class User : public virtual Player {
private:
	string move;
	
	void youLost(void);
	void youWin(void);
	
public:
	string getBet(void);
	string makeMove(void);
	void youMightLose(void);
	string getName(void);
};