#include<cs50.h>
#include<stdio.h>
#include<string.h>

// int main(void){
//   string s =get_string("Intput: ");
//   printf("Output: ");
//   int length =strlen(s);
//   for(int i=0;i < length;i++){
//     printf("%c",s[i]);
//   }
//   printf("\n");
// }


int main(void){
  string s =get_string("Intput: ");
  printf("Output: ");

  for(int i=0,n=strlen(s);i < n;i++){
    printf("%c",s[i]);
  }
  printf("\n");
}
