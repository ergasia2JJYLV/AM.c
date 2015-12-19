
#include "Btree.h"
#include <stdio.h>


Node* createTree(int keycapacity,int size){
	Node * root;
	root  =malloc(sizeof(Node)); 									// malloc rizas
 	if(root==NULL){
   		printf("error with memory allocation\n");
    	return NULL;
  	}
 	root->block=malloc(sizeof(int)*(keycapacity+1));  // malloc pinaka int pou periexe block #
  	root->key=malloc(size*(keycapacity));             // malloc pinaka me keys 
  	root->branch=malloc(sizeof(Node)*(keycapacity+1));// malloc pinaka me ta branches;
 	
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




int createBranchesfromBlock(int blockSrc,int fileDesc,int keycapacity,int size, Node * current){
	void *block;
	if(BF_ReadBlock(fileDesc,blockSrc, &block)<0){
      fprintf(stderr,"can't read the file #%d \n",fileDesc);
      return 0;
  	}
  	if(blockSrc!=1){ // run code for everything except root whi is already initilized
    
	  	current->block=malloc(sizeof(int)*(keycapacity+1));  // malloc pinaka int pou periexe block #
	  	current->key=malloc(size*(keycapacity));             // malloc pinaka me keys 
	  	current->branch=malloc(sizeof(Node)*(keycapacity+1));// malloc pinaka me ta branches;
	 	
		if(current->block==NULL){
		    printf("error with memory allocation\n");
		    return 0;
		}
		if(current->key==NULL){
		    printf("error with memory allocation\n");
		    return 0;
		}
		if(current->branch==NULL){
		    printf("error with memory allocation\n");
		    return 0;
		 }
	} 

  // to prwto byte/int na einai panta anagnwristiko sta blocks??? px  -1 = adeio, 0=aplo fullo tou dentrou , 1= teleutaio prin ta data
	int i;
			// where key_data in the block (after all the ints)
	if(size==sizeof(int)){ 
        int* nodekey=(int*)current->key;	
       	int* keys=&(((int*)block)[keycapacity+2]); 
       	if(((int*)block)[0]==-1){   // root is empty
    
    
			for(i=0;i<keycapacity;i++){   // MHDENISE TA PANTA

		        //current->branch[i];
		        current->block[i]=-1;
		        nodekey[i]==-1;
		        
		    }
		    // keycapacity +1 periptwsh
		   // current->branch[i];		
		    current->block[i]=0;
		    current->nextBlock=NULL;
		    return -1;  // 

		}
	  	else if(((int*)block)[0]==1){ // DATA NODE

	  		for(i=0;i<keycapacity;i++){  
	  									// to dentro teleiwnei edw
	        //current->branch[i];		// ftiaxnei to Node pou einai sto block ((int*)block)[i+1]						
	       		current->block[i]=((int*)block)[i+1];		// pare to number tou block gia th 8esh i
	        // put key from block
	       		memcpy(&(nodekey[i]),&((int*)keys)[i],size);
	        //int x =(int)current->key[i];
	        //printf("%d\n", (int*)nodekey[i]); 
	  		}
	  		//current->branch[i];		
	   		current->block[i]=((int*)block)[i+1];
	    	return 1;
	  	}
	  else{    // KEY NODE
	  		for(i=0;i<keycapacity;i++){  
	  			if(createBranchesfromBlock(((int*)block)[i+1],fileDesc,keycapacity,size,&current->branch[i])==-1){

	  				return 0;
	  			}		    					
	       		current->block[i]=((int*)block)[i+1];	 // pare to number tou block gia th 8esh i
	        	if(i>0){
	        		current->branch[i-1].nextBlock=&current->branch[i];
	      	    }		
	         // put key from block
	        	memcpy(&nodekey[i],&keys[i],size);
	        	//int x =(int)current->key[i];
	        	//printf("%d\n", (int*)nodekey[i]);   
	  		}
	  		createBranchesfromBlock(((int*)block)[i+1],fileDesc,keycapacity,size,&current->branch[i]);						
	    	current->block[i]=((int*)block)[i+1];	
	    	return 0;
	 	 }
    }
	if(size==sizeof(float)){
	    float* nodekey=(float*)current->key;	
	    float * keys=&(((int*)block)[keycapacity+2]); 
	    if(((int*)block)[0]==-1){   // root is empty
    
    
			for(i=0;i<keycapacity;i++){   // MHDENISE TA PANTA

		        //current->branch[i];
		        current->block[i]=-1;
		        nodekey[i]==-1;
		        
		    }
		    // keycapacity +1 periptwsh
		   // current->branch[i];		
		    current->block[i]=0;
		    current->nextBlock=NULL;
		    return -1;  // 

		}
	    else if(((int*)block)[0]==1){ // DATA NODE ...to dentro teleiwnei edw

	  		for(i=0;i<keycapacity;i++){  
				// ftiaxnei to Node pou einai sto block ((int*)block)[i+1]						
	       		current->block[i]=((int*)block)[i+1];		// pare to number tou block gia th 8esh i
	        // put key from block
	      		memcpy(&(nodekey[i]),&((float*)keys)[i],size);
	        	//float l =(float)current->key[i];
	         //	printf("%f\n", (float*)nodekey[i]);
	  	}
	  //	current->branch[i];		
	    current->block[i]=((int*)block)[i+1];
	    return 1;
	  	}
		else{    // KEY NODE
		  	for(i=0;i<keycapacity;i++){  
		  		if(createBranchesfromBlock(((int*)block)[i+1],fileDesc,keycapacity,size,&current->branch[i])==-1){

		  			return 0;
		  		}					
		        current->block[i]=((int*)block)[i+1];	 // pare to number tou block gia th 8esh i
		        if(i>0){
		        	current->branch[i-1].nextBlock=&current->branch[i];
		        }	
		        memcpy(&nodekey[i],&keys[i],size);
		        //float l =(float)current->key[i];
		        //printf("%f\n", (float*)nodekey[i]);
		  	}
		  	createBranchesfromBlock(((int*)block)[i+1],fileDesc,keycapacity,size,&current->branch[i]);					
		    current->block[i]=((int*)block)[i+1];	
		    return 0;

		}
	}
	else{
	        char*  nodekey=(char*)current->key;	
	       	char * keys=(char*)((block)+((keycapacity+1)*sizeof(int) +1));
	       	if(((int*)block)[0]==-1){   // root is empty
    
    
				for(i=0;i<keycapacity;i++){   // MHDENISE TA PANTA

			        //current->branch[i];
			        current->block[i]=-1;
			        nodekey[i]==-1;
			        
			    }
			    // keycapacity +1 periptwsh
			   // current->branch[i];		
			    current->block[i]=0;
			    current->nextBlock=NULL;
			    return -1;  // 

			}
		  else if(((int*)block)[0]==1){ // DATA NODE

		  	for(i=0;i<keycapacity;i++){  
		  									// to dentro teleiwnei edw
		        //current->branch[i];		// ftiaxnei to Node pou einai sto block ((int*)block)[i+1]						
		        current->block[i]=((int*)block)[i+1];		// pare to number tou block gia th 8esh i
		        // put key from block
		       
		        memcpy(&nodekey[i*size],&keys[i*size],size);
		            //char* t1= (char*)current->key[i*size];
		           // printf("%s\n",(char*)&((char*)nodekey[i*size]));
		     
		  	}
		  	//current->branch[i];		
		    current->block[i]=((int*)block)[i+1];
		    return 1;
		  }
		  else{    // KEY NODE
		  	for(i=0;i<keycapacity;i++){  
		  		if(createBranchesfromBlock(((int*)block)[i+1],fileDesc,keycapacity,size,&current->branch[i])==-1){

		  			return 0;
		  		}				
		        current->block[i]=((int*)block)[i+1];	 // pare to number tou block gia th 8esh i
		        if(i>0){
		        	current->branch[i-1].nextBlock=&current->branch[i];
		        }	


		         // put key from block
		   
		            memcpy(&(nodekey[i*size]),&(keys[i*size]),size);
		            //char* t1= (char*)current->key[i*size];
		           // printf("%s\n",(char*)&((char*)nodekey[i*size]));
		        
		  	}
		  	createBranchesfromBlock(((int*)block)[i+1],fileDesc,keycapacity,size,&current->branch[i]);				
		    current->block[i]=((int*)block)[i+1];	
		    return 0;
	    }


	}



}