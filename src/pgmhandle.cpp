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

void connecCompOp(int **IMG, int i0, int j0, int nr, int nc,int ncomp){
queue <int> icola, jcola;
vector <int> iconex, jconex;
int flag=0,mi,mj;
const int vi[]={0,1,1,0,1,-1,-1,-1};
const int vj[]={-1,-1,0,1,1,-1,0,1};
  icola.push(i0); jcola.push(j0);
  iconex.push_back(icola.front()); jconex.push_back(jcola.front());
 //cout<<"entras?\n";
 while(!icola.empty() || !jcola.empty() ){//
    if(icola.front()==0){
    for(int k=0;k<5;k++){ //Cinco vecinos
      mi=icola.front()+vi[k];
      mj=jcola.front()+vj[k];
      if(IMG[mi][mj]!=0){
       for(int r=0;r<iconex.size();r++){
        if(iconex[r]==mi && jconex[r]==mj){
          flag=1; 
          break;
        }
       }
       if(flag==1){
          flag=0;
          continue;
       } else{
          icola.push(mi); jcola.push(mj);
       }
      }
    }}
  else{
  //cout<<"entras\n";
    for(int k=0;k<8;k++){ //Ocho vecinos
      mi=icola.front()+vi[k];
      mj=jcola.front()+vj[k];
      for(int r=0;r<iconex.size();r++){
        if((iconex[r]==mi)||(jconex[r]==mj)){
          flag=1; 
          break;
        }
      }
      if(flag==1){flag=0; continue;}
      else{
        if(IMG[mi][mj]!=0){
          icola.push(mi);
          jcola.push(mj);
        }
      }
    } 
  }  
    icola.pop(); jcola.pop();
    iconex.push_back(icola.front()); jconex.push_back(jcola.front());
  }
for(int i=0;i<iconex.size();i++){
  IMG[iconex[i]][jconex[i]]=127;//5*(ncomp+1);
}
char nuevo[]={"nuevo.pgm"};
writePgm(IMG,nr,nc,255,nuevo);
}


int connectedComponent(int **IMG, int nr, int nc){
 int ncomp=0; 
 vector <int> tamanios; 
 for(int i=0;i<nr-1;i++){
    for(int j=0;j<nc-1;j++){
      if(IMG[i][j]!=0 && IMG[i][j]>(ncomp+1)*10){
        //Revisa todo el componente
        //connecCompOp(IMG,i,j,nr,nc,ncomp);
        tamanios.push_back(ccOp(IMG,i,j,ncomp));
        ncomp++;
//        cin.get();
//        cout<<"que haces?\n";
      }
    }
  } 
//for(int j=0;j<40;j++)  cout<<IMG[0][j]<<" "; 

char nuevo[]={"nuevo.pgm"};
writePgm(IMG,nr,nc,(ncomp+1)*10,nuevo);
cout<<"La cantidad de elementos conexos es: "<<ncomp<<"\n";
for(int i=0;i<tamanios.size();i++) 
  cout<<"Pixeles del elemento <"<<i+1<<"> :"<<tamanios[i]<<"\n";
return(0);}

int ccOp(int **IMG, int i0, int j0,int ncomp){
queue <int> ic, jc; 
  ic.push(i0); jc.push(j0);
vector<int> idex;
vector<int> jdex; 
int vi[8]={0,+1,+1,0,+1,-1,-1,-1};
int vj[8]={-1,-1,0,+1,+1,-1,0,+1};
int mi,mj,flag=0;
idex.push_back(ic.front()); jdex.push_back(jc.front());
IMG[idex.back()][jdex.back()]=(ncomp+1)*10;
//Ciclo de recorrido de toda la estructura
//cout<<"etraste?\n";
while(!ic.empty()){
//Si la estructura no esta pegada al borde
 if(ic.front()!=0){
  for(int k=0;k<8;k++){
    mi=ic.front()+vi[k]; mj=jc.front()+vj[k];
//Primero revisamos que el punto no se encuentre en el conjunto
    if(IMG[mi][mj]!=0 && IMG[mi][mj]!=(ncomp+1)*10){
    IMG[mi][mj]=(ncomp+1)*10;
    ic.push(mi); 
    jc.push(mj);}
    //cout<<mi<<" "<<mj<<"\n";
    //cin.get();
   }
  }
//Si la estructura esta pegada al borde
 else{
  for(int k=0;k<5;k++){
    mi=ic.front()+vi[k]; mj=jc.front()+vj[k];
//Primero revisamos que el punto no se encuentre en el conjunto
    if(IMG[mi][mj]!=0 && IMG[mi][mj]!=(ncomp+1)*10){
      IMG[mi][mj]=(ncomp+1)*10;
      ic.push(mi); 
      jc.push(mj);} 
   } 
 }
ic.pop(); jc.pop();
idex.push_back(ic.front());
jdex.push_back(jc.front());
}
//cout<<"saliste?\n";
//for(int i=0;i<idex.size();i++){
//  IMG[idex[i]][jdex[i]]=127;//5*(ncomp+1);
//}

return(idex.size());}








