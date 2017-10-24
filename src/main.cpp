#include <iostream>
#include "pgmhandle.h"
using namespace std;
int main(int argc, char *argv[]){
char archivo[30]; 
  readParams(argc, argv, archivo);
int nr,nc, gs;
int **imagen;
imagen=readPgm(archivo,&nr,&nc,&gs);
connectedComponent(imagen,nr,nc);

freeMatrix(imagen,nr);
cout<<"Su programa ha terminado\n";
return 0;}
