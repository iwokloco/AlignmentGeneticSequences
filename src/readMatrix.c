#include "alineator.h"

//Funció que llegeix una matriu de substitució indicada pel nom del fitxer.
void readMatrix(char* nameFileMatrix, int* seqSubMatrix, int* sizeSubMatrix, int* sizeXSubMatrix, int* sizeYSubMatrix, char* letras)
{
	int canal, n, i, j, sizeI, sizeJ, is, menos, unidad, decena, hayNum, aux;
	char c;
	char matrix[24][24];
	char* indexMatrix;
	int  matrixSub[23][23];
	indexMatrix	= (char *) malloc (30 * sizeof(char));	//assignació de memòria.

	if( (canal = open(nameFileMatrix, O_RDONLY)) < 0 )	//O_RDONLY: Fitxer obert només per a lectura.
	{
		escriureMissatge(nameFileMatrix);
		error("El fitxer no existeix.");
	}
	i = 0;j=0;
	while((n = read(canal, &c, 1)) > 0 && (int)(c)!=10)
	{
		if((int)(c)!=32)
		{
		//Obtenció de les lletres que serveixen per indexar-se a la matriu de substitució.
			*(letras+i)=c;
			*(indexMatrix+i)=c;
			i++;
		}
	}
	//Obtenció dels valors de puntuació de la matriu de substitució.
	i = 0;j=0;menos = 0;unidad=0;decena=0;hayNum=0;aux=0;
	while((n = read(canal, &c, 1)) > 0)
	{
		if((int)(c)<58 && (int)(c)!=32 && (int)(c)!=10)	//58 representa el umbral dels nombres en ASCII.
		{
			if((int)(c)==45)	//45 en ASCII és '-'
			{
				menos = 1;	//indiquem que aquest valor serà negatiu.
			}
			else
			{
				if(menos == 1)
				{
					if(unidad==0 && decena==0)
					{
//Es transforma de l'ascii al valor enter i es nega ja que menos=1 i això indica un valor negatiu.
						aux = -((int)(c)-48);	
						unidad = 1;
						hayNum = 1;
					}
					else if(unidad==1 && decena==0)//Si el nombre és més petit que -9.
					{
						aux=aux*10+(int)(c)-48;
						unidad=0;
						decena=1;
						hayNum = 1;
					}
					else if(unidad==0 && decena==1)//Si el nombre és més petit que -99.
					{
						aux=aux*10+(int)(c)-48;
						unidad=0;
						decena=1;
						hayNum = 1;
					}
				}
				else
				{
					if(unidad==0 && decena==0)
					{
//Es transforma de l'ascii al valor enter, aquest valor serà positiu, ja que menos=0.
						aux = (int)(c)-48;
						unidad = 1;
						hayNum = 1;
					}
					else if(unidad==1 && decena==0)//Si el nombre és més gran que 9.
					{
						aux=aux*10+(int)(c)-48;
						unidad=0;
						decena=1;
						hayNum = 1;
					}
					else if(unidad==0 && decena==1)//Si el nombre és més gran que 99.
					{
						aux=aux*10+(int)(c)-48;
						unidad=0;
						decena=1;
						hayNum = 1;
					}
				}
			}	
		}
		else
		{
			if(hayNum==1)
			{
				matrix[i][j]=aux;
				i++;
				menos=0;unidad=0;decena=0;hayNum=0;aux=0;
			}
			if((int)(c)==10)
			{
				*sizeXSubMatrix = i;
				sizeI=i;
				i=0;
				j++;
			}
		}
	}
	if(n<0)
	{
		error("Error al llegir el fitxer.");//si el fitxer no s'ha pogut llegir s'indica un error.
	}
	close(canal);
	
	
	*sizeYSubMatrix = j;
//Es plena el vector seqSubMatrix amb els valors de la matriu de substitució.
	sizeJ = j;is=0;
	for(j=0;j<sizeJ;j++)
	{
		for(i=0;i<sizeI;i++)
		{
			*(seqSubMatrix+is)=matrix[i][j];
			is++;
			*sizeSubMatrix = is;
		}	
	}
}
