#include "AM.h"
#include "BF.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AM_ERROR_GETTING_BLOCKS -2
#define MAXOPENFILES 20

FileInfo OpenFile[MAXOPENFILES];


struct FileInfo{
  int i;
  int keytype;
  int datatype;
  int datacapacity; // plh8os kleidiwn+data pou xwrane se ena block
  int keycapacity; // plh8os kleidiwn pou xwrane se ena block
  Node *root;
};
typedef struct FileInfo FileInfo;

struct Node{
  void *key[];
  int branch[];//
  Node *nextBlock;
  int checking; //checking if block is/was used
};
typedef struct Node Node;
