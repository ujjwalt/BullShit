/* 
 *  main.h
 *  Cows&Bulls
 *
 *  Created by Ujjwal Thaakar on 04/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#include "main.h"

char cnum[MAX], unum[MAX];
int lpadding;

int main (int argc, const char * argv[]) {
		// Declare variables
	int i;
    char uname[MAX_NAME];
	
		// Randomly initalize the number thrown by the computer ;)
	randnum(cnum);	
		// Ask the user his name and number?
	printf("Whats your name hobbit ? Just your name !\n");
		//strcpy(uname, "JFK");
	scanf("%s", uname);
	lpadding = strlen(uname);
	printf("Enter your bet !");
	takenum(unum);
	
		// Print the table headers
	printf("\n\n %s\t\tcows  bulls", uname);
	for (i = 0; i < TABLE_DIFF; i++) {
		putchar(' ');
	}
	printf("The Godfather :(\t\tcows  bulls\n");
	
	while (YES) {
		static int i = 1;
		if (i%2 != 0) {
			yourchance();
			i++;
		} else {
			compchance();
			i--;
		}
	}
    return 0;
}

void analyse(char a[MAX], char b[MAX], int *cows, int *bulls) {
	*cows = *bulls = 0;
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			if (b[i] == a[j]) {
				if (i == j) {
					(*bulls)++;
					break;
				} else {
					(*cows)++;	
					break;
				}
			}
		}
	}
}

void printTable(const char a[MAX], const int cows, const int bulls, const bool bycomp) {
	static bool finished;
	if (bycomp) {
		for (int i = 0; i , i < TABLE_DIFF+6; i++) {
			putchar(' ');
		}
		printf("%s", a);
		for (int i = 0; i < 12; i++) {
			putchar(' ');
		}
		printf("\t\t%d     %d", cows, bulls);
	} else {
		printf("%s", a);
		for (int i = 0; i < lpadding-NUM; i++) {
			putchar(' ');
		}
		printf("\t\t%d     %d", cows, bulls);
	}
	
	if (bulls == NUM) {
		if (bycomp) {
			if (finished) {
				printf("\n\nNo one beats the Godfather ! - its a draw !");
			} else {
				printf("\n\nNo one beats the Godfather !");
			}
			printf("\n\ncomputer generated no. = %s", cnum);
			exit(0);
		} else {
			if (!finished) {
				printf("\n\nCongrats you won - you beat the Godfather lol...wait a sec, lets give him one chance more !\n");
				finished = YES;
				compchance();
			}
		}
	} else if (finished) {
		printf("\n\nThe Godfather accepts the defeat !");
		printf("\n\ncomputer generated no. = %s", cnum);
		exit(0);
	}
}

void takenum(char a[MAX]) {
	int len;
	do{
		
		scanf("%s", a);
		len = strlen(a);
	}
	while (!validate(a) || len != NUM);
}

void yourchance() {
	static int cows, bulls;
	static char a[MAX];
	printf("\n>");
	strcpy(a, "1234");
		//takenum(a);
	analyse(a, cnum, &cows, &bulls);
	printTable(a, cows, bulls, NO);
}

bool validate(char a[MAX]) {
	int i, j;
	if (a[0] == '0') {
		return NO;
	}
	for (i = 0; i < NUM-1; i++) {
		for (j = i+1; j < NUM; j++) {
			if (a[i] == a[j] || !isdigit(a[i])) {
				return NO;
			}
		}
	}
	return YES;
}

/* *************************************************************************************************************************/

#pragma mark Computer

int cows1, cows2, bulls1, bulls2, previousCows, previousBulls, cows, bulls, pos;
char firstNum[MAX], secondNum[MAX], primary[MAX], secondary[MAX], alpha, beta;
bool found = NO, digitsConfirmed = NO;
int nums[10], alphaContenderCount = 0;
char alphaContenders[6];
char posns[MAX];

