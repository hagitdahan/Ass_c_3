#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct _node {
    const char * _data;
    struct _node * _next;
} Node;

struct _StrList{
    Node * _head;
    size_t _size;
};
typedef struct _StrList StrList;

Node * Node_alloc(const char * data, Node * next) {
	Node* p= (Node*)malloc(sizeof(Node));
    //checking if malloc didnt work well
    if(p==NULL) return NULL;
    //otherwise create memory for new data also checking if malloc work well else free p 
    else{
        p->_data=(char *)malloc(strlen(data)+1);
        if(p->_data!=NULL){
            strcpy((char*)p->_data,data);
            p->_next= next;
        } 
        else{
            free(p);
            p=NULL;
        } 
    }
	return p;
}

StrList * StrList_alloc(){
    //create new strlist with create memory and initialize size 
    //and head and return pointer to the new list.
	StrList * p= (StrList*)malloc(sizeof(StrList));
    if(p!=NULL){
	    p->_head= NULL;
	    p->_size= 0;
    }
	return p;
}
void StrList_remove_all(StrList * strlist){
    //if there is one node in the list just delete the head
    //free the data and the node,and update the size
    if(strlist->_size==1){
        free((void *)strlist->_head->_data);
        strlist->_head=NULL;
        strlist->_size=0;
    }
    //if there is 2 nodes at list free to the data and the node,by holding 2 nodes
    //every time and free the first of them,update the size to 0
    else if(strlist->_head!=NULL && strlist->_head->_next!=NULL)
    {
        Node * current_node=strlist->_head;
        Node * next;
        while(current_node!=NULL){
            next=current_node->_next;
            free((void *)current_node->_data);
            free(current_node);
            current_node=next;
        }
        strlist->_head=NULL;
        strlist ->_size=0;   
    }
}
void StrList_free(StrList* StrList){
    //free to strlist,if the list not alloc return.
    //otherwise we are doing free to all nodes, also there data, after free to the list
    StrList_remove_all(StrList);
    free(StrList);
}
size_t StrList_size(const StrList* StrList){
    //return the size of the list
    return StrList->_size;
}
/*if the list is empty ask for memory and insert the head,
else insert in the end of the list' also update the size of the list*/
void StrList_insertLast(StrList* StrList,const char* data){
    Node * new_p = Node_alloc(data,NULL);
    if(new_p!=NULL){
        if(StrList->_head==NULL) {
            StrList->_head=new_p;
            StrList->_size++;
        }
        else {
            Node * p=StrList->_head;
            while(p->_next!=NULL){
                p=p->_next;
            }
            p->_next=new_p;
            StrList->_size++;
        }
    }
}
/*first checking that the index is valid, then going to the right place in the list, 
ask for memory for the node and insert him then update the size of the list*/
void StrList_insertAt(StrList* StrList,const char* data,int index){
    if(index>=0 && index<=StrList->_size){
        if(StrList->_head!=NULL){
            //private case insert last
            if(index==StrList->_size) StrList_insertLast(StrList,data);
            Node * p=StrList->_head;
            while(index-1>0){
                p=p->_next;
                index--;
            }
            Node * new_node=Node_alloc(data,p->_next);
            if(new_node!=NULL){
                //insert in head
                if(index==0){
                    new_node->_next=StrList->_head;
                    StrList->_head=new_node;
                }
                //regular case
                else{
                    p->_next=new_node;
                }
                StrList->_size++;
            }
        }
        //if the list is empty
        else{
            StrList_insertLast(StrList,data);
        }
    }
}

char* StrList_firstData(const StrList* StrList){
    //if the head not null return the first string of the head node
    //else return null.
    if(StrList->_head!=NULL){
        return (char*)StrList->_head->_data;
    }
    else return NULL;
}
void StrList_print(const StrList* StrList){
    //print all the strings in Strlist
    if(StrList->_head!=NULL){
        Node * p= StrList->_head;
        for(int i=0;i<StrList->_size;i++){
            printf("%s",p->_data);
            if(i<StrList->_size-1) printf(" ");
            p=p->_next;
        }
    }
    printf("\n");
}
/*check that the index is valid,
 then going the node in the index and print his data to the screen*/
