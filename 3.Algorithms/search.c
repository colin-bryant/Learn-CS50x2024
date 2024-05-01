#include<cs50.h>
#include<stdio.h>
#include<string.h>

int main(void){
  // int Number[]={20,500,10,5,1,50};
  // int n =get_int("Number: ");
  // //1.linear search  number
  // for(int i = 0;i<7;i++){
  //   if(Number[i]=i){
  //     printf("found\n");
  //     return 0;
  //   }
  // }
  // printf("Not found\n");
  // return 1;

  string strings[]={"battleship","boot","cannon","iron","thimble","top hat"};

  string s =get_string("String: ");
  for(int i=0;i<6;i++){

    // strings[i]==s 在c当中 并不能比较字符串
    if(strcmp(strings[i],s)==0){
      printf("Found\n");
      return 0;
    }
  }
  printf("Not Found\n");
  return 1;
}

