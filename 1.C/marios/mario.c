#include<cs50.h>
#include<stdio.h>
void print_row(int spaces, int bricks);
int main(void){
    // Prompt the user for the pyramid's height
  int h;
  do{
    h =get_int("Height: ");
  }while(h<1||h>8);

  for(int i=0;i<h;i++){

    print_row(h-i,i+1);
 

    printf("\n");
  }

}
void print_row(int spaces,int bricks){
  //Print spaces
  for(int i=1;i<spaces;i++){
   printf(" ");
  }
  //Pront bricks
  for(int i=0;i<bricks;i++){
    printf("#");
  }
}

