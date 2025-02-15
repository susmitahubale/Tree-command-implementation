#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"command.h"




void tree_arg1(char *rootname) {
	tnode p = NULL;
	
	//creating tree structure and sorting alphabetically
	p = createTree(rootname);
	if(p) 
		p->inner_ptr = sort_subd(p->inner_ptr);
	printTree(p);
	printf("\n");
    	
    printf("\n%d directories, %d files\n", dir_count, file_count);
	
}

void tree_arg2(char *rootname, char *flag) {
	
	//creating tree structure and sorting alphabetically
	tnode p = createTree(rootname);
	if(p) 
		p->inner_ptr = sort_subd(p->inner_ptr);


	//comparing command line argument with different flags
	if(!strcmp(flag, "-a")) {
		printTree_a(p);
		printf("\n");
	}
	else if(!strcmp(flag, "-d")) {
		printTree_d(p);
		printf("\n");
	
       printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if(!strcmp(flag, "-s")) {
		printTree_s(p);
		printf("\n");
    	
    	printf("\n%d directories, %d files\n", dir_count, file_count);
	}
    else if(!strcmp(flag, "-f")) {
		printTree_f(p);
		printf("\n");
    	
    	printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if(!strcmp(flag, "--inodes")) {
		printTree_inode(p);
		printf("\n");
    	
    	printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else if(!strcmp(flag, "-D")) {
		printTree_D(p);
		printf("\n");
    	
    	printf("\n%d directories, %d files\n", dir_count, file_count);
	}
	else{
		printf("Invalid Flag <:) ");
	}

	
}

void tree_arg3(char *rootname, char *arg1, char *arg2) {
	if(!strcmp(arg1, "-L")) {
		tnode p = createTree(rootname);
		if(p) 
			 p->inner_ptr = sort_subd(p->inner_ptr);
		    
		//checking level exceeded or not
		//atoi --> convert string argument into integer
		if(atoi(arg2) > 0) {
			printTree_L(p, atoi(arg2));  
			printf("\n");
			
			printf("\n directories-> %d, files--> %d\n", dir_count, file_count);
		}
		else {
			printf("Level must be greater than 0\n");
		}
	}

}

int main(int argc, char*argv[]){
     switch(argc) {
    	case 1:
    		   tree_arg1(".");
			   printf("tree printed");
    		   break;
    	case 2:   
		       if(!strcmp(argv[1], "--help")){
			         
    			     help();
					 
			    }
    		    else if(!strcmp(argv[1], "-a") || !strcmp(argv[1], "-d") || !strcmp(argv[1], "-s") || !strcmp(argv[1], "-f") || !strcmp(argv[1], "--inodes") || !strcmp(argv[1], "-D")){
    	    	    	tree_arg2(".", argv[1]);
					    printf("%s..",argv[1]);
				//	    tree_arg2(argv[1], argv[2]);
			            break;
			    }
    		    else    
    		 	    tree_arg1(argv[1]);
    		        break;
                break; 
		case 3:
    		    if(!strcmp(argv[1], "-L") ) {
    		     	tree_arg3(".", argv[1], argv[2]);
					printf("...");
					break;
				}
    		    else{
    			    tree_arg2(argv[1], argv[2]);
					
    		        break;
				}		
		case 4:
		        if(!strcmp(argv[2], "-L"))
    		        tree_arg3(argv[1], argv[2], argv[3]);
				break;
		default:
		        printf("command not found");		
		       			
     } 
    return 0;        
}



//                          Thank You ... :)
//                                        112003048(Susmita Hubale)