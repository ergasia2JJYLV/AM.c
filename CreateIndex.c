#include "BF.h"
#include "AM.h"
#include <stdio.h>
#define AM_ERCREATE -1
#define STRINGSIZE	256
int AM_errno;


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
			keytype=0;
			keysize=attrLength1;
			break;
		case 'i':
			keytype=1;
			keysize=attrLength1;
			break;
		case 'f':
			keytype=2;
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
				datatype=0;
				datasize=attrLength2;
			break;
		case 'i':
				datatype=1;
				datasize=attrLength2;
			break;
		case 'f':
				datatype=2;
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
	// type string =0  , int = 1, float = 2	
	//  string max size =255, int/float =4

	// key type-size
	((int*)block)[0]=keytype;	
	((int*)block)[1]=keysize;	
	// value type-size
	((int*)block)[2]=datatype;
	((int*)block)[3]=datasize;
	
	if(BF_WriteBlock(fileDesc,0)<0){
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