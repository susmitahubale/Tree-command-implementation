#include"command.h"


//merge sorting for link list
//for finding mid value(tortoid method)
node* findMid(tnode head){
     node *slow_ptr = head; 
     node *fast_ptr = head; 
  
    while (fast_ptr->next_ptr && fast_ptr->next_ptr->next_ptr) 
   {    slow_ptr = slow_ptr->next_ptr; 
        fast_ptr = fast_ptr->next_ptr->next_ptr; 
         
    } 
    return slow_ptr;        
}

node* merge(tnode left, tnode right){

    if(left == NULL)
        return right;

    if(right == NULL)
        return left;
    node* ans = NULL;;
    node*p= left , *q = right, *r= NULL;

    //comapre indiviual list and then add
    if(strcasecmp(left->fname, right->fname)< 0){
        ans = p;
        r = p;
        p = p->next_ptr;
    }
    else{
        ans = q;
        r = q;
        q = q->next_ptr;
    }
    
    // any one list in available only
    while(p && q) {
    	//comparing file names
        if(strcasecmp(p->fname, q->fname) < 0) {
            r->next_ptr = p;
            p = p->next_ptr;
        }
        else {
            r->next_ptr = q;
            q = q->next_ptr;
        }
        r = r->next_ptr;
    }
    if(p)
        r->next_ptr = p;
    if(q)
        r->next_ptr = q;

    return ans;       
}

node* mergeSort(tnode head){
    //base case

    if(head == NULL || head->next_ptr == NULL)
        return head;
  
    node*mid = findMid(head);
    //seperating list in two parts
    //1st half
    node*left = head;
    //second half
    node*right = mid->next_ptr;
    //discoonect list from mid
    mid->next_ptr =NULL ;
      
    
    //recurse call to sort both halves
    node*l = mergeSort(left);
    node*r = mergeSort(right);  
    
    //merge both halves
    return merge(l, r);
    
}

//sort for subdirectory

node* sort_subd(tnode q){
    node* sorted = mergeSort(q);

    node* a = sorted ;
  
    while(a){
        if(a->inner_ptr)
               a->inner_ptr = sort_subd(a->inner_ptr);
        a = a->next_ptr;     
      
    }
    return sorted; 
}














