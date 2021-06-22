////////////////////////////////////////////////////////////////////////
///////   Creating Dictionary for the AOL Dataset   Task2    //////////
//////  			Canay Kaplan			 				//////////
///// 			    Egemen Engin			 	 		   //////////
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
  
    FILE * newFile = fopen("Dictionary2.txt","w"); 
    char fileNames[10][20]={ {"data1.txt"},{"data2.txt"},{"data3.txt"},{"data4.txt"},{"data5.txt"},{"data6.txt"},{"data7.txt"},{"data8.txt"},{"data9.txt"},{"data10.txt"}};						  
     struct Trie* head = NULL;
      double usedTime;
       
for(int i =0 ; i< 10;i++){

    fp[i]=fopen(fileNames[i],"r");

   char * input = (char *)malloc(2048*sizeof(char));
	
	while(fgets(input,2048,fp[i])){
		input[strlen(input)-1]='\0';
		char *wordInQuery=strtok(input," ");
	    while(wordInQuery!=NULL){
	    
	   	 insert(&head,wordInQuery);
	   	 wordInQuery=strtok(NULL," ");
	    }      
		
		
	}
	
	
	free(input);
}	

traverseTST(head,newFile);
deleteAll(head);

endTime = clock();
    usedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Used time is: %f\n", usedTime);
	
	for(int i =0 ; i< 10;i++){

	fclose(fp[i]);
	
}

}

  


 
