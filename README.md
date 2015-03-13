# AlignmentGeneticSequences
Global alignment 
Esta aplicación ha sido desarrollada para funcionar sobre Ubuntu.
Los alineamientos de las secuencias son guardados en ficheros *.html, se ven correctamente bajo el navegador Firefox, con la fuente "Courier 10 Pitch".
Si no se dispone de esta fuente, es posible que al representar el alineamiento los guiones y astericos empleados para indicar las coincidencias, no se correspondan correctamente con sus posiciones entre las letras afectadas.

exec: contiene el archivo ejecutable "alineator".
matrices: contiene los ficheros de las matrices de sustitución. 
“blosum62”, “dna1”, “dna2”, “pam120”.
samples: aquí hay ficheros de ejemplo que contienen secuencias de aminoácidos o bien de nucleótidos.
Outputs: aquí se guardan las salidas del programa en *.html.
Contiene 3 ficheros correspondientes a 3 ejemplos de ejecución:
- GlobalAminoacidsB62.html
- defFuncioPuntuacio.html
- GlobalSenseMatriuSubs.html
src: contiene el código del programa.

Todo el código se ha desarrollado desde cero basándome en el algoritmo de alineamiento global de secuencias genéticas que se emplea en aplicaciones de bioinformática.
Podéis emplearlo para otro tipo de aplicaciones.

ALINEAMIENTO GLOBAL DE 2 SECUENCIAS CON MATRIZ DE SUSTITUCIÓN
usuari@User-ubuntu:~/alineator$ exec/alineator -sm matrices/nomFitxerMatriu -g <-a o -n>
samples/nomFitxerSeqüenciaA.fa samples/nomFitxerSeqüenciaB.fa [-html <nomFitxerSortida.html>]

usuari@User-ubuntu:~/alineator$ exec/alineator -sm matrices/blosum62 -g -a samples/ttrRat.fa
samples/ttrHuman.fa -html Outputs/GlobalAminoacids.html

Esta ejecución generó la salida "GlobalAminoacids.html"

ALINEAMIENTO GLOBAL DE 2 SECUENCIAS SIN MATRIZ DE SUSTITUCIÓN
usuari@User-ubuntu:~/alineator$ exec/alineator -g <-a o -n> samples/nomFitxerSeqüenciaA.fa
samples/nomFitxerSeqüenciaB.fa [-html <nomFitxerSortida.html>]

usuari@User-ubuntu:~/alineator$ exec/alineator -g -a samples/ttrRat.fa samples/ttrHuman.fa -html
Outputs/GlobalSenseMatriuSubs.html

Esta ejecución generó la salida "GlobalSenseMatriuSubs.html"

ALINEAMIENTO GLOBAL DONDE SE PUEDE DEFINIR LA FUNCIÓN DE PUNTUACIÓN MATCH, MISMATCH, GAP
usuari@User-ubuntu:~/alineator$ exec/alineator -sc 3 0 -2 -g -a samples/uoc2.fa samples/uoc1.fa
-html Outputs/defFuncioPuntuacio.html

OPCIONES
-sm: indica que queremos utilizar una matriz de sustitución, esta se indica mediante el path donde se encuentra.
-g: indica que queremos un alineamiento global.
-a: indica que el alineamiento es de secuencia de aminoácidos.
-n: indica que el alineamiento es de secuencias de nucleótidos.

COMPILACIÓN
usuari@User-ubuntu:~/alineator/src$ gcc alineator.c global.c score.c loadSequence.c html.c
readMatrix.c -o alineator
