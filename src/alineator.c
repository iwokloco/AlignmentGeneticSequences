#include "alineator.h"


int 
  /* Default scoring scheme */ 
  ID=2,MIS=0,GAP=-1;

//Funció per a gestionar els errors
void error(char *m)
{
	write(2, m, strlen(m));
	write(2, "\n", 1);
	write(2, strerror(errno), strlen(strerror(errno)));
	exit(1);
}
//Funció per a escriure missatges per pantalla
void escriureMissatge(char *missatge)
{
	int n;
	n=write(1,missatge, strlen(missatge));
}

//Funció principal
int main(int argc, char* argv[])
{
	int i, n, m, sizeSubMatrix, score;
	char *FileSubMatrix;
	char *SequenceA, *SequenceB, *SeqResultA, *SeqResultB, *SeqAsterisc, *letras;
	int *SeqSubMatrix, sizeXSubMatrix, sizeYSubMatrix;
//Assignació de la memòria per al nom del fitxer de la matriu de substitució.
	FileSubMatrix 	= (char *) malloc (100 * sizeof(char));
//Assignació de la memòria per a les variables de sequencies.
	SequenceA   = (char *) malloc (2000 * sizeof(char));
	SequenceB   = (char *) malloc (2000 * sizeof(char));
	SeqResultA  = (char *) malloc (2000 * sizeof(char));
	SeqResultB  = (char *) malloc (2000 * sizeof(char));
	SeqAsterisc = (char *) malloc (2000 * sizeof(char));
	letras = (char *) malloc (24 * sizeof(char));
//assignació de memòria per emmagatzemar les dades de la matriu com una seqüència o vector.
	SeqSubMatrix = (int *) malloc (580 * sizeof(int));
	
//Segons els arguments d'entrada al programa, es realitzaran unes funcions o no.
	if(strcmp(argv[1],"-sm")==0)	//Si argv[1] és -sm vol dir que haurem d'utilitzar una matriu de substitució
	{
		escriureMissatge(">Loading first sequence \n");
		SequenceA = loadSequence(argv, 5);		//Carrega de la seqüència I
		escriureMissatge(">Loading second sequence \n");
		SequenceB = loadSequence(argv, 6);		//Carrega de la seqüència J
		n = strlen(SequenceA);
		m = strlen(SequenceB);
		if(strcmp(argv[4],"-a")==0)	//Si argv[4] és -a, les seqüències que carreguem són d'aminoàcids.
		{
			printf("# Sequence I - Length = %d amino acids\n", n);
			printf("# Sequence J - Length = %d amino acids\n", m);
		}
		else if(strcmp(argv[4],"-n")==0)//Si argv[4] és -n, les seqüències que carreguem són de nucleòtids.
		{
			printf("# Sequence I - Length = %d nucleotides\n", n);
			printf("# Sequence J - Length = %d nucleotides\n", m);			
		}
		else
		{
			error("Error format command");
		}
		if(strcmp(argv[3],"-g")==0)	//Si argv[3] és -g vol dir que farem un alineament global.
		{
			escriureMissatge(">Global Aligment \n");
			//Crida a la funció d'alineament global.
			global(0, SequenceA, SequenceB, n, m, SeqResultA, SeqResultB, SeqAsterisc, ID, MIS, GAP, &score);
		}
		FileSubMatrix = argv[2];
		escriureMissatge(">Loading Substitution Matrix \n");
		//Crida a la funció que llegeix la matriu de substitució del fitxer indicat pel argument argv[2].
		readMatrix(FileSubMatrix, SeqSubMatrix, &sizeSubMatrix, &sizeXSubMatrix, &sizeYSubMatrix, letras);
		//Crida a la funció que calcula la puntuació, basant-se en la matriu de substitució.
		score = scores(SeqResultA, SeqResultB, letras, SeqSubMatrix, GAP);
		printf("#Total SCORE: %d\n", score);
		if(argc>7) //si tenim més de 7 arguments en aquest cas, hi ha l'opció de fer un fitxer html amb l'alineament i la puntuació.
		{
			if(strcmp(argv[7],"-html")==0)
			{		
				outHTML(argv[8], score, strlen(SeqResultA), SequenceA, SequenceB, SeqResultA, SeqResultB, SeqAsterisc, "Global", ID,MIS,GAP);
			}
		}
		
				
	}
//Segons si es demana un alineament global o local sense especificar matriu de substitució.
	else if(strcmp(argv[1],"-g")==0 || strcmp(argv[1],"-l")==0)
	{
		escriureMissatge(">Loading first sequence \n");
		SequenceA = loadSequence(argv, 3);		//Carrega de la seqüència I
		escriureMissatge(">Loading second sequence \n");
		SequenceB = loadSequence(argv, 4);		//Carrega de la seqüència J
		n = strlen(SequenceA);
		m = strlen(SequenceB);
		if(strcmp(argv[2],"-a")==0)//Si argv[2] és -a, les seqüències que carreguem són d'aminoàcids.
		{
			printf("# Sequence I - Length = %d amino acids\n", n);
			printf("# Sequence J - Length = %d amino acids\n", m);
		}
		else if(strcmp(argv[2],"-n")==0)//Si argv[2] és -n, les seqüències que carreguem són de nucleòtids.
		{
			printf("# Sequence I - Length = %d nucleotides\n", n);
			printf("# Sequence J - Length = %d nucleotides\n", m);			
		}
		else
		{
			error("Error format command");
		}
		if(strcmp(argv[1],"-g")==0)//Si argv[1] és -g vol dir que farem un alineament global.
		{
			escriureMissatge(">Global Aligment \n");
			//Crida a la funció d'alineament global, que mostra la matriu de similaritats.
			global(1, SequenceA, SequenceB, n, m, SeqResultA, SeqResultB, SeqAsterisc, ID, MIS, GAP, &score);
			//Mostra l'alineament resultant per la consola.
			escriureMissatge(SeqResultA);
			printf("\n");
			escriureMissatge(SeqAsterisc);
			printf("\n");
			escriureMissatge(SeqResultB);
			printf("\n");
		}
		//Es mostra la puntuació per la consola.
		printf("#Total SCORE: %d\n", score);

		if(argc>5)//si tenim més de 5 arguments en aquest cas, hi ha l'opció de fer un fitxer html amb l'alineament i la puntuació.
		{
			if(strcmp(argv[5],"-html")==0)
			{	//crida a la funció que genera el fitxer html.	
				outHTML(argv[6], score, strlen(SeqResultA), SequenceA, SequenceB, SeqResultA, SeqResultB, SeqAsterisc, "Global", ID,MIS,GAP);
			}
		}

	}
//Segons si es vol especificar la funció de puntuació MATCH, MISMATCH, GAP. -sc: scores
	else if(strcmp(argv[1],"-sc")==0)
	{	//Introdueix els nous valors a les variables MATCH, MISMATCH, GAP.
		escriureMissatge(">Change values of scores...");
		ID = atoi(argv[2]);
		MIS = atoi(argv[3]);
		GAP = atoi(argv[4]);
		
		escriureMissatge(">Loading first sequence \n");
		SequenceA = loadSequence(argv, 7);	//Carrega de la seqüència I
		escriureMissatge(">Loading second sequence \n");
		SequenceB = loadSequence(argv, 8);	//Carrega de la seqüència J
		n = strlen(SequenceA);
		m = strlen(SequenceB);
		if(strcmp(argv[6],"-a")==0)//Si argv[6] és -a, les seqüències que carreguem són d'aminoàcids.
		{
			printf("# Sequence I - Length = %d amino acids\n", n);
			printf("# Sequence J - Length = %d amino acids\n", m);
		}
		else if(strcmp(argv[6],"-n")==0)//Si argv[6] és -n, les seqüències que carreguem són de nucleòtids.
		{
			printf("# Sequence I - Length = %d nucleotides\n", n);
			printf("# Sequence J - Length = %d nucleotides\n", m);			
		}
		else
		{
			error("Error format command");
		}
		if(strcmp(argv[5],"-g")==0)//Si argv[5] és -g vol dir que farem un alineament global.
		{
			escriureMissatge(">Global Aligment \n");
			//Crida a la funció d'alineament global.
			global(1, SequenceA, SequenceB, n, m, SeqResultA, SeqResultB, SeqAsterisc, ID, MIS, GAP, &score);
			//Escriu els resultats de l'alineament per la consola.
			escriureMissatge(SeqResultA);
			printf("\n");
			escriureMissatge(SeqAsterisc);
			printf("\n");
			escriureMissatge(SeqResultB);
			printf("\n");
		}
		printf("#Total SCORE: %d\n", score);

		if(argc>9)//si tenim més de 9 arguments en aquest cas, hi ha l'opció de fer un fitxer html amb l'alineament i la puntuació.
		{
			if(strcmp(argv[9],"-html")==0)
			{	//crida a la funció que genera el fitxer html.	
				outHTML(argv[10], score, strlen(SeqResultA), SequenceA, SequenceB, SeqResultA, SeqResultB, SeqAsterisc, "Global", ID,MIS,GAP);
			}
		}
	}

	exit(1);
}