void compchance() {
	static int chance;
	chance++;
	
		// if all four digits have been confirmed then rearrange them
	if (digitsConfirmed) {
		permutate();
		return;
	}
	
	if (chance == 1) { 
		/* If this is the first chance then generate a random num and assign it to firstNum
		 check for the cows and bulls to see if you get any confirmation ! */
		for (int i = 0; i < 10; i++) {
			nums[i] = UNCONFIRMED;
			if (i < NUM) {
				posns[i] = WILDCARD;
			}
		}
		randnum(firstNum);
		post(firstNum);
		cows1 = cows;
		bulls1 = bulls;
		return;
	} else if (chance == 2) { 
		/* If this is the second chance then generate a random num and assign it to secondNum 
		 check for the cows and bulls to see if you get any confirmation !*/
		randnum(secondNum);
		srandom(time(NULL));
		for (int i = 0; i < NUM; i++) {
			for (int j = 0; j < NUM; j++) {
				if (secondNum[i] == firstNum[j]) {
					do {
						secondNum[i] = '0' + (random()%9+(i==0));
					} while (!validate(secondNum));
					i = -1;
					break;
				}
			}
		}
		post(secondNum);
		cows2 = cows;
		bulls2 = bulls;
		return;
	} else if (chance == 3) {
			// Determine alpha and beta
		for (int i = 0, step = 1; i < 10; i++) {
			for (int j = 0; j < NUM; j++) {
				if (i == (firstNum[j]-'0') || i == (secondNum[j]-'0')) {
					found = YES;
				}
			}
			if (!found) {
				if (step == 1) {
					alpha = i+'0';
					step++;
				} else if (step == 2) {
					beta = i+'0';
					break;
				}
			} else {
				found = NO;
			}
		}
		
			// alpha should not be '0' since it is to be placed first - just  a silly precaution
		if (alpha == '0') {
			char t = beta;
			beta = alpha;
			alpha = t;
		}
		
			// Determine primary and secondary on the basis of who scored more
		if (cows1+bulls1 >= cows2+bulls2) {
			strcpy(primary, firstNum);
			strcpy(secondary, secondNum);
			cows = cows1;
			bulls = bulls1;
		} else {
			strcpy(primary, secondNum);
			strcpy(secondary, firstNum);
			cows = cows2;
			bulls = bulls2;
		}
		
			// Prepare the alphaContenders stack by inputting secondary's digits
		for (int i = 0; i < NUM; i++) {
			push(secondary[i]);
		}
		
			// Determine the status of alpha and beta on the basis of initaly random inputs
		switch (cows1+bulls1+cows2+bulls2) {
			case 4:
				nums[alpha-'0'] = nums[beta-'0'] = NO;
				theOtherCase();
				break;
			case 2:
				nums[alpha-'0'] = nums[beta-'0'] = YES;
				theOtherCase();
				break;
			default:
				bothUnconfirmed();
				break;
		}
	} else {
			// Deduce the statuse
		deduce();
			// Post the new primary
		post(primary);
	}
}

/* ********************************************************************************************/

void theOtherCase(void) {
		// Set beta as a contender for alpha
	push(beta);
		// Set beta
	setBeta(BETA);
		// Replace beta in primary by alpha
	primary[pos] = alpha;
		// Post primary
	post(primary);
}

/* ********************************************************************************************/

