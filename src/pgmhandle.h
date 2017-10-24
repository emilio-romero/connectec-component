#ifndef PGMHANDLE_H
#define PGMHANDLE_H 
#include <iostream> 
#include <cstring> 
#include <cstdio>
#include <queue>
#include <cstdlib>
using namespace std;
void readParams(int argc, char *argv[], char *file);
int **createMatrix(int nr, int nc);
void freeMatrix(int **mat, int nr);
int **readPgm(char *pfile, int *nr, int *nc, int *gs);
int writePgm(int **Npgm, int nr, int nc, int gs, char *cfile);
//Funciones para la busqueda de objetos conexos
void connecCompOp(int **IMG, int i0, int j0, int nr, int nc, int ncomp);
int connectedComponent(int **IMG, int nr, int nc);
int ccOp(int **IMG, int i0, int j0,int ncomp);
#endif 
