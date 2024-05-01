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
    else{
      for(node *ptr=list;ptr!=NULL;ptr=ptr->next){
        //If at end of list
        if(ptr->next ==NULL){
          //Append node
          ptr->next=n;
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
