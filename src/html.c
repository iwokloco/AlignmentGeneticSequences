#include "alineator.h"


//Funció que genera un document html.
void outHTML(char* nameHTML, int score, int length, char* seqA, char* seqB, char* seqRA, char* seqRB, char* seqAst, char* aligment, int match,int mismatch,int gap)
{
	int html, i, j,a,b,d;
	char c;
	char* src, *aux;
	src = (char *) malloc (50000 * sizeof(char));
	aux = (char *) malloc (1000 * sizeof(char));

//creació d'un fitxer html amb el nom que entra com a paràmetre a la funció.
	if((html=open(nameHTML, O_WRONLY | O_TRUNC | O_CREAT, 0600))<0)
		error("Error al intentar crear el fitxer html.");
//Es dona el format correcte a un punter de caràcters o cadena de caràcters, amb totes les dades que volem que surtin al document.
	sprintf(src, "<HTML><HEAD><TITLE>PRACTICA DE BIOINFORMATICA</TITLE></HEAD><BODY><FONT FACE=\"Courier 10 Pitch\"><b>PROGRAM OPTIONS:</b><br>-Aligment type: %s<br>-Match score: %d<br>-Mismatch score: %d<br>-Gap penalty: %d<p><b>INPUT SEQUENCES</b><br>Sequence I: %s<br>Sequence J: %s<p><b>ALIGNMENT</b><br>SCORE: %d<br>LENGTH: %d<p>:%s <br>:<font color=green>%s </font><br>:%s<br></FONT></BODY></HTML>",aligment, match, mismatch, gap,seqA,seqB, score, length, seqRA, seqAst, seqRB);

	i=0;
	while(i<strlen(src))
	{
		if((write(html, (src+i), 1))<0)	//S'escriu caràcter per caràcter dins del fitxer .html
			error("Error de escriptura en el fitxer html.");
		i++;
	}

	close(html);//Es tanca el canal obert pel fitxer.
}
