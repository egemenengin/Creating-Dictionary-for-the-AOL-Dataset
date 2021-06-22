////////////////////////////////////////////////////////////////////////
///////   Creating Dictionary for the AOL Dataset   Task4    //////////
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

void createDic(void* param) {
    FILE* tempFP = (FILE*)param;
    char* input = (char*)malloc(2048 * sizeof(char));
    
    while (fgets(input, 2048, tempFP)) {
        input[strlen(input) - 1] = '\0';
        pthread_mutex_lock(&locker);
        char* wordInQuery = strtok(input, " ");

        while (wordInQuery != NULL) {

            insert(&head, wordInQuery);

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
    FILE* fp[10];
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * 10);
    FILE* newFile = fopen("Dictionary4.txt", "w");
    char fileNames[10][20] = { {"data1.txt"},{"data2.txt"},{"data3.txt"},{"data4.txt"},{"data5.txt"},{"data6.txt"},{"data7.txt"},{"data8.txt"},{"data9.txt"},{"data10.txt"} };
    head = NULL;

    double usedTime;
    

    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
    }
   
    for (int i = 0; i < 10; i++) {
        pthread_create(&threads[i], NULL, (void*)createDic, fp[i]);
    }
    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

    traverseTST(head, newFile);
   
       
        free(threads);
    
     deleteAll(head);
    endTime = clock();
    for (int i = 0; i < 10; i++) {
        
        fclose(fp[i]);

    }

    usedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Used time is: %f\n", usedTime);
    
    fclose(newFile);



 }




