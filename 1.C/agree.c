#include<cs50.h>
#include<stdio.h>

int main(void){
  char c= get_char("what's c ");
  if(c=='y' || c=='Y'){
    printf("Argeed\n");
  }
  else if(c=='n' ||c=='N'){
    printf("Not Argeed\n");
  }
}
