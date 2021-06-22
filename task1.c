////////////////////////////////////////////////////////////////////////
///////   Creating Dictionary for the AOL Dataset   Task1    //////////
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

#define MAX 2048

// We take struct of trie, newNode, insert, traverseTSTUtil, traverseTST from https://www.geeksforgeeks.org/ternary-search-tree/
// But we changed them. For example insert counts number of words and traverseTST write to output file instead of printing to console.
typedef struct Trie {
    char data;

    // True if this character is last character of one of the words
    int isEndOfString;

    struct Trie* left, * eq, * right;


}Trie;

struct Trie* newNode(char data)
{
    Trie* temp = (Trie*)malloc(sizeof(Trie));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

// Function to insert a new word in a Ternary Search Tree
void insert(Trie** root, char* word)
{

    // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);

    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        insert(&((*root)->left), word);

    // If current character of word is greate than root's character,
    // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word);

    // If current character of word is same as root's character,
    else
    {
        if (*(word + 1))
            insert(&((*root)->eq), word + 1);

        // the last character of the word
        else{
            (*root)->isEndOfString = (*root)->isEndOfString + 1;
            
            }
    }

}

// A recursive function to traverse Ternary Search Tree
void traverseTSTUtil(Trie* root, char* buffer, int depth, FILE* out)
{
    if (root)
    {
        // First traverse the left subtree
        traverseTSTUtil(root->left, buffer, depth, out);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            buffer[depth + 1] = '\0';
            fprintf(out, "%s\t%d\n", buffer, root->isEndOfString);
        }

        // Traverse the subtree using equal pointer (middle subtree)
        traverseTSTUtil(root->eq, buffer, depth + 1, out);

        // Finally Traverse the right subtree
        traverseTSTUtil(root->right, buffer, depth, out);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverseTST(Trie* root, FILE* out)
{
    char buffer[MAX];
    traverseTSTUtil(root, buffer, 0, out);
}


void insertForUnion(Trie** root, char* word,int remaining)
{

    
    if (!(*root))
        *root = newNode(*word);

    
    if ((*word) < (*root)->data)
        insertForUnion(&((*root)->left), word,remaining);

    
    else if ((*word) > (*root)->data)
        insertForUnion(&((*root)->right), word,remaining);

    
    else
    {
        if (*(word + 1))
            insertForUnion(&((*root)->eq), word + 1,remaining);

        
        else{
            (*root)->isEndOfString = (*root)->isEndOfString + remaining;
            
            }
    }

}



void combineTrieUtil(Trie* root,Trie* bigTrieRoot, char* buffer, int depth)
{
    if (root)
    {
     
        combineTrieUtil(root->left, bigTrieRoot,buffer, depth);

     
        buffer[depth] = root->data;
        if (root->isEndOfString)
        {
            
            buffer[depth + 1] = '\0';
            insertForUnion(&bigTrieRoot,buffer,root->isEndOfString);
        }

        combineTrieUtil(root->eq,bigTrieRoot,buffer, depth + 1);

        
        combineTrieUtil(root->right,bigTrieRoot, buffer, depth);
    }
}

void combineTrie(Trie* root, Trie* bigTrieRoot)
{
    char buffer[MAX];
    combineTrieUtil(root,bigTrieRoot, buffer, 0);
}

void deleteAll(Trie* root){
    if(root==NULL)
        return;
    if( root->left !=NULL){
        deleteAll(root->left);
    }
    if(root->eq!=NULL){
        deleteAll(root->eq);
    }
    if(root->right !=NULL){
        deleteAll(root->right);
    }
    
    free(root);
    root=NULL;
}




