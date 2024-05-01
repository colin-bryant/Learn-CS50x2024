// 代替 就是 将26个字母 转换为key
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
//TODO
//Get key
//Validate key
//Get plaintext
//Encipher
//Print ciphertext
bool key_validate(string key);
char rotate(char p,string k);
int main(int argc,string argv[]){
  //make sure accept a single command-line argument
  if(argc!=2){
    printf("Usage: ./substitution key");
    return 1;
  }
   if(!key_validate(argv[1])){
    return 1;
   }
   string plaintext =get_string("plaintext:  ");

   printf("ciphertext: ");

// 在C语言中，字符串以null字符（'\0'）结尾，用于指示字符串的结束。当您声明一个字符数组并将其初始化为一个字符串时，编译器会自动在字符串的末尾添加一个null字符。 a[i] != '\0'
   for(int i=0;i<strlen(plaintext);i++){
   char p=rotate(plaintext[i],argv[1]);
   printf("%c",p);
   }


 printf("\n");
 return 0;
}
char rotate(char p,string k){

  if(isupper(p)){
   int index=p-'A';
   char c=toupper(k[index]);
   return c;
  }
  if(islower(p)){
   int index =p-'a';
   char c=tolower(k[index]);
   return c;
  }
 return p;
}
bool key_validate(string key){
   int n=strlen(key);
  if(n!=26){
    //长度
    printf("Key must contain 26 characters.\n");
    return false;
  }

  for(int i=0;i<n;i++){
    //make sure  an alphabetic character,
     if(!isalpha(key[i])){
       printf("Key must only contain alphabetic character.\n");
       return false;
     }

  }
     //make sure  key must not contain repeated character
     // 难度***
     int charset[26]={0};
   for(int i=0;i<n;i++){
    char c= tolower(key[i]);
    int index=c-'a';//
     if(charset[index]==0){
      charset[index]=1;
     }else{
      printf("key must not contain repeated character.\n");
       return false;
     }

   }
 return true;

}


