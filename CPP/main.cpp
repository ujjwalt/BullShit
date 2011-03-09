#import <iostream>
#import "main.h"
using namespace std;

extern const int numLength;

int main (int argc, char * const argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    return 0;
}

void randnum(char a[numLength+1]) {
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

bool validate(char a[numLength+1]) {
	int i, j;
	if (a[0] == '0') {
		return NO;
	}
	for (i = 0; i < numLength-1; i++) {
		for (j = i+1; j < numLength; j++) {
			if (a[i] == a[j] || !isdigit(a[i])) {
				return NO;
			}
		}
	}
	return YES;
}