#include<stdio.h>
#include"command.h"
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include <time.h>

void get_last_mod(node* ptr, char *file_name) {
	struct stat st;
	struct tm *mod;
	
	if(stat(file_name, &st) != 0)
		return;
	
	mod = localtime(&st.st_mtime);


	ptr->info.last_mod.fdate = mod->tm_mday;
	ptr->info.last_mod.fmon = mod->tm_mon + 1;
	ptr->info.last_mod.fyear = mod->tm_year + 1900;
	ptr->info.last_mod.fhour = mod->tm_hour;
	ptr->info.last_mod.fmin = mod->tm_min;
	ptr->info.last_mod.fsec = mod->tm_sec;
	return;
}

long int get_inode(char*file_name){
    struct stat st;

    if(stat(file_name, &st)== 0){
        return st.st_ino;
    }
    else
        return 0;
}


//This functions initializes the information about a file/directory
node* createTreeNode(char *name) {
    node* nn = (node*)malloc(sizeof(node));
    nn->fname = name;
    nn->isdir = 1;
    nn->isrootNode = 0;
    nn->info.fsize = 0;
    //nn->info.inode = 0;
    
    nn->info.fpath = (char*)calloc(1000, sizeof(char));
 
    
    //last modification details
    nn->info.last_mod.fdate = -1;
    nn->info.last_mod.fmon = -1;
    nn->info.last_mod.fyear = -1;
    nn->info.last_mod.fhour = -1;
    nn->info.last_mod.fmin = -1;
    nn->info.last_mod.fsec = -1;
    
    //self referencial pointers
    nn->inner_ptr = NULL;
    nn->next_ptr = NULL;
    
    return nn;
}

node* createTree(char *rootname) {
	DIR *dir = opendir(rootname);
 	//if it fails to open root directory then return
    if(!dir) {
        printf("Failed to open %s ...", rootname);
        return NULL;
    }
	closedir(dir);
	
	node *rootNode = createTreeNode(rootname);
	rootNode->isrootNode = 1;
	rootNode->inner_ptr = createTree_1(rootname);
	//rootNode->info.fpath = ".";
	return rootNode;
}


node* createTree_1(char *rootname) {
    node *p = NULL, *q = NULL;
    node *t_start = NULL;
    
    char name[1000];
    struct dirent *dr = NULL;
    
    //opening a directory 
    DIR *dir = opendir(rootname);
    if(!dir) {
        printf("Failed to open %s...\n", rootname);
        return NULL;
    }
	
	//traversing until end of directory stream
    while((dr = readdir(dir)) != NULL) {
    	
    	//Not to consider sub-directories "." and ".."
    	if(strcmp((dr->d_name),".") != 0 && strcmp((dr->d_name),"..") != 0) 
			p = createTreeNode(dr->d_name);
		else {
			p = NULL;
			continue;
		}
    
        //t_start will point to first node in root directory
        if(!q)
            t_start = p;
        else
            q->next_ptr = p;
        
		//if current stream is directory
        if((dr->d_type) == DT_DIR) {
            
            p->isdir = 1;
            //copy rootname to name
            strcpy(name, rootname);
            //printf("%s", name);
            //coombining string
            p->inner_ptr = createTree_1(strcat((strcat(name, "/")), dr->d_name));
            p->info.fsize = get_Size(name);
            p->info.inode = get_inode(name);
            strcpy(p->info.fpath, name);
            
            strcpy(name, rootname);
            //p = p->next_ptr;
           // printf("%s", name);
        }	
        //else current stream is not directory
        else {
            p->isdir = 0;
            p->inner_ptr = NULL;
            
            strcpy(name, rootname);
            strcat((strcat(name, "/")), dr->d_name);
            p->info.fsize = get_Size(name);
            get_last_mod(p, name);
             
            strcpy(p->info.fpath, name);
         //  strcpy(name, "");	
         //  printf("%s\n", name);
          	
        }
        
        q = p;
    //    p = p->next_ptr;
    }
    
    //returning start node of tree structure
    return t_start;
    closedir(dir);
}


//get the size of directory using stat()
unsigned long int get_Size(char *file_name) {
	struct stat st;		//declare stat variable
	
	if(stat(file_name, &st) == 0)
		return st.st_size;
	else
		return 0;
}



//get the size of file using fseek() and ftell()
//ftell() is used to store the current file position. fseek() is used to relocate to one of the following:
//A file position stored by ftell()
//A calculated record number (SEEK_SET)
//A position relative to the current position (SEEK_CUR)
//A position relative to the end of the file (SEEK_END)

long int get_fileSize(char *file_path) {
	FILE *fp = fopen(file_path, "r");
	if(!fp) {
		return -1;
	}
	long int size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fclose(fp);
	return size;
}

//printing help file
void help(){
	FILE*fp ;
	fp = fopen("helpmenu.txt", "r");
    
	if(!fp)
	     printf("not able to open");
	    
	char c = fgetc(fp);
	while(c != EOF){
		
		printf("%c", c);
        c = fgetc(fp);

	}
	fclose(fp);
	return;
}








