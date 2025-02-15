#include "command.h"

void printTree(tnode t) {
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 
	
    if(!p)
        return;
    
    if(p->isrootNode || p->fname[0] != '.') {
		printf("\n");
		for(i = 0; i < count; i++) {    	
			printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			printf("%s", front);
		}
		
		if(p->isdir) {
			printf("%s", p->fname);
		}
		else {
			//access() checks whether file is executable or not
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				//X_OK -- access for execution, R_OK -- reading, W_OK -- writing
				printf("%s", p->fname);
			}
			else
				printf("%s", p->fname);
		}
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree(p->inner_ptr);
			else {
				dir_count++;		//incrementing directory count
				count++;
				printTree(p->inner_ptr);
				count--;
			}
		} 
		if(!p->isdir)
    		file_count++;		//incrementing file count
    }
    
    printTree(p->next_ptr);
    
    return;

}


//When -a flag used (print private files and directories also)
void printTree_a(tnode t) {
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 
    if(!p) {
        return;
  	}
	printf("\n");
	for(i = 0; i < count; i++) {    	
		printf("%s", down);
	}
		
	if(count >= 0 && !p->isrootNode) {
				printf("%s", front);
		}
		
		if(p->isdir)
			printf("%s", p->fname);

		else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				printf("%s", p->fname);

			}
			else
				printf("%s", p->fname);
		}
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree_a(p->inner_ptr);
			else {
				dir_count++;		//incrementing directory count
				count++;
				printTree_a(p->inner_ptr);
				count--;
			}
		} 
    
    if(!p->isdir)
    	file_count++;				//incrementing file count
    printTree_a(p->next_ptr);
    //printf("\n");
    
    return;

}

// -d flag (listing directories only)
void printTree_d(tnode t){
	node*p = t;
	int i;
	char *front = "|-+-+-+-", *down = "|    ";
	//if(p->isdir){
    if(!p)
	    return;

	if(p->isdir && (p->isrootNode || p->fname[0] != '.')) {
		printf("\n");
		for(i = 0; i < count; i++) {    	
				printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			printf("%s", front);
		}
		if(p->isdir){
			printf("%s", p->fname);
		}
		if(p->isdir){
			if(p->isrootNode)
			     printTree_d(p->inner_ptr);
            else{
				dir_count++;
				count++;
				printTree_d(p->inner_ptr);
				count--;

			}
		}
	  if(!p->isdir)
	       file_count++;	

		  
	}
    printTree_d(p->next_ptr);
    return;

}



void printTree_s(tnode t) {
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 
	
    if(!p)
        return;
    
    if(p->isrootNode || p->fname[0] != '.') {
		printf("\n");
		for(i = 0; i < count; i++) {    	
				printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			printf("%s", front);

		}
	
		long int k = p->info.fsize;
		int dig_count = 0;
		if(p->info.fsize) {
			while(k) {
				k /= 10;
				dig_count++;
			}
		}
		else
			dig_count = 1;
		
		if(p->isdir) {
			printf("%s  ", p->fname);
						
			if(!p->isrootNode) {
				printf("[");
				
				printf("%lu bytes]", p->info.fsize);
			}
		}
		else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				printf("%s  ", p->fname);
			}
			else
				printf("%s  ", p->fname);
				
			printf("[");
			printf("%lu bytes]", p->info.fsize);
		}
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree_s(p->inner_ptr);
			else {
				dir_count++;
				count++;
				printTree_s(p->inner_ptr);
				count--;
			}
		} 
		if(!p->isdir)
    		file_count++;
    }
    
    printTree_s(p->next_ptr);
    
    return;

}

//printing file path
void printTree_f(tnode t) {
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 
	
    if(!p)
        return;
    
    if(p->isrootNode || p->fname[0] != '.') {
		printf("\n");
		for(i = 0; i < count; i++) {    	
				printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			//if(p->next_ptr)
				printf("%s", front);
		
		}
		
		if(p->isdir) {
			printf("%s", p->info.fpath);

		}
		else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				printf("%s", p->info.fpath);

			}
			else
				printf("%s", p->info.fpath);
		}
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree_f(p->inner_ptr);
			else {
				dir_count++;
				count++;
				printTree_f(p->inner_ptr);
				count--;
			}
		} 
		if(!p->isdir)
    		file_count++;
    }
    
    printTree_f(p->next_ptr);
    
    return;

}

