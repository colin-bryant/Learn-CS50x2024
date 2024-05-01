#include<stdio.h>
#include<stdlib.h>

int main (void){

  int *list=malloc(3*sizeof(int));
  if(list = NULL){
    return 1;
  }
   list[0]=1;
   list[1]=2;
   list[2]=3;
  int *tmp=malloc(4*sizeof(int));
  if(tmp=NULL){
    //如果不释放内存会发生内存泄露
    free(list);
    return 1;
  }

  for(int i=0;i<3;i++){
    tmp[i]=list[i];
  }
  tmp[3]=4;

  free(list); //list 虽然被释放内存 但是内存块还是存在
  list=tmp; // 将 list 指向 tmp 所指向的内存块

  for(int i=0;i<4;i++){
    printf("%i\n",list[i]);
  }
   free(list);//释放了list 的同时也释放了tmp  因为它们指向同一块内存

   return 0;
}
