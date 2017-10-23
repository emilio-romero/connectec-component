#include "pgmhandle.h" 

void readParams(int argc, char *argv[], char *file){
  if(argc>1) strcpy(file,argv[1]);
}

int **createMatrix(int nr, int nc){
  int **mat;
  mat=(int**)malloc(nr*sizeof(int*));
  if(mat==NULL) return(NULL);
  for(int i=0;i<nr;i++)
    mat[i]=(int*)malloc(nc*sizeof(int));
return(mat);}

void freeMatrix(int **mat, int nr){
  for(int i=0;i<nr;i++)
    free(mat[i]);
  free(mat);
}

int **readPgm(char *pfile, int *nr, int *nc, int *gs){
  int **mat; 
  char ch; int val; 
  FILE *f1=fopen(pfile,"r");
  if(!f1) return(NULL);
  ch=getc(f1);
  if(ch!='P'){
    cout<<"Error: no es un archivo pgm valido\n";
    return(NULL);
  }
  ch=getc(f1);
  //
  //
  fscanf(f1,"%d",nc); fscanf(f1,"%d",nr); fscanf(f1,"%d",gs);
  mat=createMatrix(*nr,*nc);
  for(int i=0;i<(*nr);i++){
    for(int j=0;j<(*nc);j++){
      fscanf(f1,"%d",&val);
      mat[i][j]=val;
    }
  }
  fclose(f1);

return(mat);}

int writePgm(int **Npgm, int nr, int nc, int gs, char *cfile){
FILE *out; 
  out=fopen(cfile,"w");
  fprintf(out,"P2\n");
  fprintf(out,"%d %d\n%d\n",nc,nr,gs);
  for(int i=0;i<nr;i++){
    for(int j=0;j<nc;j++){
      fprintf(out,"%d ",Npgm[i][j]);
    }
    fprintf(out,"\n");
  }
fclose(out);
return(0);}



