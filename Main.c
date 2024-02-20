#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>



int main(){
    int numberOfWords=0;
    char currentStr[256];
    int number;
    scanf("%d",&number);
    StrList* strlist=StrList_alloc();
    while(number!=0){
        if(number==1){
                scanf("%d",&numberOfWords);
                if(numberOfWords>0) {
                    while(numberOfWords>0){
                        scanf("%s",currentStr);
                        StrList_insertLast(strlist,currentStr);
                        numberOfWords--;
                    }
                
                }
        }
        else if(number==2){
                int index;
                scanf("%d",&index);
                scanf("%s",&currentStr);
                StrList_insertAt(strlist,currentStr,index);
        }
        else if (number==3){
                StrList_print(strlist);
            }
        else if(number==4){
            int len=StrList_size(strlist);
            printf("%d",len);
        }
        else if(number==5){
            int index;
            scanf("%d",&index);
            StrList_printAt(strlist,index);
        }
        else if(number==6){
            int count_chars=0;
            count_chars=StrList_printLen(strlist);
            printf("%d",count_chars);
        }
        else if(number==7){
            scanf("%s",currentStr);
            int n=StrList_count(strlist,currentStr);
            printf("%d",n);
        }
        else if(number==8){
            scanf("%s",currentStr);
            StrList_remove(strlist,currentStr);
        }
        else if(number==9){
            int index;
            scanf("%d",&index);
            StrList_removeAt(strlist,index);

        }
        else if(number==10){
            StrList_reverse(strlist);
        }
        else if(number==11){
            StrList_remove_all(strlist);
        }
        else if(number==12){
            StrList_sort(strlist);
        }
        else if(number==13){
            int n=StrList_isSorted(strlist);
            if(n==1) printf("true\n");
            else printf("false\n");
        }
        scanf("%d",&number);
    }
    

    return 0;
}