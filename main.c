#include <stdio.h>
#include "AM.h"




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


  if(AM_CreateIndex("test",'c',255,'i',4)!=AME_OK){
    printf("ERROR\n");
    return -1;
  }
  AM_OpenIndex("test");
  return 0;
}
