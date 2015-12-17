#include "AM.h"
#include "defn.h"
#include "BF.h"
#include <stdio.h>

#define MAXOPENFILES 20

struct FileInfo{
  int i;
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
