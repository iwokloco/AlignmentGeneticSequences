#include "alineator.h"

//Funció que calcula l'alineament òptim donades dues seqüències i si s'indica pinta la matriu de similaritat.
void global(int showMatrix, char* seqA, char* seqB, int n, int m, char* seqResA, char* seqResB, char* seqAst, int ID, int MIS, int GAP, int* score)
{
	int matrix[n+1][m+1];			//Matriu de puntuacions del pas 1 de l'algorisme.
	int matrix2[n+1][m+1];			//Matriu de puntuacions del pas 2 de l'algorisme.
	int matrixOrientation[n+1][m+1];	//Matriu que serveix per reconstruir el camí al pas 3 de l'algorisme.
	int caseA,caseB,caseC,caseD;
	int i, j, indexSeq, orientation;	
	i=0;j=0;

//Construcció del primer array de puntuacions.
	while(i<(n+1))
	{
		matrix[i][0]=MIS;
		i++;
	}
	while(j<(m+1))
	{
		matrix[0][j]=MIS;
		j++;
	}
	for(j=0; j<strlen(seqB);j++)
	{
		for(i=0; i<strlen(seqA);i++)
		{
			if(*(seqB+j)==*(seqA+i))
			{
				matrix[i+1][j+1]=ID;	//MATCH
			}
			else
			{
				matrix[i+1][j+1]=MIS;	//MISMATCH
			}
		}	
	}
	
//Construcció del segon array de puntuacions, on cada Si,j rep una puntuació definida com el màxim entre 3 regles.	
	//Per convenció la cel·la S(0,0) al no tenir més cel·les amunt o a l'esquerra se li assigna la puntuació 0.
	matrix2[0][0]=MIS;
	matrixOrientation[0][0]=DIAGONAL;
	//En el cas de la cel·la S(0,1), només es pot escollir l'opció c (cap amunt) així: S(0,1)=-1
	matrix2[0][1]=GAP;
	matrixOrientation[0][1]=UP;
	//En el cas de la cel·la S(1,0), només es pot escollir l'opció b (cap a l'esquerra) així: S(1,0)=-1
	matrix2[1][0]=GAP;
	matrixOrientation[1][0]=LEFT;
	//Per la cel·la S(1,1), s'ha d'escollir el màxim d'entre les 3 opcions, així S(1,1)=0
	matrix2[1][1]=MIS;
	matrixOrientation[1][1]=DIAGONAL;

	for(j=0;j<(m+1);j++)
	{
		for(i=0;i<(n+1);i++)
		{
			if(!((i==0 && j==0 )||(i==0 && j==1 )||(i==1 && j==0 )||(i==1 && j==1 )))
			{
				if((i==0))
				{
					caseC = matrix2[i][j-1]+GAP;
					matrix2[i][j] = caseC;
					matrixOrientation[i][j]=UP;
				}
				if((j==0))
				{
					caseB = matrix2[i-1][j]+GAP;
					matrix2[i][j] = caseB;
					matrixOrientation[i][j]=LEFT;
				}
				if(j!=0 && i!=0)
				{
					caseA = matrix2[i-1][j-1]+matrix[i][j];	//càlcul de la regla A
					caseB = matrix2[i-1][j]+GAP;		//càlcul de la regla B	
					caseC = matrix2[i][j-1]+GAP;		//càlcul de la regla C
//Es guarda el valor màxim dels 3 casos en la cel·la corresponent, i segons el cas que sigui màxim s'indica una orientació determinada.
					if(caseA>=caseB && caseA>=caseC)
					{
						matrix2[i][j] = caseA;
						matrixOrientation[i][j]=DIAGONAL;
					}
					if(caseB>caseA && caseB>=caseC)
					{
						matrix2[i][j] = caseB;
						matrixOrientation[i][j]=LEFT;
					}
					if(caseC>caseA && caseC>=caseB)
					{
						matrix2[i][j] = caseC;
						matrixOrientation[i][j]=UP;
					}
				}
			}	
		}
	}



//Traducció del resultat de la matriu de similaritat a l'alineament de els dues seqüències.
//Es recorre el camí desde la posició cel·la s(n,m), seguint l'orientació indicada per la matriu d'orientació,
//fins a arribar a la cel·la s(0,0)
	i=n;j=m;indexSeq=0;
	*score = matrix2[i][j];
	while(i!=0 && j!=0)
	{
		orientation = matrixOrientation[i][j];
		//En cas que l'orientació sigui diagonal s'alinean les lletres d'aquesta posició.
		if(orientation == DIAGONAL)
		{
			*(seqResA+indexSeq)=*(seqA+i-1);
			*(seqResB+indexSeq)=*(seqB+j-1);
			i=i-1;
			j=j-1;
		}
		//En cas que l'orientació indiqui un moviment cap a l'esquerra afegim un gap a la seqüència B.
		else if(orientation == LEFT)
		{
			*(seqResA+indexSeq)=*(seqA+i-1);
			*(seqResB+indexSeq)='-';
			i=i-1;
		}
		//En cas que l'orientació indiqui un moviment cap a dalt afegim un gap a la seqüència A.
		else if(orientation == UP)
		{
			*(seqResA+indexSeq)='-';
			*(seqResB+indexSeq)=*(seqB+j-1);
			j=j-1;
		}
		indexSeq++;
	}
//Al fer el camí desde el final les dues seqüències resultants estàn en ordre invers.
//Amb aquesta crida, queden ven ordenades.
	inverseSeq(seqResA);
	inverseSeq(seqResB);
//Es crida a la funció match per trobar les coincidències entre les dues seqüències resultants de l'alineament.
	match(seqResA, seqResB, seqAst);

//Representació de la matriu de similaritat.
	if(showMatrix == 1)
	{
		printf("   ");	
		for(i=0;i<n;i++)
		{printf("  %c  ", *(seqA+i));}
		printf("\n     ");
		for(j=0;j<(m+1);j++)
		{
			for(i=0;i<(n+1);i++)
			{
				printf("%d  ", matrix2[i][j]);
			}
			printf("\n %c  ",*(seqB+j));
		}
		printf("\n");
	}
}


//Aquesta funció serveix per invertir l'ordre una seqüència donada.
void inverseSeq(char* seq)
{
	int i,j;
	char* aux;
	aux = (char *) malloc (strlen(seq) * sizeof(char));
	i=0;
	j=strlen(seq)-1;
	while(i<strlen(seq))
	{
		*(aux+i)=*(seq+j);
		i++;
		j--;
	}
	i=0;
	while(i<strlen(seq))
	{
		*(seq+i)=*(aux+i);
		i++;
	}
}


//Aquesta funció serveix per trobar les coincidències donades dues seqüències que tenen la mateixa longitud, és a dir, que ja hagin estat alineades.
void match(char* seqA, char* seqB, char* match)
{
	int i;
	i=0;

	while(i<strlen(seqA))
	{
//compara les dues seqüències, si són iguals a la seqüència match s'indica mitjançant un '*', si són diferents es fica un un guió '-'
		if((int)*(seqA+i)==(int)*(seqB+i))
		{
			*(match+i)='*';
		}
		else
		{
			*(match+i)='-';
		}
		i++;
	}
}
