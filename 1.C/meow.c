#include<cs50.h>
#include<stdio.h>

void meow(int n)

int main(void){
  // int i = 3;
  // while(i>0){
  //   meow();
  //   i--;
  // }
  // for(int i=0;i<3;i++){
  //   meow();
  // }
  meow(5);
}
void meow(int n){
  for(int i=0;i<n;i++){
    printf("meow\n");
  }
}
