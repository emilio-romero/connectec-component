#ifndef PGMHANDLE_H
#define PGMHANDLE_H 
#include <iostream> 
#include <cstring> 
#include <cstdio>
#include <queue>
using namespace std;
void readParams(int argc, char *argv[], char *file);
int **createMatrix(int nr, int nc);
void freeMatrix(int **mat, int nr);
int **readPgm(char *pfile, int *nr, int *nc, int *gs);
int writePgm(int **Npgm, int nr, int nc, int gs, char *cfile);
//Funciones para la busqueda de objetos conexos

#endif 
