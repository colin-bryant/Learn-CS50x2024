#include<stdio.h>
#include<stdlib.h>
typedef struct node{
  int number;
  struct node *next;
}node;

int main(int argc, char *argv[]){
    node *list=NULL;

  for(int i=1;i<argc;i++){
    int number=atoi(argv[i]);
    node *n=malloc(sizeof(node));
    if(n==NULL){
      //Free memory thus far

      return 1;
    }
    n ->number=number;
    n->next=NULL;
    // n->next=NULL;
    if(list==NULL){
      list=n;
    }
    // if number belongs at beginning of list 如果插入的数字在列表的开头
    else if(n->number <list->number){
      n->next=list;
      list=n;
    }
    else{
      for(node *ptr=list;ptr!=NULL;ptr=ptr->next){
        //If at end of list
        if(ptr->next ==NULL){
          //Append node
          ptr->next=n;

        }
        //if in middle of list 插入的数字小于下一个节点的数字
        //就是说在中间插入  ptr一般在n-1的内存里 ptr->在n里
        if(n->number < ptr->next->number){
          n->next=ptr->next;
          ptr->next=n;
          break;
        }
      }
    }
  }
  //Print whole list
  node *ptr =list;
  while(ptr!=NULL){
    printf("%i\n",ptr->number);
    ptr=ptr->next;
  }

}
