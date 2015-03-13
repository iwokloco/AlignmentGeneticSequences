#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

#define DIAGONAL 1
#define LEFT	 2
#define UP 	 3


void error(char *m);
char* loadSequence(char* argv[], int index);
void global(int showMatrix, char* seqA, char* seqB, int n, int m, char* seqResA, char* seqResB, char* seqAst, int ID, int MIS, int GAP, int* score);
void inverseSeq(char* seq);
void match(char* seqA, char* seqB, char* match);
void readMatrix(char* nameFileMatrix, int* seqSubMatrix, int* sizeSubMatrix, int* sizeXSubMatrix, int* sizeYSubMatrix, char* letras);
void outHTML(char* nameHTML, int score, int length, char* seqA, char* seqB, char* seqRA, char* seqRB, char* seqAst, char* aligment, int match,int mismatch,int gap);
int scores(char* seqA, char* seqB, char* letras, int* subMatrix, int GAP);
int search(char c, char* letras);
