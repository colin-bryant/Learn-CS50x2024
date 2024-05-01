#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(void){
  string s=get_string("Before: ");
  printf("After:  ");

  // for(int i =0,n=strlen(s);i<n;i++){
  //   printf("%c\n",toUpper(s[i]));
  // }
 for(int i=0,n=strlen(s);i<n;i++){

 if(s[i] >='a' && s[i]<='z'){
  printf("%c\n",s[i]-('a'-'A'));
 }else{
   printf("%c\n",s[i]);
 }
 }
}


