#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<limits.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
    //Shri//

//struct ADT of TREE of FILE
typedef struct node {
    char *fname;
    int isdir;
    int isrootNode;
    
    struct information {
    	unsigned long int fsize;
    	char* fpath;
    	char* fpermissions;
    	char* fuser_name;
		long int inode;
    	struct last_modification {
    		short fdate;
    		short fmon;
    		short fyear;
    		short fhour;
    		short fmin;
    		short fsec;
    	}last_mod;
    	
    }info;
    
    struct node *next_ptr;
    struct node *inner_ptr;
}node;

typedef node* tnode;

//for counting
int count;
int file_count;
int dir_count;

//creation of treenode and tree structure 
node* createTreeNode(char *name);
node* createTree(char *rootname);
node* createTree_1(char *rootname);
 
//get size of of file and function for inode
unsigned long int get_Size(char *file_name) ;
long int get_fileSize(char *file_path);
long int get_inode(char *file_path);


//printing a tree wrt to flags
void printTree(tnode t);
void printTree_a(tnode t);
void printTree_d(tnode t);
void printTree_s(tnode t);
void printTree_f(tnode t);
void printTree_L(tnode t, int level);
void printTree_inode(tnode t);
void printTree_D(tnode t);

//command line argument passing for directory and diff flags
void help();
void tree_arg1(char *rootname);
void tree_arg2(char *rootname, char *flag);
void tree_arg3(char *rootname, char *arg1, char *arg2);

//sorting a files
node*findMid(tnode head);
node*merge(node*left, node*right);
node*mergeSort(tnode head);
node* sort_subd(tnode q);
