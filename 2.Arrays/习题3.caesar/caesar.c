#include<cs50.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//TODO
// Get key 密钥
// Get plaintext 明文
// Encipher 加密
// print ciphertext 打印密文
bool only_digits(string s);
char rotate(char c,int n);
int main(int argc,string argv[]){
 // Make sure program was run with just one command-line argument

 if(argc!=2){

     printf("Usage: ./caesar key\n");
     return 1;
 }
 // Make sure every character in argv[1] is a digit 都是一个数字 非负整数
 if(!only_digits(argv[1])) {
  printf("Usage: ./caesar key\n");
  return 1;
 }else{
  printf("Usage: ./caesar %s\n",argv[1]);
 }

//Convert（转变） argv[1] from a 'string' to an 'int'  atoi 把字符串转换为整数 在stdio.h
  int key=atoi(argv[1]);
  // Prompt user for plaintext 明文
  string plaintext=get_string("plaintext:  ");
  printf("ciphertext: ");
    // For each character in the plaintext:
    for(int i=0,n=strlen(plaintext);i<n;i++){
      // Rotate the character if it's a letter
      char c=rotate(plaintext[i],key);
      printf("%c",c);
    }
    printf("\n");
    return 0;
}
 //1. check the key
bool only_digits(string key){
   // 保证key的每一位都是数字
  for(int i =0,n=strlen(key);i<n;i++){
     if(!isdigit(key[i])){

       return false;
     }

  }
 return true;
}
// isalpha isupper islower
char rotate(char c,int n){
    if(isupper(c)){
      char c_digit=(c-'A'+n)%26+'A';
      return c_digit;
    }
    else if(islower(c)){
       char c_digit=(c-'a'+n)%26+'a';
      return c_digit;
    }
    // else if(!isalpha(c)){
    //   return c;
    // }
    return c;
}
