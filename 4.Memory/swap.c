#include<stdio.h>


void swap(int *a, int *b);


int main(void){
  int x=1;
  int y=2;
  printf("x is %i,y is %i\n",x,y);
  swap(&x,&y);
  printf("x is %i,y is %i\n",x,y);
}

//passing by reference
void swap(int *a, int *b){
  int temp= *a;
  *a=*b;
  *b=temp;
}
//passing by value
// void swap(int a, int b){
//   int temp= a;
//   a=b;
//   b=temp;
// }