void StrList_printAt(const StrList* Strlist,int index){
    if(index>=0 && index<Strlist->_size){
        int i=0;
        Node * p=Strlist->_head;
        while(i<index){
            p=p->_next;
            i++;
        }
        printf("%s\n",p->_data);
    }
}
/*first the count equal to zero, then this func going on the list and update the count
by the number of chars in the nodes*/
int StrList_printLen(const StrList* Strlist){
    int count=0;
    if(Strlist->_head!=NULL){
        Node * p=Strlist->_head;
        while(p!=NULL){
            count=count+strlen(p->_data);
            p=p->_next;
        }
    }
    return count;
}
/*if there is nodes with the same data in the input num_exist++*/
int StrList_count(StrList* StrList, const char* data){
    int num_exist=0;
    if(StrList->_head!=NULL){
        Node * p=StrList->_head;
        while(p!=NULL){
            if (strcmp(data,p->_data)==0)
            {
                num_exist++;
            }
            p=p->_next;
        }
    }
    return num_exist;
}
/*this function remove all the nodes that there date equal to the input data
by free the data and the node then update the size ovf the list*/
void StrList_remove(StrList* StrList, const char* data) {
    if (StrList->_head != NULL) {
        Node *current_node = StrList->_head;
        Node *prev_node = NULL; // Track the previous node to update next pointers
        while (current_node != NULL) {
            // Check if the data matches the current node's data
            if (strcmp(data, current_node->_data) == 0) {
                // Special case: removing the head node
                if (current_node == StrList->_head) {
                    StrList->_head = current_node->_next;
                } else {
                    prev_node->_next = current_node->_next;
                }
                free((void *)current_node->_data); // Free memory allocated for data
                free(current_node); // Free memory allocated for the node
                current_node=StrList->_head;
                StrList->_size--;
            }
            else {
                // Moving to the next node
                prev_node = current_node;
                if(current_node->_next!=NULL){
                    current_node = current_node->_next;
                }
                else return;
            }
            
        }
    }
}
/*this func remove the node at the input index, first check if the index valid
then going to the node in the index and remove him, free the data and the node
and update the size of the liss*/
void StrList_removeAt(StrList* StrList, int index){
    if(index>=0&&index<=StrList->_size){
        if(StrList->_head!=NULL){
            Node * p=StrList->_head;
            Node * to_remove=StrList->_head;
            int i=0;
            //going to the node in before the index
            while(i<index-1){
                p=p->_next;
                i++;
            }
            //private case remove head
            if(index==0){
                StrList->_head=to_remove->_next;
            }
            else {
                to_remove=p->_next;
                p->_next=to_remove->_next;
            }
            //upadte the size and free node and data
            StrList->_size--;
            free((void *)to_remove->_data);
            free(to_remove);

        }
        
    }
}
/*this func check if two lists have the same nodes by strcmp if they are equal return 1
else return 0 */
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1->_size!=StrList2->_size){
        return 0;
    }
    else
    {
        Node * p1=StrList1->_head;
        Node * p2=StrList2->_head;
        while (p1!=NULL) 
        {
            if(strcmp(p1->_data,p2->_data)!=0)
                return 0;
            p1=p1->_next;
            p2=p2->_next;
        } 
    }
    return 1;
}
/*this func create new list (with alloc memory) then create new nodes with the same data 
as the list in the input then return the new list*/
StrList* StrList_clone(const StrList* Strlist){
    StrList * newlist=StrList_alloc();
    if(newlist==NULL) return NULL;
    else{
        if(Strlist->_head!=NULL){
            Node * n=Strlist->_head;
            while (n!=NULL)
            {
                StrList_insertLast(newlist,n->_data);
                n=n->_next;
            }
            
        }
    }
    return newlist;
}
/*this function reverse the list by 3 pointers to nodes*/
void StrList_reverse( StrList* StrList){
    if(StrList->_head!=NULL){
        Node * current_node=StrList->_head;
        Node * prev_node=NULL;
        Node * next_node=NULL;
        while(current_node->_next!=NULL){
            next_node=current_node->_next;
            current_node->_next=prev_node;
            prev_node=current_node;
            current_node=next_node;
        }
        //dealing with the last last node and create connection with the new head of the list
        current_node->_next=prev_node;
        StrList->_head=current_node;
    }

}
/*in this func we do bubble sort with 3 pointers to make the swap*/
void StrList_sort( StrList* StrList){
    int size=StrList->_size;
    if(StrList->_head!=NULL){
        for(int j=0;j<size-1;j++){
            Node* p=StrList->_head;
            Node* temp1 = p ->_next;
            Node* prev = StrList ->_head;
            for(int i=0 ; i<size-j-1 && p->_next!=NULL;i++){
                //swap pointers
                if(strcmp(p->_data,p->_next->_data)>0){
                    if(i==0){
                        StrList ->_head = temp1;
                        prev=StrList->_head;
                        p ->_next = temp1 ->_next;
                        StrList -> _head ->_next = p;
                    }
                    else {
                        temp1 = p->_next;
                        prev->_next = temp1;
                        p->_next = temp1->_next;
                        temp1->_next = p;
                        prev = prev ->_next;
                    }
                }
                else{
                    prev=p;
                    p=p->_next;
                }
            }
        }
    }

}
/*checking if the data in the nodes sort by letters
if yes return 1, else return 0 by strcmp*/
int StrList_isSorted(StrList* StrList){
    if(StrList->_head!=NULL){
        Node * p=StrList->_head;
        while(p->_next!=NULL){
            
            if(strcmp(p->_data,p->_next->_data)>0)
            {
                return 0;
            }
            p=p->_next;
        }
    }
    return 1;
}
