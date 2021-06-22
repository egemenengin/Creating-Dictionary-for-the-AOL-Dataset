# Creating-Dictionary-for-the-AOL-Dataset
Creating Dictionary for the AOL Dataset C Project

-Egemen Engin	
-Canay Kaplan

# How to run
We have 7 files for tasks and each file do what project wants and run like shown below except first file:
	gcc task2.c -o task2
	./task2
!!Except first file because it doesn't have any main method.
	
For task4 and task5 -lpthread should be added to gcc part:
	gcc task4.c -o task4 -lpthread
	./task4
From task2 to task7 it needs files' names must be like data1.txt,data2.txt,...,data10.txt. These files aren't in our file, so you should put these into the file. 
If you want change the readSize in task3, you must change max value in task1 and malloc sizes of input and tempInp.(It doesn't work 512 or lower)
# Design Overview
	In this project we have 7 different c files for each task. First file hold structure of trie and methods of it. Also it doesn't have main method. From second to seventh file, they read all files, do their tasks which project wants from us and they print Trie results to file in format of term\tCountOfTerm. File names are formed like Dictionary2.txt, Dictionary3.txt, Dictionary4.txt, ..., Dictionary10.txt. Also they print their execution time which is named as a used time in our code. Every file will be explained in detailed way in complete specification part.
# Complete Specification
	task1.c:
		There are structe of ternary tree structure which holds char as a data, count of the word and left eq and right Trie structures. Count of word is only assigned in the last characters of word. All other c files uses this file.
		Also there are some methods which are
			struct Trie* newNode(char data): It allocates a memory for Trie and create it with given data which is char and return it.
			void insert(Trie** root, char* word): It inserts new word to the Trie structure. If there is no root, it creates the root with this word. Also it increase it counts by 1.
			void traverseTST(Trie* root, FILE* out): It calls traversTSTUtil with buffer and output file.
			void traverseTSTUtil(Trie* root, char* buffer, int depth, FILE* out): It searches whole Trie and writes all terms in this Trie to the output file with their counts in format term\tCount.
			void insertForUnion(Trie** root, char* word,int remaining): It is insert function to use in union of Tries. Differences from normal insert when end of term is found, its count is incremented by as much as coming from other Trie.
			void combineTrie(Trie* root, Trie* bigTrieRoot): It calls combineTrieUtil with buffer and two trie which one of them is global final trie and other one is subTrie.
			void combineTrieUtil(Trie* root,Trie* bigTrieRoot, char* buffer, int depth):It takes each word from a Trie and implements to big one which will be global one. It is importat for task5.
			void deleteAll(Trie* root): Deallocate all Trie.
	task2.c: 
		It reads files line by line and with using Trie structure from task1, it implements each terms of each query to Trie with insert method. Then it writes all terms to output file which name is "Dictionary2.txt" with traverseTST method and after that, we used deleteAll method for deallocation operation; both methods are defined in task1.
		Lastly, for printing the execution time which represents the performance of the task, we made execution name as an used time in our code.
	task3.c:
		In this task, it reads Data files as a block of queries with firstly parsing strings to get queries. After that, we read only one read operation for multiple queries.Then we used insert method to add terms into Trie structure.
		After reading terms and inserting to Trie operations,traverseTST method writes all terms to output file which name is "Dictionary3.txt" and it is defined detailed in task1. Then we used deleteAll method for deallocation operation which is defined in task1.
		Lastly, we printed the execution time which represents the performance of the task, we made execution name as an used time in our code.
		
	task4.c:
		In this task, we execute thread execution. As an explanation, we read Data files with assigning a thread for each of them. For preventing threads' to access shared data at the same time, we used mutex.
		For inserting terms to Trie is same with task2's Trie implementation. We used insert method which is also explained detailed in task1. Thus, we insert terms into Trie structure with incrementing count. For the situation of Trie doesn't have that new term, we create new branch and that term is added to there.
		After reading terms and inserting to Trie operations,traverseTST method writes all terms to output file which name is "Dictionary4.txt" and it is defined detailed in task1. Then we used deleteAll method for deallocation operation which is defined in task1.
		Lastly, we printed the execution time which represents the performance of the task, we made execution name as an used time in our code.

	task5.c:
		In this task, with some changes on task4, we implemented for reading Data files with assigning the same multi-threaded way and using mutex. We used insert method for inserting operation the Trie structure. 
		As a difference of implementing terms to Trie structure, we created local Tries then in the end of adding terms part; we merged them into one and final Trie with combineTrie method which is explained detailed in task1.
		After reading and inserting to Trie operations,traverseTST method is called and wrote all terms to output file which name is "Dictionary5.txt" and it is defined detailed in task1.
		Lastly, for printing the execution time which represents the performance of the task, we made execution name as an used time in our code.

	task6.c:
		In this task, we did some changes on task2 and task3 and task6 is formed. As a difference of those tasks is that reading all Data files into memory.Then we insert terms into Trie structure with using insert and we called traverseTST method which are defined in task1.
		With the help of using traverseTST method, we wrote all terms to output file which name is "Dictionary6.txt" with that method and after that, we used deleteAll method for deallocation operation which are also defined in task1 in a much more detailed way. 
		Lastly, we printed the execution time which represents the performance of the task, we made execution name as an used time in our code.
	task7.c:
		In this task, for increasing the performance of one task that we chose, we did some changes onto it and their comparison and disccussion part is shown in Report part. We chose task6 to create some differences for decreasing the used time. 
		For increasing task7's performance, we changed allocation re-allocation situation and we implemented malloc operation for 10 times instead of reallocating the same memory location.
		After we changed that part, we called our insert method for insterting terms into Trie structure and we called traverseTST method  for writing all those terms to output file which name is "Dictionary7.txt" ; these methods are explained in much more detailed way in task1. 
		After reading terms and inserting terms to Trie operations, we called deleteALL method for deallocation operation which are also defined in task1 in a much more detailed way. 
		Lastly, we printed the execution time which represents the performance of the task, we made execution name as an used time in our code.
			
# Known bugs or problems
	We don't have any known bugs or problems in our whole tasks.
	
	
