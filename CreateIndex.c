#include "BF.h"
#include "AM.h"
#include "defn.h"
#include <stdio.h>

#define AM_ERCREATE -1
#define STRINGSIZE	256
#define MAXOPENFILES 20
#define AME_ERROR_OPEN_INDEX -2

#define MAXOPENFILES 20

int AM_errno;


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


int AM_CreateIndex(
  char *fileName, /* όνομα αρχείου */
  char attrType1, /* τύπος πρώτου πεδίου: 'c' (συμβολοσειρά), 'i' (ακέραιος), 'f' (πραγματικός) */
  int attrLength1, /* μήκος πρώτου πεδίου: 4 γιά 'i' ή 'f', 1-255 γιά 'c' */
  char attrType2, /* τύπος πρώτου πεδίου: 'c' (συμβολοσειρά), 'i' (ακέραιος), 'f' (πραγματικός) */
  int attrLength2 /* μήκος δεύτερου πεδίου: 4 γιά 'i' ή 'f', 1-255 γιά 'c' */)
{
	BF_Init();

	int error;
	//key

	int keytype;
	int keysize;
	switch(attrType1){
		case 'c':
			if(attrLength1>0){
				keytype=attrLength1;
				keysize=attrLength1;
			}
			else{
				printf("String size of 0< is pointless\n");
				return AM_errno=AM_ERCREATE;	
			}	
			break;
		case 'i':
			keytype=-1;
			keysize=attrLength1;
			break;
		case 'f':
			keytype=-2;
			keysize=attrLength1;
			break;
		default:
			printf("Not valid type for key field\n");
			return AM_errno=AM_ERCREATE;
	}

	// data
	int datatype;
	int datasize;
	switch(attrType2){
		case 'c':
			if(attrLength2>0){
				datatype=attrLength2;
				datasize=attrLength2;
			}
			else{
				printf("String size of 0< is pointless\n");
				return AM_errno=AM_ERCREATE;	
			}	
			break;
		case 'i':
				datatype=-1;
				datasize=attrLength2;
			break;
		case 'f':
				datatype=-2;
				datasize=attrLength2;
			break;
		default:
			printf("Not valid type for value field\n");
			return AM_errno=AM_ERCREATE;
	}

	if(error=BF_CreateFile(fileName)<0){   
		//BF_PrintError(error);
		fprintf(stderr,"can't create in %s \n",fileName);
		return AM_errno=AM_ERCREATE;
	}
	int fileDesc=BF_OpenFile(fileName);
	if(fileDesc<0){
		fprintf(stderr,"can't write in %s \n",fileName);
		return AM_errno=AM_ERCREATE;
	}

	if(BF_AllocateBlock(fileDesc)<0){  
		fprintf(stderr,"can't allocate %s \n",fileName);
		return AM_errno=AM_ERCREATE;
	}

	// INITIALIZATION OF FIRST BLOCK+
	void* block;
	if(BF_ReadBlock(fileDesc,0, &block)<0){
			fprintf(stderr,"can't read the file #%d \n",fileDesc);
			return AM_errno=AM_ERCREATE;
	}
	// type string =x  , int = -1, float = -2	
	// x= string max size , int/float =sizeof(int)

	// key type-size
	((int*)block)[0]=keytype;	
	// key type-size
	((int*)block)[1]=datatype;	
	// block capacity of key 
	int capacity=(BLOCK_SIZE-2*sizeof(int))/(sizeof(int)+keysize);
	((int*)block)[2]=capacity;
	// block capacity of data value 
	capacity=BLOCK_SIZE/(datasize+keysize);
	((int*)block)[3]=capacity;


	if(BF_WriteBlock(fileDesc,0)<0){
		fprintf(stderr,"can't Initialize the file #%d \n",fileDesc);
		return AM_errno=AM_ERCREATE;
	}



	// INITIALIZE ROOT as empty

	if(BF_AllocateBlock(fileDesc)<0){  
		fprintf(stderr,"can't allocate %s \n",fileName);
		return AM_errno=AM_ERCREATE;
	}
	if(BF_ReadBlock(fileDesc,1, &block)<0){
			fprintf(stderr,"can't read the file #%d \n",fileDesc);
			return AM_errno=AM_ERCREATE;
	}


	((int*)block)[0]=-1; 	// to -1 => to root einai adeio  	

	if(BF_WriteBlock(fileDesc,1)<0){
		fprintf(stderr,"can't Initialize the file #%d \n",fileDesc);
		return AM_errno=AM_ERCREATE;
	}





	//Ending the creation
	if(BF_CloseFile(fileDesc)<0){
		fprintf(stderr,"can't close %s \n",fileName);
		return AM_errno=AM_ERCREATE;
	}

	return AM_errno=AME_OK;
}

