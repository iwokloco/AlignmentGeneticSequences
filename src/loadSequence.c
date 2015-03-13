#include "alineator.h"

//Funció que carrega del fitxer que té el nom que entra com a primer paràmetre, una seqüència
//retorna la seqüència que hi ha al fitxer
char* loadSequence(char* argv[], int index)
{
	int canal, n, lenSeq, i, newLine;
	char c;
	char* nameFileSeq;
	char* Sequence;

	lenSeq = 100;
	//Assignació de memòria per les variables
	nameFileSeq 	= (char *) malloc (lenSeq * sizeof(char));
	Sequence	= (char *) malloc (2000 * sizeof(char));

	nameFileSeq = argv[index];

	if( (canal = open(nameFileSeq, O_RDONLY)) < 0 )	//O_RDONLY: Fitxer obert només per a lectura.
	{
		escriureMissatge(nameFileSeq);
		error("El fitxer no existeix.");
	}
	i = 0;
	newLine = 0;
	while((n = read(canal, &c, 1)) > 0)	//lectura del fitxer caràcter a caràcter mentre hi hagin caràcters dins.
	{
		if(newLine == 1)
		{
			if((int)(c)!=10)	//10 en ascii significa salt de línea.
			{
				*(Sequence+i) = c;//es guarda cada caràcter llegit dins de la seqüència.
				i++;
			}
		}
		if((int)(c) == 10)		//si tenim un salt de línea no ho guardem.
		{
			newLine = 1;
		}
	}
	if(n<0)
	{
		error("Error al llegir el fitxer."); //si es produeix un error de lectura del fitxer, s'indica.
	}
	close(canal);
	return Sequence;	//Retorna la seqüència llegida del fitxer.	
}
