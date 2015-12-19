#ifndef BTREE_H_
#define BTREE_H_
#include "BF.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AM_ERROR_GETTING_BLOCKS -2
#define MAXOPENFILES 20


struct Node{

  void *         key;
  struct Node*   branch;//
  int*           block;  
  struct Node*   nextBlock;
  int            checking; //checking if block is/was used
};
typedef struct Node Node;

struct FileInfo{

  int  i;
  int  keytype;
  int  datatype;
  int  datacapacity; // plh8os kleidiwn+data pou xwrane se ena block
  int  keycapacity; // plh8os kleidiwn pou xwrane se ena block
  Node*root;
};

typedef struct FileInfo FileInfo;



Node* createTree(int keycapacity,int size);
int   createBranchesfromBlock(int blockSrc,int fileDesc,int keycapacity,int size, Node * root);
void  putTreeInBlock(FileInfo* info);
#endif /* BTREE_H_ */