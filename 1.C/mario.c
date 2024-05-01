#include<cs50.h>
#include<stdio.h>

int main(void){

  // const int n =get_int("size: ");
  // int n =get_int("size: ")
  // while(n<1){
  //  n=get_int("size: ");
  // }
  //Prompt user for positive integer
  int n;
  do{
    n = get_int("size: ");
  }while( n<1);
  // Print an n-by-n grid of bricks
  for(int i = 0;i<n;i++){
    for(int j=0;j<n;j++){
      printf("#");
    }
    printf("\n");
  }
}
