////////////////////////////////////////////////////////////////////////
///////   Creating Dictionary for the AOL Dataset   Task5    //////////
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

Trie* head = NULL;
pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;
Trie * tries[10];

FILE* fp[10];
void createDic(void* param) {
   FILE* tempFP = (FILE*)fp[*((int *)param)];
    char* input = (char*)malloc(2048 * sizeof(char));
     
    while (fgets(input, 2048, tempFP)) {
        input[strlen(input) - 1] = '\0';
        pthread_mutex_lock(&locker);
        char* wordInQuery = strtok(input, " ");
 	    
        while (wordInQuery != NULL) {
            	 	
            insert(&(tries[*((int *)param)]), wordInQuery);
            
            wordInQuery = strtok(NULL, " ");
        }
        
        pthread_mutex_unlock(&locker);
    }
   
    free(input);
}
int main(int argc, char* argv[])
{
    
     clock_t startTime, endTime;
     
     startTime = clock();
    
    
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * 10);
    FILE* newFile = fopen("Dictionary5.txt", "w");
    
    char fileNames[10][20] = { {"data1.txt"},{"data2.txt"},{"data3.txt"},{"data4.txt"},{"data5.txt"},{"data6.txt"},{"data7.txt"},{"data8.txt"},{"data9.txt"},{"data10.txt"} };
    head = newNode('\0');

    double usedTime;
    

    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
        tries[i] =newNode('\0');
    }
   int counter[10];
    for (int i = 0; i < 10; i++) {
       counter[i]=i;
        pthread_create(&threads[i], NULL, (void*)createDic,&counter[i]);
    }
    
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }
    for(int i = 0; i< 10 ; i++){
   	//traverseTST(tries[i], newFile);
    	
        combineTrie(tries[i],head);
    }
    	traverseTST(head, newFile);
    endTime = clock();
    for (int i = 0; i < 10; i++) {
   
        fclose(fp[i]);

    }
    
    usedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Used time is: %f\n", usedTime);
    
    fclose(newFile);
    for (int i = 0; i < 10; i++) {
        deleteAll(tries[i]);
    
    }
    deleteAll(head);
    free(threads);
    

}