void bothUnconfirmed(void) {
		// Save the value replaced in tempBeta :)
	char tempBeta = primary[0];
		// Save the cows and bulls of the original number;
	const int tempPrevCows = cows, tempPrevBulls = bulls;
	
	for (int i = 0; i < NUM; i++) {
			// If alpha is wrong then replace the value replaced again - provided its the not the first chance
		if (i > 0 && nums[alpha-'0'] != YES) {
			primary[pos] = tempBeta;
				// Restore the cows and bulls as if the number wasn't modified at all ;)
			cows = tempPrevCows;
			bulls = tempPrevBulls;
		}
		
			// If state of alpha is determined then break out
		if (nums[alpha-'0'] != UNCONFIRMED)
			break;
		
			// Save the number being replaced
		tempBeta = primary[i];
			// Set position variable pos to i
		pos = i;
		primary[pos] = alpha;
		post(primary);
		
			// If cows increase then alpha exits and beta doesn't else the opposite is true
		if (cows > tempPrevCows) {
			nums[alpha-'0'] = YES;
			nums[tempBeta-'0'] = NO;
		} else if (cows < tempPrevCows) {
			nums[alpha-'0'] = NO;
			nums[tempBeta-'0'] = YES;
			
		}
		
			// If bulls increase then not only is alpha confirmed but so is its position
		if (bulls > tempPrevBulls) {
			nums[alpha-'0'] = YES;
			posns[i] = alpha;
			/* If bulls have increased but there is no effect on the cows => tempBeta had no effect on cows
			 and thus was wrong*/
			if (cows == tempPrevCows) {
				nums[tempBeta-'0'] = NO;
			}
		} else if (bulls < tempPrevBulls) {
				// Since the bulls decreased therefore tempBeta is true and so is its position
			nums[tempBeta-'0'] = YES;
			posns[i] = tempBeta;
			if (cows == tempPrevBulls) {
				/* If bulls have decreased but there is no effect on the cows => alpha had no effect on cows
				 and thus was wrong*/
				nums[alpha-'0'] = NO;
			}
		}
			// Give the poor user a try - he's gonna lose anyway ;)
		yourchance();
	}
	
		// Finally out ... phew !
	
		// If alpha is wrong then beta is right and vice-versa
	if (nums[beta-'0'] = !nums[alpha-'0']) {
			// If beta is right then exhange values with alpah thus making beta -> alpha
		char c = alpha;
		alpha = beta;
		beta = c;
			// Since alpha is wrong thus all digits it could not evaluate were wrong too !
		for (int i = 0; i < pos; i++) {
			nums[primary[i]-'0'] = NO;
		}
	} else {
			// Since alpha is right thus all digits it could not evaluate were wrong too !
		for (int i = 0; i < pos; i++) {
			nums[primary[i]-'0'] = YES;
		}
			// Make tempBeta -> alpha
		alpha = tempBeta;
	}
	
		// Make the present beta a contender for alpha
	push(beta);
	
		// Determine a new beta which is unconfirmed
	for (int i = 0; i < NUM; i++) {
		if (nums[primary[i]-'0'] == UNCONFIRMED) {
			if (alpha=='0' && i==0) {
				continue;
			}
			beta = primary[i];
			pos = i;
			found = YES;
			break;
		}
	}
	
		// If no unconfirmed beta exists then set new alpha and beta as an random digit from primary
	if (!found) {
		alpha = pop();
		beta = primary[random()%3+(alpha=='0')]; // If alpha is '0' then the position should not be 0
	}
	
	primary[pos] = alpha;
	post(primary);
}

/* ********************************************************************************************/

void intermediateDeduction() {
		// Make intermediate deductions based on the digits of primary and their statuses
	char tobeConfirmed[NUM];
	int noCount = 0, c = 0;
	for (int i = 0, count = 0; i < 10 && count < MAX; i++) {
			// If the digit is true then increase the count
		if (nums[i] == YES) {
			count++;
				//printf("\n%d confirmed\n", i);
		}
		
			// If the digit is false then increase the "NO" count else add it to tobeConfirmed[]
		if (nums[i] == NO) 
			noCount++;
		else
			tobeConfirmed[c++] = i+'0';
		
		
		
		if (count == 4) {
				// Number of true digits is 4 so confirm digits, print them and permuatate the positions
			digitsConfirmed = YES;
			return;
		}
	}
	if (noCount==6) {
		/* If the number of digits which are false is 6 then the remaining 4 contained within b[]
		 must be true*/
		for (int i = 0; i < c; i++) {
			nums[tobeConfirmed[i]-'0'] = YES;
				//printf("Confirming %c\n", tobeConfirmed[i]);
		}
		digitsConfirmed = YES;
			//printf("\nfound intermediately\n");
		return;
	}
}

