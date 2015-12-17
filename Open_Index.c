#include "AM.h"
#include "defn.h"
#include "BF.h"
#include <stdio.h>

#define MAXOPENFILES 20

struct FileInfo{
  int i;
  int keytype;
  int keysize;
  int datatype;
  int datasize;
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
  
  // type string =0  , int = 1, float = 2 
  //  string max size =255, int/float =4

  // key type-size
  OpenFile[i].keytype=((int*)block)[0]; 
  OpenFile[i].keysize=((int*)block)[1];
  // value type-size
  OpenFile[i].datatype=((int*)block)[2];
  OpenFile[i].datasize=((int*)block)[3];
  printf("%d %d %d %d \n", OpenFile[i].keytype, OpenFile[i].keysize, OpenFile[i].datatype, OpenFile[i].datasize);
  printf("BFS is %d\n",bfs );
  return OpenFile[i].i;
}

int main(){
  //anoigoume 5 arxeia
  BF_Init();
  BF_CreateFile("fuji");
  BF_CreateFile("fuji1");
  AM_OpenIndex("fuji");
  AM_OpenIndex("fuji1");
  BF_CreateFile("fuji2");
  BF_CreateFile("fuji3");
  AM_OpenIndex("fuji2");
  AM_OpenIndex("fuji2");
  int i=AM_OpenIndex("fuji2");
  AM_OpenIndex("fuji3");
  printf("%d\n",i );
  return 0;
}
