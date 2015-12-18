
#define MAXOPENFILES 20

struct FileInfo{
  int   i;
  int   keytype;
  int   datatype;
  int   datacapacity; // plh8os kleidiwn+data pou xwrane se ena block 
  int   keycapacity; // plh8os kleidiwn pou xwrane se ena block
  node* root;         
};

typedef struct FileInfo FileInfo;

FileInfo OpenFile[MAXOPENFILES];
int current_Open=0;

int AM_OpenIndex(char *fileName)
{
  int bfs=BF_OpenFile(fileName);
  if (bfs < 0)
  {
    BF_PrintError("Error opening file");
    return AME_ERROR_OPEN_INDEX;
  }
  int i;
  for (i =0; i< MAXOPENFILES ;i++)
  {
    if (OpenFile[i].i==0)
    {
      OpenFile[i].i=current_Open;
      current_Open++;
      break;
    }
    printf("fuji\n" );
  }
  
  // ARXIKOPOIHSH B+ dentrou
  void *block;
  if(BF_ReadBlock(fileDesc,0, &block)<0){
      fprintf(stderr,"can't read the file #%d \n",fileDesc);
      return AM_errno=AM_ERCREATE;
  }
  
  // type string 0> , int = -1, float = -2 
  //  string max size =255, int/float =4

  // key type-size
  OpenFile[i].keytype=((int*)block)[0]; 
  OpenFile[i].datatype=((int*)block)[1];
  // value type-size
  OpenFile[i].keycapacity=((int*)block)[2];
  OpenFile[i].datacapacity=((int*)block)[3];


  int size;
  if(OpenFile[i].keytype==-1){
    size=sizeof(int);
  }
  else if(OpenFile[i].keytype==-2){
    size=sizeof(float);
  }
  else {
    size=OpenFile[i].keytype;
  }

  if(BF_ReadBlock(fileDesc,1, &block)<0){
      fprintf(stderr,"can't read the file #%d \n",fileDesc);
      return AM_errno=AM_ERCREATE;
  }


  OpenFile[i].root  =malloc(sizeof(node)); // malloc rizas
  OpenFile[i].root->block=malloc(sizeof(int)*(OpenFile[i].keycapacity+1));  // malloc pinaka int pou periexe block #
  OpenFile[i].root->key=malloc(size*(OpenFile[i].keycapacity));             // malloc pinaka me keys 
  OpenFile[i].root->branch=malloc(sizeof(Node)*(OpenFile[i].keycapacity+1));// malloc pinaka me ta branches;
  if(OpenFile[i].root==NULL){
    printf("error with memory allocation\n");
    return AM_errno=AM_ERCREATE;
  }
  if(OpenFile[i].root->block==NULL){
    printf("error with memory allocation\n");
    return AM_errno=AM_ERCREATE;
  }
  if( OpenFile[i].root->key==NULL){
    printf("error with memory allocation\n");
    return AM_errno=AM_ERCREATE;
  }
  if(OpenFile[i].root->branch==NULL){
    printf("error with memory allocation\n");
    return AM_errno=AM_ERCREATE;
  }

  OpenFile[i].root->nextBlock=NULL;                                         // H riza exei dn exei next
  OpenFile[i].root->checking=0;                                             // check ==0

  if(((int*)block)[0]==-1){   // root is empty
    int i;
    for(i=0;i<keycapacity;i++){   // MHDENISE TA PANTA

        OpenFile[i].root->branch[i]=0;
        OpenFile[i].root->block[i]=0;

        if(size==sizeof(int)|| size==sizeof(float)){ 
            OpenFile[i].root->key[i]==0;
        }
        else{
            OpenFile[i].root->key[i]=="";
        }
    }
    // keycapacity +1 periptwsh
    OpenFile[i].root->branch[i]=0;
    OpenFile[i].root->block[i]=0;

  }
  else{ // pare ta data apo to block tou root ... 


  }

  printf("%d %d %d %d \n", OpenFile[i].keytype, OpenFile[i].datatype, OpenFile[i].keycapacity, OpenFile[i].datacapacity);
  printf("BFS is %d\n",bfs );

  return OpenFile[i].i;
}
