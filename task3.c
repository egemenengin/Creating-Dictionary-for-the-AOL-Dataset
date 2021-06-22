/////////////////////////////////////////////////////////////////////////
//////// 			CMPE 382 Project3 	 					  //////////
///////   Creating Dictionary for the AOL Dataset   Task3    //////////
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


int main(int argc, char* argv[])
{
    
  
    clock_t startTime, endTime;
    startTime = clock();
    FILE* fp[10];
    FILE* tempFP[10];
    FILE* newFile = fopen("Dictionary3.txt", "w");
    char fileNames[10][20] = { {"data1.txt"},{"data2.txt"},{"data3.txt"},{"data4.txt"},{"data5.txt"},{"data6.txt"},{"data7.txt"},{"data8.txt"},{"data9.txt"},{"data10.txt"} };
    struct Trie* head =NULL;
    
    
    double usedTime;
        char* input = (char*)malloc(2048* sizeof(char));

        char* tempInp = (char*)malloc(2048* sizeof(char));
    for (int i = 0; i < 10; i++) {

        
        fp[i] = fopen(fileNames[i], "r");
        tempFP[i] = fopen(fileNames[i], "r");

        

        fseek(tempFP[i], 0, SEEK_END);
        long a = 0;
        int readSize = MAX;
        char* endPtr;
        char* endPtr2;

        while (fread(input, readSize, 1, fp[i]) == 1) {

            strcpy(tempInp, input);
            
            char* temp = strtok_r(input, "\n", &endPtr);


            long innera = 0;
            int checker = 1;
            while (temp != NULL && checker) {

                //printf("TEMP: %s\n",temp);

                if (tempInp[innera + strlen(temp)] != '\n') {
                    fseek(fp[i], a, SEEK_SET); 

                    checker = 0;
                    break;
                }
                a += strlen(temp) + 1;
                innera += strlen(temp) + 1;
                char* wordInQuery = strtok_r(temp, " ", &endPtr2);
                while (wordInQuery != NULL) {

                    insert(&head, wordInQuery);
                    wordInQuery = strtok_r(NULL, " ", &endPtr2);
                    
                    
                }
                temp = strtok_r(NULL, "\n", &endPtr);
                
            }

            long size1 = (ftell(tempFP[i]) - ftell(fp[i]));
            
            if ((size1) < MAX) {
                readSize = size1;
            }

        }
        
        
    }
        free(input);
        free(tempInp);
    traverseTST(head, newFile);
    
    endTime = clock();
    usedTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("Used time is: %f\n", usedTime);
    
    fclose(newFile);
    

    for (int i = 0; i < 10; i++) {

        fclose(fp[i]);
        fclose(tempFP[i]);
    }
deleteAll(head);
}



