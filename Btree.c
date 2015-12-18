
#include "Btree.h"
#include <stdio.h>


Node* createTree(int keycapacity,int size){
	Node * root;
	root  =malloc(sizeof(Node)); 									// malloc rizas
 	root->block=malloc(sizeof(int)*(keycapacity+1));  // malloc pinaka int pou periexe block #
  	root->key=malloc(size*(keycapacity));             // malloc pinaka me keys 
  	root->branch=malloc(sizeof(Node)*(keycapacity+1));// malloc pinaka me ta branches;
 	if(root==NULL){
   		printf("error with memory allocation\n");
    	return NULL;
  	}
	if(root->block==NULL){
	    printf("error with memory allocation\n");
	    return NULL;
	}
	if(root->key==NULL){
	    printf("error with memory allocation\n");
	    return NULL;
	}
	if(root->branch==NULL){
	    printf("error with memory allocation\n");
	    return NULL;
	 }

	root->nextBlock=NULL;                                         // H riza exei dn exei next
	root->checking=0;                                             // check ==0
	return root;
}

Node* createBranchesfromBlock(int blockSrc,int keycapacity,int size, Node * root){
	void *block;
	if(BF_ReadBlock(fileDesc,blockSrc, &block)<0){
      fprintf(stderr,"can't read the file #%d \n",fileDesc);
      return NULL;
  	}
  // to prwto byte na einai panta anagnwristiko sta blocks??? px  -1 = adeio, 0=aplo fullo tou dentrou , 1= teleutaio prin ta data
	int i;
	if(((int*)block)[0]==-1){   // root is empty
    
    
    for(i=0;i<keycapacity;i++){   // MHDENISE TA PANTA

        root->branch[i];
        root->block[i]=-1;

        if(size==sizeof(int)|| size==sizeof(float)){ 
            root->key[i]==-1;
        }
        else{
            root->key[i]=="";
        }
    }
    // keycapacity +1 periptwsh
    root->branch[i];		
    root->block[i]=0;

  }
  else if(((int*)block)[0]==1){ // DATA NODE

  	for(i=0;i<keycapacity;i++){  

        OpenFile[i].root->branch[i]=NULL		// ftiaxnei to Node pou einai sto block ((int*)block)[i+1]						
        OpenFile[i].root->block[i]=((int*)block)[i+1];		// pare to number tou block gia th 8esh i
        // put key from block
        if(size==sizeof(int)|| size==sizeof(float)){ 
            OpenFile[i].root->key[i]==0;
        }
        else{
            OpenFile[i].root->key[i]=="";
        }
  	}
  }
  else{    // KEY NODE
  	for(i=0;i<keycapacity;i++){  

        OpenFile[i].root->branch[i]=createBranchesfromBlock(((int*)block)[i+1],keycapacity,size);						
        OpenFile[i].root->block[i]=((int*)block)[i];		// pare to number tou block gia th 8esh i

        if(size==sizeof(int)|| size==sizeof(float)){ 
            OpenFile[i].root->key[i]==0;
        }
        else{
            OpenFile[i].root->key[i]=="";
        }
  	}	

  }




}