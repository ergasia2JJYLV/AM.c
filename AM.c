
#include "AM.h"

#include "Btree.h"
#include "defn.h"
#include "BF.h"
#include <stdio.h>


#define STRINGSIZE	256
#define MAXOPENFILES 20
#define ROOTBLOCK	1

#define AME_ERROR_OPEN_INDEX -2
#define AM_ERCREATE -1
#define AM_NOT_OPENED -3
int AM_errno;		// from extern in AM.h


FileInfo	OpenFile[MAXOPENFILES];
int 		current_Open=0;         //maybe not needed

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
      OpenFile[i].i=bfs;    // keep FileDesc
      current_Open++;
      break;
    }
    printf("fuji\n" );
  }
  
  // ARXIKOPOIHSH B+ dentrou
  void *block;
  if(BF_ReadBlock(bfs,0, &block)<0){
      fprintf(stderr,"can't read the file #%d \n",OpenFile[i].i);
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

 
  int keycapacity=OpenFile[i].keycapacity;

  OpenFile[i].root=createTree(keycapacity,size);		// sto Btree.c
  if(OpenFile[i].root==NULL){
  	printf("Error with  tree creation\n");
  	return -1;
  }
  if(createBranchesfromBlock(ROOTBLOCK,bfs,keycapacity,size,OpenFile[i].root)==-2)	// anadromika ftiaxnei ta branches mexri kai ta data nodes
  {
  	printf("error creating branches\n");
  	return AM_errno=AM_ERCREATE;
  }

  /*
  // anadromika  auto to kommati???
  if(BF_ReadBlock(fileDesc,1, &block)<0){
      fprintf(stderr,"can't read the file #%d \n",fileDesc);
      return AM_errno=AM_ERCREATE;
  }
  // to prwto byte na einai panta anagnwristiko sta blocks??? px  -1 = adeio, 0=aplo fullo tou dentrou , 1= teleutaio prin ta data

  if(((int*)block)[0]==-1){   // root is empty
    int i;
    
    for(i=0;i<keycapacity;i++){   // MHDENISE TA PANTA

        OpenFile[i].root->branch[i];
        OpenFile[i].root->block[i]=-1;

        if(size==sizeof(int)|| size==sizeof(float)){ 
            OpenFile[i].root->key[i]==-1;
        }
        else{
            OpenFile[i].root->key[i]=="";
        }
    }
    // keycapacity +1 periptwsh
    OpenFile[i].root->branch[i];		
    OpenFile[i].root->block[i]=0;

  }
  else if(((int*)block)[0]==1){ // DATA NODE

  	for(i=0;i<keycapacity;i++){  

        OpenFile[i].root->branch[i]=	// ftiaxnei to Node pou einai sto block ((int*)block)[i+1]						
        OpenFile[i].root->block[i]=((int*)block)[i+1];		// pare to number tou block gia th 8esh i

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

        OpenFile[i].root->branch[i];						
        OpenFile[i].root->block[i]=((int*)block)[i];		// pare to number tou block gia th 8esh i

        if(size==sizeof(int)|| size==sizeof(float)){ 
            OpenFile[i].root->key[i]==0;
        }
        else{
            OpenFile[i].root->key[i]=="";
        }
  	}	

  }
	*/
  //^ anadromika  auto to kommati???

  printf("%d %d %d %d \n", OpenFile[i].keytype, OpenFile[i].datatype, OpenFile[i].keycapacity, OpenFile[i].datacapacity);
  printf("BFS is %d\n",bfs );

  return OpenFile[i].i;
}



int AM_CloseIndex (int fileDesc){
	int i;
	for (i =0; i< MAXOPENFILES ;i++)
  {
    if (OpenFile[i].i==fileDesc){
     	putTreeInBlock(&OpenFile[i]);
      	return 0;
    }
  }
  if(i==MAXOPENFILES){
  	return AM_errno=AM_NOT_OPENED;
  }
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