void analysedDeduction() {
		// if the number of numbers which are false = NUM - (cows+bulls) then the rest are true and vice-versa
	int notYesCount = 0, notNoCount = 0, yesCount = 0;
	int noCount = 0;
	char notYesStack[NUM];
	char notNoStack[NUM];
	for (int i = 0; i < NUM; i++) {
		if (nums[primary[i]-'0'] == NO) {
			noCount++;
		} else {
			notNoStack[notNoCount++] = primary[i];
		}
		if (nums[primary[i]-'0'] == YES) {
			yesCount++;
		} else {
			notYesStack[notYesCount++] = primary[i];
		}
	}
	
	if (yesCount == cows+bulls) {
		for (int i = 0; i < notYesCount; i++) {
			nums[notYesStack[i]-'0'] = NO;
		}
	}
	if (noCount == NUM-(cows+bulls)) {
		for (int i = 0; i < notNoCount; i++) {
			nums[notNoStack[i]-'0'] = YES;
				//printf("Confirming %c\n", notNoStack[i]-'0');
		}
	}
}
void deduce() {
	/* Make deductions about beta like Sherlock Homes based on the status of alpha and the cows and bulls obtained
	 and the cows and bulls obtained previously*/
	
		// If alpha is true follow the following deduction criteria
	if (nums[alpha-'0'] == YES) {
			// If cows increase then beta is false true
		if (cows > previousCows) {
			nums[beta-'0'] = NO;
		} else {
			nums[beta-'0'] = YES;
		}
			// If bulls increase the position of alpha is confirmed
		if (bulls > previousBulls) {
			posns[pos]=alpha;
				// If beta had no effect on cows then it is wrong
			if (cows == previousCows) {
				nums[beta-'0'] = NO;
			}
		} else if (bulls < previousBulls) {
				// As bulls have decreased thus beta was not only true but also at the right position
			nums[beta-'0'] = YES;
			posns[pos] = beta;
		}
	}
		// If alpha is false follow the following deduction criteria
	else if (nums[alpha-'0'] == NO) {
			// If cows decrease then beta is true else false
		if (cows < previousCows) {
			nums[beta-'0'] = YES;
		} else {
			nums[beta-'0'] = NO;
		}
		
			// If bulls decrease the position of beta is confirmed and so is its status
		if (bulls < previousBulls) {
			nums[beta-'0'] = YES;
			posns[pos] = beta;
		}
	} 
	
		// If alpha is unconfirmed follow the following deduction criteria
	else if (nums[alpha-'0'] == UNCONFIRMED) {
		
		/* Based on the status of beta follow the following deduction criteria - reverse to the one followed above !
		 REVERSE ENGINEERING BABY - REVERSE ENGINEERING ! */
		if (nums[beta-'0'] == YES) {
			if (cows < previousCows) {
				nums[alpha-'0'] = NO;
			} else {
				nums[alpha-'0'] = YES;
			}
			if (bulls > previousBulls) {
				nums[alpha-'0'] = YES;
				posns[pos] = alpha;
			} else if (bulls < previousBulls) {
				if (cows == previousCows) {
					nums[alpha-'0'] = NO;
				}
				posns[pos]=beta;
			}
			
		} else if (nums[beta-'0'] == NO){
			if (cows > previousCows) {
				nums[alpha-'0'] = YES;
			} else {
				nums[alpha-'0'] = NO;
			}
			if (bulls > previousBulls) {
				nums[alpha-'0'] = YES;
				posns[pos]=alpha;
			}
		} else {
				// Same as that followed in bothUnconfirmed()
			if (cows > previousCows) {
				nums[alpha-'0'] = YES;
				nums[beta-'0'] = NO;
			} else if (cows < previousCows) {
				nums[alpha-'0'] = NO;
				nums[beta-'0'] = YES;
				
			}
			
			if (bulls > previousCows) {
				nums[alpha-'0'] = YES;
				posns[pos] = alpha;
				if (cows == previousCows) {
					nums[beta-'0'] = NO;
				}
			} else if (bulls < previousBulls) {
				nums[beta-'0'] = YES;
				posns[pos] = beta;
				if (cows == previousBulls) {
					nums[alpha-'0'] = NO;
				}
			}
			
				// If alpha is still unconfirmed then change it
			if (nums[alpha-'0'] == UNCONFIRMED) {
				cows = previousCows;
				bulls = previousBulls;
				char t = alpha;
				alpha = pop();
					// Push back th alpha which could not be evaulated !
				push(t);
				primary[pos] = alpha;
				return;
			}
		}
	}
	
		// Make changes to primary
	if (betaUnconfirmed()) {
		alpha = beta;
		setBeta(BETA);
	} else {
		alpha = pop();
		setBeta(BETA_WITH_ALPHA_UNCONFIRMED);
	}
	if (pos == 0 && alpha == '0') {
		char t = alpha;
		alpha = pop();
		push(t);
	}			
	primary[pos] = alpha;
	
		// Make intermediate deductions based on statues
	intermediateDeduction();
}

/* ********************************************************************************************/

void setBeta(int var) {
		// Set the value of beta based on whether alpha is confirmed or not
	int i;
	
	srandom(time(NULL));
	if (var == BETA) {
			// Alpha is determined so get a unconfirmed beta
		for (i = 0; i < NUM; i++) {
			if (nums[primary[i]-'0'] == UNCONFIRMED) {
				if (nums[primary[i]-'0'] == beta) {
						// Don't return the same beta as before - another silly precaution :D
					continue;
				}
				pos = i;
					// Set beta
				beta = primary[pos];
				break;
			}
		}
	} else {
			// Alpha is undetermined so get a determined beta
		char tempBeta;
		do {
			i = random()%3;
			tempBeta = primary[i];
		} while (tempBeta == beta || nums[tempBeta-'0'] == UNCONFIRMED);
		pos = i;
		beta = primary[pos];
	}
}

