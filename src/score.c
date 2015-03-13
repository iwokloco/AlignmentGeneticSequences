#include "alineator.h"

//Funció que calcula la puntuació d'un alineament donades dos seqüències alineades i una matriu de substitució.
int scores(char* seqA, char* seqB, char* letras, int* subMatrix, int GAP)
{
	int i, x, y, scoreTotal, iSubMatrix;
	int *score;
	score = (int *) malloc (strlen(letras) * sizeof(int));
	i=0;scoreTotal=0;x=0;y=0;iSubMatrix=0;
	while(i<strlen(seqA))
	{
		if(*(seqA+i)!='-' && *(seqB+i)!='-')
		{
			x = search(*(seqA+i), letras);//coordenada i dins de la matriu de substitució.
			y = search(*(seqB+i), letras);//coordenada j dins de la matriu de substitució.
			iSubMatrix = y*strlen(letras)+x;//Ens indexem dins del vector de la matriu de substitució mitjançant aquesta fòrmula, k permet utilitzar les coordenades de la matriu original.
			*(score+i) = *(subMatrix+iSubMatrix);//Acumulem dins del vector de puntuacions, una nova puntuació indicada per la matriu de substitució per aquestes dues lletres.			
		}
		else
		{
			*(score+i) = GAP; //si tenim un GAP, afegim la seva puntuació negativa dins del vector de puntuacions.
		}
		i++;
	}
	i=0;
	while(i<strlen(seqA))
	{
		scoreTotal = scoreTotal + *(score+i);	//càlcul de la puntuació total
		i++;
	}
	
	return scoreTotal;
}


//Funció que retorna la posició que ocupa un valor dins la matriu de substitució indicat per la seva lletra.
int search(char c, char* letras)
{
	int i, find, position;
	i=0;find=0;

	while(i<strlen(letras) && find==0)
	{
		if(*(letras+i)==c)
		{
			find=1;		//Si troba el valor el bucle finalitza i es retorna la posició.
			position = i;
		}
		i++;
	}
	if(find == 0)
	{
		error("La lletra no s'ha trobat");
	}
	return position;
}
