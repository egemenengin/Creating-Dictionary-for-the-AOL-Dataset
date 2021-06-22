/////////////////////////////////////////////////////////////////////////
//////// 			CMPE 382 Project3 	 					  //////////
///////   Creating Dictionary for the AOL Dataset   Task7    //////////
//////  			Canay Kaplan 13975913008 				//////////
///// 			Egemen Engin 43144164030 	 			   //////////
////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "task1.c"


int main(int argc, char * argv[])
{	
	
	 clock_t startTime, endTime;
    startTime = clock();
	FILE * fp[10];
  
 

    FILE * newFile = fopen("Dictionary7.txt","w"); 
    char fileNames[10][20]={ {"data1.txt"},{"data2.txt"},{"data3.txt"},{"data4.txt"},{"data5.txt"},{"data6.txt"},{"data7.txt"},{"data8.txt"},{"data9.txt"},{"data10.txt"}};						  
     struct Trie* head = NULL;
     
      double usedTime;
	  long    numbytes[10];
      long totalNumBytes;
for(int i =0 ; i< 10;i++){
fp[i]=fopen(fileNames[i],"r");
	fseek(fp[i], 0L, SEEK_END);
	numbytes[i] = ftell(fp[i]);
	totalNumBytes += numbytes[i];
	 fseek(fp[i], 0L, SEEK_SET);	
}
char *buffer = (char*)malloc((totalNumBytes)*sizeof(char));
if(buffer == NULL){	 
   		 return 1;
}	 
for(int i =0 ; i< 10;i++){
	char*tempBuffer=(char*)malloc(numbytes[i]*sizeof(char));
	fread(tempBuffer, sizeof(char), numbytes[i], fp[i]);
	strcat(buffer,tempBuffer);
	free(tempBuffer);
}
char* tempLine = (char *)malloc(2048*sizeof(char));
char* endPtr;
char* endPtr2;
tempLine = strtok_r(buffer,"\n",&endPtr);

while(tempLine!=NULL){
	char* wordInQuery=strtok_r(tempLine," ",&endPtr2);
    while(wordInQuery!=NULL){	    
	   	insert(&head,wordInQuery);
	   	wordInQuery=strtok_r(NULL," ",&endPtr2);
	}  
	tempLine = strtok_r(NULL,"\n",&endPtr);   
}

traverseTST(head,newFile);
deleteAll(head);
free(buffer);

endTime = clock();
    usedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Used time is: %f\n", usedTime);
	
	for(int i =0 ; i< 10;i++){

	fclose(fp[i]);
	
}

}

  


 
