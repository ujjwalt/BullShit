/*
 *  main.h
 *  Cows&Bulls
 *
 *  Created by Ujjwal Thaakar on 04/03/11.
 *  Copyright 2011 Nirma University. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define NUM (4)
#define MAX (NUM+1)
#define MAX_NAME (10)
#define TABLE_DIFF (15)
#define NO (0)
#define YES (1)
#define UNCONFIRMED (666)
#define BETA (1)
#define BETA_WITH_ALPHA_UNCONFIRMED (-1)
#define WILDCARD ('*')

typedef int bool;

void yourchance();
void takenum(char[MAX]);
void analyse(char[MAX], char[MAX], int*, int*);
void printTable(const char [MAX], const int, const int, const bool);
bool validate(char a[MAX]);

void compchance(void);
void bothConfirmed(void);
void theOtherCase(void);
void bothUnconfirmed(void);
void rearrange(void);
void randnum(char[MAX]);
void setBeta(int);
void permutate(void);
void post(char a[]);
void merge(void);
void positionDeduce(void);
void deduce(void);
void intermediateDeduction(void);
void theCaseThree(void);
void analysedDeduction(void);
void theCaseFour(void);
void shiftLeft(char v[],int go,int n);
void swap(char v[],int i,int j);
void permute(char v[], const int start, const int n);


char pop(void);
void push(char c);
bool betaUnconfirmed(void);
