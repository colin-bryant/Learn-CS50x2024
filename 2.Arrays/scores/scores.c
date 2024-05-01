#include<cs50.h>
#include<stdio.h>
//全局变量
 const  int N=3;


int main(void){

  int scores[N];
  int sum=0;
  for(int i=0;i<N;i++){
    scores[i]=get_int("Scores: ");
    sum+=scores[i];
  }
  printf("Average:,%f\n",sum/(float)N);
}