void post(char a[]) {
	previousCows = cows;
	previousBulls = bulls;
	a[NUM] = '\0';
	if (!validate(a)) {
		printf("\n\nInvalid Input - %s\n\n", a);
	}
	analyse(a, unum, &cows, &bulls);
	printTable(a, cows, bulls, YES);
	
	if ((cows+bulls) == 4 && !digitsConfirmed) {
			// Set all digits as true and rest as false
		digitsConfirmed = YES;
		for (int i = 0; i < 10; i++) {
			nums[i] = NO;
		}
		for (int i = 0; i < NUM; i++) {
			nums[a[i]-'0'] = YES;
		}
	} else if ((cows+bulls) == 0) {
			// Set all digits as false
		for (int i = 0; i < NUM; i++) {
			nums[a[i]-'0'] = NO;
		}
	}
	
	if (!digitsConfirmed) {
		analysedDeduction();
	}
}

void randnum(char a[MAX]) {
		//Generate a random number with unique digits
	register int i;
	srandom(time(NULL));
	do {
		for (i = 0; i < NUM;i++)
			a[i] = '0'+ (random()%9+(i==0));
	}
	while (!validate(a));
	a[NUM] = '\0';
}

char posNotConfirmed[NUM]; // Contains digits in correct order whose position has not been determined
int positions_confirmed = 0; // Number of positions confirmed

void rearrange() {
		// Set found to NO
	found = NO;
	
	/*Run a loop to determine if there is any digit in primary which is not right ? If yes then substitute it with
	 right digit*/
	for (int i = 0; i < NUM; i++) {
		if (nums[primary[i]-'0'] != YES) {
			for (int j = 0; j < 10; j++) {
				if (nums[j] == YES) {
						//printf("\n=>%d", j);
					for (int k = 0; k < NUM; k++) {
						if (j+'0' == primary[k]) {
							found = YES;
							break;
						}
					}
					if (!found) {
						if (j==0 && i==0) {
							continue;
						} else {
							primary[i] = j+'0';
							break;
						}
					} else {
						found = NO;
					}
				}
				
			}
		}
	}
		//printf("\nprimary after replacing bad digits = %s\n", primary);
		// Set count of digits whose position is not confirmed to 0
	int posNotConfirmedCount = 0;
	char s[MAX];
	strcpy(s, posns);
	for (int i = 0; i < NUM; i++) {
		if (s[i] != WILDCARD) {
				// If a digit is confirmed at i position then increase positons confirmed count
			positions_confirmed++;
		}
	}
	
		// If any digit of primary does not exist in s[] then its positon is not confirmed
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < NUM; j++) {
			if (s[j] == primary[i]) {
				found = YES;
			}
		}
		if (!found) {
			for (int k = 0; k < NUM; k++) {
					// Add the digit with unconfirmed position to s[] at the next empty slot
				if (s[k] == WILDCARD) {
					posNotConfirmed[posNotConfirmedCount++] = s[k] = primary[i];
					break;
				}
			}
		}
		found = NO;
	}
	
	/* Check wether first position is unconfirmed and stack of unconfirmed digits starts with '0'
	 since the 0 will be placed at first palce*/
	if (posns[0] == WILDCARD && posNotConfirmed[0] == '0') {
		char temp = posNotConfirmed[0];
		posNotConfirmed[0] = posNotConfirmed[1];
		posNotConfirmed[1] = temp;
		merge();
	}
		// Pad the ending of s[] with '\0' for [roper copying in strcpy()
	s[NUM] = '\0';
		// Copy the prepared s[] to primary
	strcpy(primary, s);
}

void permutate(void) {
	static int chance;
	chance++;
	
	if (chance == 1) {
			// On first chance rearrange primary to bring back the confirmed digits
		char a[MAX];
		strcpy(a, primary);
		rearrange();
		if (!strcmp(a, primary)) {
			positionDeduce();
		}
	} else {
		positionDeduce();
	}
	//printf("I the permutate called\n");
	post(primary);
}

void merge() {
		// Merge the new order of unconfirmed positions and confirmed positions
	int count = 0;
	strcpy(primary, posns);
	for (int i = 0; i < NUM; i++) {
		if (posns[i] == WILDCARD) {
			primary[i] = posNotConfirmed[count++];
		}
	}
}

void positionDeduce() {
	switch (positions_confirmed) {
		case 2:
			permute(posNotConfirmed, 0, 2);
			break;
			
		case 1:
			theCaseThree();
			break;
			
		case 0:
			theCaseFour();
			break;
	}
}