//levelwise printing
void printTree_L(tnode t, int level) {
	if(count >= level)
		return;
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 
	
    if(!p)
        return;
    
    if(p->isrootNode || p->fname[0] != '.') {
		printf("\n");
		for(i = 0; i < count; i++) {    	
				printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			//if(p->next_ptr)
				printf("%s", front);
		}
		
		if(p->isdir) {
			printf("%s", p->fname);
		
		}
		else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				printf("%s", p->fname);
			}
			else
				printf("%s", p->fname);
		}
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree_L(p->inner_ptr, level);
			else {
				dir_count++;
				count++;
				printTree_L(p->inner_ptr, level);
				count--;
			}
		} 
		if(!p->isdir)
    		file_count++;
    }
    
    printTree_L(p->next_ptr, level);
    
    return;

}

//list inode value
void printTree_inode(tnode t) {
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 

    if(!p)
        return;
    
    if(p->isrootNode || p->fname[0] != '.') {
		printf("\n");
		for(i = 0; i < count; i++) {    	
				printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			//if(p->next_ptr)
				printf("%s", front);
		}
		
		if(p->isdir) {
		
			printf("%s  ", p->fname);
			
			if(!p->isrootNode)
				printf("[%ld]", p->info.inode);
		}
		else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				
				printf("%s  ", p->fname);
				
				printf("[%ld]", p->info.inode);
			}
			else
				printf("%s  [%ld]", p->fname, p->info.inode);
		}
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree_inode(p->inner_ptr);
			else {
				dir_count++;
				count++;
				printTree_inode(p->inner_ptr);
				count--;
			}
		} 
		if(!p->isdir)
    		file_count++;
    }
    
    printTree_inode(p->next_ptr);   
    return;

}

//when -D flag is used (To display last modification date and time of file) 
void printTree_D(tnode t) {
	node *p = t;
	int i;
	char *front = "|----", *down = "|    "; 
	//char *last = "'----";
    if(!p)
        return;
    
    if(p->isrootNode || p->fname[0] != '.') {
		printf("\n");
		for(i = 0; i < count; i++) {    	
				printf("%s", down);
		}
		
		if(count >= 0 && !p->isrootNode) {
			//if(p->next_ptr)
				printf("%s", front);
			
		}
		
		if(p->isdir) {
			
			printf("%s", p->fname);
			
			if(!p->isrootNode) {
				//checking number of digits in hours and minutes
				if(p->info.last_mod.fhour >= 10 && p->info.last_mod.fmin >= 10)
					printf("  [%hi/%hi/%hi %hi:%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
				else if(p->info.last_mod.fhour >= 10 && p->info.last_mod.fmin < 10)
					printf("  [%hi/%hi/%hi %hi:0%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
				else if(p->info.last_mod.fhour < 10 && p->info.last_mod.fmin >= 10)
					printf("  [%hi/%hi/%hi 0%hi:%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
				else if(p->info.last_mod.fhour < 10 && p->info.last_mod.fmin < 10)
					printf("  [%hi/%hi/%hi 0%hi:0%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
			}
		}
		else {
			if(!access(p->fname,X_OK) || !strcmp(p->fname, "a.out")) {
				printf("%s", p->fname);
			}
			else
				printf("%s", p->fname);
			//checking number of digits in hours and minutes
			if(p->info.last_mod.fhour >= 10 && p->info.last_mod.fmin >= 10)
				printf("  [%hi/%hi/%hi %hi:%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
			else if(p->info.last_mod.fhour >= 10 && p->info.last_mod.fmin < 10)
				printf("  [%hi/%hi/%hi %hi:0%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
			else if(p->info.last_mod.fhour < 10 && p->info.last_mod.fmin >= 10)
				printf("  [%hi/%hi/%hi 0%hi:%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
			else if(p->info.last_mod.fhour < 10 && p->info.last_mod.fmin < 10)
				printf("  [%hi/%hi/%hi 0%hi:0%hi]", p->info.last_mod.fdate, p->info.last_mod.fmon, p->info.last_mod.fyear, p->info.last_mod.fhour, p->info.last_mod.fmin);
		}
	
		
		if(p->isdir) {
			if(p->isrootNode)
				printTree_D(p->inner_ptr);
			else {
				dir_count++;
				count++;
				printTree_D(p->inner_ptr);
				count--;
			}
		} 
		if(!p->isdir)
    		file_count++;
    }
    
    printTree_D(p->next_ptr);
    
    return;

}