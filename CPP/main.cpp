#import <iostream>
#import <stdlib.h>
#import <time.h>
#import "main.h"
#import "Refree.h"

extern const int numLength;

int main (int argc, char * const argv[]) {
    Refree richard;
	richard.startGame();
    return 0;
}

void randnum(string &a) {
		//Generate a random number with unique digits
	register int i;
	srandom(time(NULL));
	do {
		for (i = 0; i < numLength;i++)
			a[i] = '0'+ (random()%9+(i==0));
	}
	while (!validate(a));
	a[numLength] = '\0';
}

bool validate(string a) {
	int i, j;
	if (a[0] == '0') {
		return false;
	}
	for (i = 0; i < numLength-1; i++) {
		for (j = i+1; j < numLength; j++) {
			if (a[i] == a[j] || !isdigit(a[i])) {
				return false;
			}
		}
	}
	return true;
}