void theCaseFour() {
	static int chance, firstBull;
	chance++;
	
	if (chance == 1) {
		firstBull = bulls;
	}
	
	if (firstBull == 2) {
			// Only any two values need to be interhcanged so its better to use this manual set than permute them - 4C2
		switch (chance) {
			case 1:
				swap(posNotConfirmed, 0, 1);
				break;
				
			case 2:
				swap(posNotConfirmed, 0, 1);
				
				swap(posNotConfirmed, 2, 3);
				break;
				
			case 3:
				swap(posNotConfirmed, 2, 3);
				
				swap(posNotConfirmed, 0, 2);
				break;
				
			case 4:
				swap(posNotConfirmed, 0, 2);
				
				swap(posNotConfirmed, 0, 3);
				break;
				
			case 5:
				swap(posNotConfirmed, 0, 3);
				
				swap(posNotConfirmed, 1, 2);
				break;
				
			case 6:
				swap(posNotConfirmed, 0, 3);
				
				swap(posNotConfirmed, 1, 3);
				break;
		}
		merge();
	} else {
		permute(posNotConfirmed, 0, 4);
	}
}
char ex;
bool exSet = NO;
void permute(char v[], const int start, const int n) {
	if (start<n)
    {
        int i,j;
        for(i=n-2; i>=start; i--)
        {
            for(j=i+1; j<n; j++)
            {
                swap(v,i,j);
                permute(v,i+1,n);
            }
            shiftLeft(v,i,n);
        }
    }
	
	merge();
	if (validate(primary) && start!=0) {
		if (exSet == YES && primary[0] == ex) {
			return;
		}
		post(primary);
		if (bulls == 0) {
			ex = primary[0];
			exSet = YES;
		}
		yourchance();
	}
}

/*==============================
 Function swap
 ==============================*/
void swap(char v[],int i,int j)
{
    char t = v[i];
    v[i] = v[j];
    v[j] = t;
}

/*===========================
 Function shift left
 ===========================*/
void shiftLeft(char v[],int go,int n)
{
    int tmp = v[go];
    for (int i=go; i<n-1; i++)
    {
        v[i] = v[i+1];
    }
    v[n-1] = tmp;
}

void theCaseThree() {
		//permute(posNotConfirmed, 0, 3);
		//return;
	static int chance;
	static int firstBull;
	static char a, b, c;
	chance++;
	
	if (chance == 1) {
		a = posNotConfirmed[0];
		b = posNotConfirmed[1];
		c = posNotConfirmed[2];
		firstBull = bulls;
	}
	if (firstBull == 1) {
		switch (chance) {
			case 1:
					// Swap the digits at second position and 3rd positon => b and c
					// *Note - No one touches the guy at position no.1 - he's the King
				printf("\nThe case 3;) = %s\n", primary);
				posNotConfirmed[1] = c;
				posNotConfirmed[2] = b;
				break;
				
			case 2:
					// Obviosuly the bulls increase by 1 - check because of whom ?
					// Swap c and a
				posNotConfirmed[1] = a;
				posNotConfirmed[0] = c;
				break;
				
			case 3:
					// If the bulls decrease then the previous increase was due to c else due to b
				if (bulls < previousBulls) {
					posNotConfirmed[1] = c;
					posNotConfirmed[0] = b;
					posNotConfirmed[2] = a;
				} else {
					posNotConfirmed[0] = c;
					posNotConfirmed[1] = a;
				}
				
				break;
		}
		merge();
	} else {
		permute(posNotConfirmed, 0, 3);
	}

}

char pop() {
	static int chance;
	chance++;
	int i = alphaContenderCount;
	static char prev;
	char c;
	
	if (chance <= 4 && alphaContenderCount > 1) {
		srandom(time(NULL));
		do {
			i = random()%(alphaContenderCount);
			c = alphaContenders[i];
		} while (c == prev);
	} else {
		c = alphaContenders[i];
	}
	prev = c;
	for (int j = i; j < alphaContenderCount; j++) {
		alphaContenders[j] = alphaContenders[j+1];
	}
	alphaContenderCount--;
	return c;
}

void push(char c) {
	for (int i = 0; i < alphaContenderCount; i++) {
		if (alphaContenders[i] == c) {
			return;
		}
	}
	alphaContenders[alphaContenderCount++] = c;
}

bool betaUnconfirmed(void) {
	for (int i = 0; i < NUM; i++) {
		if (nums[primary[i]-'0'] == UNCONFIRMED) {
			return YES;
		}
	}
	return NO;
}
